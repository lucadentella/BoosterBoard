#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RotaryEncoder.h>
#include <LiquidCrystal.h>

#include "BoosterBoard.h"

OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);
RotaryEncoder encoder(ENCODER_PIN_A, ENCODER_PIN_B);
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Current and temperature values
float current;
float maxCurrent = 5.0;
float temperature;
float maxTemperature = 60.0;

// Current and temperature sampling
int currentSampleCount = 0;
long currentSampleSum = 0;
bool temperatureRequested = false;
long temperatureRequestTime = 0;

// FSM
int currentWorkingMode;
int currentConfigStatus;

// Encoder
int encoderPosition = 0;
bool currentChoice = true;

// Buttons
bool armButtonAlreadyPressed = false;
bool encButtonAlreadyPressed = false;
bool armButtonDebounce = false;
bool encButtonDebounce = false;
long armButtonDebounceTime = 0;
long encButtonDebounceTime = 0;


void setup() {

  Serial.begin(115200);
  Serial.print("BoosterBoard v");
  Serial.println(FIRMWARE_VERSION);
  Serial.println();
  
  pinMode(BOOSTER_ENABLE_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(ENCODER_PIN_BTN, INPUT_PULLUP);
  pinMode(ARM_PIN_BTN, INPUT_PULLUP);  
  Serial.println("PIN setup complete");

  currentWorkingMode = W_STOP;
  boosterOff();
  Serial.println("Booster OFF at startup");

  // read values from EEPROM if valid, else store default values
  byte eepromValid;
  EEPROM.get(E_VALID_VALUES, eepromValid);
  if(eepromValid == 123) {
    EEPROM.get(E_MAX_CURR_ADDR, maxCurrent);
    EEPROM.get(E_MAX_TEMP_ADDR, maxTemperature);
    Serial.println("Max values retrieved from EEPROM");
  } else {
    eepromValid = 123;
    EEPROM.put(E_MAX_CURR_ADDR, maxCurrent);
    EEPROM.put(E_MAX_TEMP_ADDR, maxTemperature);
    EEPROM.put(E_VALID_VALUES, eepromValid);
    Serial.println("Default values stored in EEPROM");
  }

  sensors.begin();
  sensors.setWaitForConversion(false);
  Serial.println("Temperature sensor initialized");

  lcd.begin(16, 2);
  lcd.createChar(0, selectChar);
  lcd.createChar(1, modifyChar);  
  Serial.println("LCD initialized");
  lcd.setCursor(2, 0);
  lcd.print("BoosterBoard");
  lcd.setCursor(6, 1);
  lcd.print("v");
  lcd.print(FIRMWARE_VERSION);
  
  delay(2000);
  lcd.clear();
  printLCDFirstLine();
  printLCDSecondLine();
  printMaxCurrent();
  printMaxTemperature();
  printCursor();
  Serial.println();
  Serial.println("Booster ready!");
  Serial.println();
}

void loop() {

  // if working, check temperature and current
  if(currentWorkingMode == W_POWER) {
    checkCurrent(); 
    checkTemperature();
  }

  // if not working, check encoder and its button
  else {

    encoder.tick();
    checkEncoder();
    checkEncButton();
  }

  // always check the ARM button
  checkARMbutton();
}

void checkCurrent() {

  int sample = analogRead(BOOSTER_CURRENT_PIN);
  if(sample > 1000) {
    currentWorkingMode = W_ALERT_SHORT;
    boosterOff();
    Serial.println("Booster OFF due to a short circuit"); 
    return;
  }
  currentSampleSum += sample;
  currentSampleCount++;

  if(currentSampleCount == CURRENT_SAMPLES) {
    float newCurrent = 0.00415 * (currentSampleSum / CURRENT_SAMPLES);    
    if(newCurrent > maxCurrent) {
      currentWorkingMode = W_ALERT_CUR;
      boosterOff();
      current = newCurrent;
      printCurrent();
      Serial.println("Booster OFF due to max current reached");       
    }
    else if(current != newCurrent) {
      current = newCurrent;
      printCurrent();
    }
    currentSampleSum = 0;
    currentSampleCount = 0;
  }
}

void checkTemperature() {

  if(!temperatureRequested) {
    
    sensors.requestTemperatures();
    temperatureRequested = true;
    temperatureRequestTime = millis();
  } else {

    if(millis() > temperatureRequestTime + TEMPERATURE_WAIT_TIME) {

      float newTemperature = sensors.getTempCByIndex(0);
      if(newTemperature != DEVICE_DISCONNECTED_C) {

        if(newTemperature > maxTemperature) {
          currentWorkingMode = W_ALERT_TEMP;
          boosterOff();
          temperature = newTemperature;
          printTemperature(); 
          Serial.println("Booster OFF due to max temperture reached");                               
        }
        else if(temperature != newTemperature) {
          temperature = newTemperature;
          printTemperature();          
        }       
      }
      temperatureRequested = false;
    }    
  }
}

void checkARMbutton() {

  int armButtonStatus = digitalRead(ARM_PIN_BTN);
  
  // button pressed
  if(armButtonStatus == 0) {

    // already pressed? no further action
    if(armButtonAlreadyPressed) return;

    // do we need to debounce? 
    if(!armButtonDebounce) {
      armButtonDebounce = true;
      armButtonDebounceTime = millis();
      return;
    }

    // in debounce, if time has passed do the requested action
    else if(millis() > armButtonDebounceTime + DEBOUNCE_INTERVAL) {
      if(currentWorkingMode == W_POWER) {
        currentWorkingMode = W_STOP; 
        boosterOff();
        Serial.println("Booster OFF via ARM button");           
      }
      else {
        boosterOn();
        Serial.println("Booster ON via ARM button");
      }
      armButtonAlreadyPressed = true;
    }
  }

  // button not pressed, reset variables
  else {
    armButtonAlreadyPressed = false;
    armButtonDebounce = false;
  }  
}


void checkEncoder() {

  int newEncoderPosition = encoder.getPosition();
  if (encoderPosition != newEncoderPosition) {

    bool positiveIncrement = (encoderPosition > newEncoderPosition);
    
    switch(currentConfigStatus) {

      case S_SELECT:
        currentChoice = !currentChoice;
        printCursor();
        break;

      case S_MODIFY:
        bool changed = false;
        if(currentChoice) {
          if(positiveIncrement && maxCurrent < MAX_CURRENT) { maxCurrent += 0.1; changed = true; }
          if(!positiveIncrement && maxCurrent > 0.1) { maxCurrent -= 0.1; changed = true; }
          if(changed) {
            EEPROM.put(E_MAX_CURR_ADDR, maxCurrent);
            printMaxCurrent();
          } 
        }
        if(!currentChoice) {
          if(positiveIncrement && maxTemperature < MAX_TEMPERATURE) { maxTemperature += 1.0; changed = true; }
          if(!positiveIncrement && maxTemperature > 0.1) { maxTemperature -= 1.0; changed = true; }
          if(changed) {
            EEPROM.put(E_MAX_TEMP_ADDR, maxTemperature);
            printMaxTemperature();
          } 
        }      
        break; 
    }
    encoderPosition = newEncoderPosition;
  }
}

void checkEncButton() {

  int encButtonStatus = digitalRead(ENCODER_PIN_BTN);
  
  // button pressed
  if(encButtonStatus == 0) {

    // already pressed? no further action
    if(encButtonAlreadyPressed) return;

    // do we need to debounce? 
    if(!encButtonDebounce) {
      encButtonDebounce = true;
      encButtonDebounceTime = millis();
      return;
    }

    // in debounce, if time has passed do the requested action
    else if(millis() > encButtonDebounceTime + DEBOUNCE_INTERVAL) {
      if(currentConfigStatus == S_SELECT) currentConfigStatus = S_MODIFY;
      else currentConfigStatus = S_SELECT;
      printCursor();
      encButtonAlreadyPressed = true;      
    }
  }

  // button not pressed, reset variables
  else {
    encButtonAlreadyPressed = false;
    encButtonDebounce = false;
  }
}

void boosterOn() {

  digitalWrite(BOOSTER_ENABLE_PIN, HIGH);
  digitalWrite(STATUS_LED_PIN, HIGH);
  currentWorkingMode = W_POWER;
  currentConfigStatus = S_IDLE;
  current = -1.0;
  temperature = -1.0;  
  printLCDFirstLine();
  clearCursor();  
}

void boosterOff() {

  digitalWrite(BOOSTER_ENABLE_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);
  currentConfigStatus = S_SELECT;
  printLCDFirstLine();
  printCursor();
}
