void printLCDFirstLine() {

  lcd.setCursor(0,0);
  if(currentWorkingMode == W_STOP) lcd.print("    - STOP -    ");
  else if(currentWorkingMode == W_POWER) lcd.print("-ON-            ");
  else if(currentWorkingMode == W_ALERT_CUR) lcd.print("Curr ALERT!");
  else if(currentWorkingMode == W_ALERT_TEMP) lcd.print("Temp ALERT!");
  else if(currentWorkingMode == W_ALERT_SHORT) lcd.print("! SHORTCIRCUIT !");
}

void printLCDSecondLine() {

  lcd.setCursor(0,1);
  lcd.print("Max");
  lcd.setCursor(9,1);
  lcd.print("A");
  lcd.setCursor(14,1);
  lcd.print((char)223);
  lcd.print("C"); 
}

void printCursor() {

  lcd.setCursor(4,1);
  if(currentChoice) {
    if(currentConfigStatus == S_SELECT) lcd.write(byte(0));
    else lcd.write(byte(1));
  }
  else lcd.print(" ");
  lcd.setCursor(10,1);
  if(!currentChoice) {
    if(currentConfigStatus == S_SELECT) lcd.write(byte(0));
    else lcd.write(byte(1));
  }
  else lcd.print(" ");   
}

void clearCursor() {

  lcd.setCursor(4,1);
  lcd.print(" ");
  lcd.setCursor(10,1);
  lcd.print(" ");   
}

void printMaxCurrent() {

  lcd.setCursor(5,1);
  if(maxCurrent < 10) lcd.print(" ");
  lcd.print(maxCurrent, 1);  
}

void printMaxTemperature() {

  lcd.setCursor(12,1);
  if(maxTemperature < 10) lcd.print(" ");
  lcd.print(maxTemperature, 0);   
}

void printCurrent() {

  if(currentWorkingMode == W_ALERT_CUR) lcd.setCursor(11,0);
  else lcd.setCursor(5,0);
  if(current < 10) lcd.print(" ");
  lcd.print(current, 1);
  lcd.print("A");
}

void printTemperature() {

  lcd.setCursor(11,0);
  if(temperature < 100) lcd.print(" ");
  lcd.print(temperature, 0);
  lcd.print((char)223);
  lcd.print("C");
}
