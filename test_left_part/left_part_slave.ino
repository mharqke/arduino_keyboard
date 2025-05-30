///////////////////////////////////////////////////
/*
pin D18: I2C SDA  |   usb   |   pin D21:  aux. pot
pin D19: I2C SCL  |         |   pin D8:  row 8
pin D14: row 1    |         |   pin D7:  col 1
pin D15: row 2    |         |   pin D6:  col 2
pin D16: row 3    |   top   |   pin D5:  col 3
pin D17: row 4    |         |   pin D4:  col 4
pin D20: row 5    |         |   pin D3:  col 5
pin D21: row 6    |         |
pin D2:  row 7    |_________|
8 rows and 9 cols(5-4 on each side == 5 on each)
8 rows * 5 columns == 40 buttons == 40bits
left - 35 / right - 35
left - 4bits free / right - 5bits free
total - 80bits(9 bits free) = 10b
1000 time per second = 10_000b/s = 10Kb/s 

!!!!!!!! i guess it's left part and it's slave (send data)

*/
//////////////////////////////////////////////////

#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)

const uint8_t ROWS = 7;
const uint8_t COLS = 7;


uint8_t rows[ROWS] = { 16, 10, 9, 8, 7, 6, 5 };
uint8_t cols[COLS] = { A3, A2, A1, A0, 15, 14, 30 };

bool pressed_buttons[COLS][ROWS]{
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 }
};
uint8_t keys[COLS][ROWS] = 
{
  { 0, 1, 2, 3, 4, 5, 6 },
  { 7, 8, 9, 10, 11, 12, 13 },
  { 14, 15, 16, 17, 18, 19, 20 },
  { 21, 22, 23, 24, 25, 26, 27 },
  { 28, 29, 30, 31, 32, 33, 34 },
  { 35, 36, 37, 38, 39, 40, 41 },
  { 42, 43, 44, 45, 46, 47, 48 },
};

void setup() {
  Wire.begin();
  Serial.begin(9600);

  for (int i = 0; i < ROWS; i++) {
    pinMode(rows[i], OUTPUT);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(cols[i], INPUT_PULLUP);
  }
  for (int i = 0; i < COLS; i++) {
    digitalWrite(rows[i], 1);
  }
}


void loop() {

  for (int8_t i = 0; i < ROWS; i++) {
    digitalWrite(rows[i], 0);
    for (uint8_t j = 0; j < COLS; j++) {
      if (digitalRead(cols[j]) == 0) {
        if (pressed_buttons[i][j] == 0) {
          pressed_buttons[i][j] = 1;
          int dataToSend = 100 + keys[i][j];
          // Serial.println(dataToSend);
          Wire.beginTransmission(slaveAddress);
          Wire.write(dataToSend);
          Wire.endTransmission();
          delay(20);
        }
      } else if (pressed_buttons[i][j] == 1) {
        pressed_buttons[i][j] = 0;
        int dataToSend = keys[i][j];
        // Serial.println(dataToSend);
        Wire.beginTransmission(slaveAddress);
        Wire.write(dataToSend);
        Wire.endTransmission();
        delay(20);
      }
    }
    digitalWrite(rows[i], 1);
  }
}
