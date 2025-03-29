#define FIRMWARE_VERSION  "1.0"

// Hardware connections
#define BOOSTER_ENABLE_PIN  3
#define BOOSTER_CURRENT_PIN A0
#define ENCODER_PIN_A       A2
#define ENCODER_PIN_B       A3
#define ENCODER_PIN_BTN     A1
#define ARM_PIN_BTN         A4
#define TEMPERATURE_PIN     12
#define STATUS_LED_PIN      13
#define LCD_RS              2
#define LCD_EN              4
#define LCD_D4              6
#define LCD_D5              7
#define LCD_D6              8
#define LCD_D7              9

// EEPROM addresses
#define E_MAX_CURR_ADDR     0
#define E_MAX_TEMP_ADDR     10
#define E_VALID_VALUES      20

// Absolute maximum values
#define MAX_CURRENT         10.0
#define MAX_TEMPERATURE     80.0

// Sampling parameters
#define CURRENT_SAMPLES       4000
#define TEMPERATURE_WAIT_TIME 1000
#define DEBOUNCE_INTERVAL     50

// FSM
#define W_STOP              0
#define W_POWER             1
#define W_ALERT_CUR         2
#define W_ALERT_TEMP        3
#define W_ALERT_SHORT       4
#define S_IDLE              0
#define S_SELECT            1
#define S_MODIFY            2

// LCD custom chars
byte selectChar[] = {B00000,B00100,B00110,B11111,B00110,B00100,B00000,B00000};
byte modifyChar[] = {B00100,B01110,B11111,B00000,B11111,B01110,B00100,B00000};
