

#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)

const uint8_t ROWS = 8;
const uint8_t COLS = 9;


uint8_t rows[ROWS] = { 9, 10, 11, 13, A0, A1, A2, A3};
uint8_t cols[COLS] = { 0, 2, 3, 4, 5, 6, 7, 8, 12};

bool pressed_buttons[ROWS][COLS]
{ 
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

uint8_t keys[ROWS][COLS] = 
{
  {0, 1, 2, 3, 4, 5, 6, 7, 8},
  {9, 10, 11, 12, 13, 14, 15, 16, 17},
  {18, 19, 20, 21, 22, 23, 24, 25, 26},
  {27, 28, 29, 30, 31, 32, 33, 34, 35},
  {36, 37, 38, 39, 40, 41, 42, 43, 44},
  {45, 46, 47, 48, 49, 50, 51, 52, 53},
  {54, 55, 56, 57, 58, 59, 60, 61, 62},
  {63, 64, 65, 66, 67, 68, 69, 70, 71}
};

void setup() {
  Wire.begin();
  // Serial.begin(9600);

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
          // Serial.print("  pressed - ");
          // Serial.print(cols[j]);
          // Serial.print(" - ");
          // Serial.print(rows[i]);
          // Serial.print(" - ");
          // Serial.println(keys[i][j]);
          int dataToSend = 100 + keys[i][j];
          // Serial.println(dataToSend);
          Wire.beginTransmission(slaveAddress);
          Wire.write(dataToSend);
          Wire.endTransmission();
          delay(20);
        }
      } else if (pressed_buttons[i][j] == 1) {
        pressed_buttons[i][j] = 0;
          // Serial.print("unpressed - ");
          // Serial.print(cols[j]);
          // Serial.print(" - ");
          // Serial.print(rows[i]);
          // Serial.print(" - ");
          // Serial.println(keys[i][j]);
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
