
#include <Keyboard.h>

#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)

const uint8_t ROWS = 7;
const uint8_t COLS = 7;

uint8_t rows[ROWS] = {21,20,19,18,15,14,9};
uint8_t cols[COLS] = {8,7,6,5,4,16,30};

bool tg1_pressed = false;
const uint8_t tg1_button[] = {4, 1};
const uint8_t mo2_button[] = {6, 0};
const uint8_t mo2_button_left = 97; 
//mo(1) - [4][4]
//mo(2) - [5][4]

uint8_t keys[COLS][ROWS] = {
   {'a', '6','8', '9', '[', ']', 'a'},
   {'a', 'y', '7', 'o', '0', 'a', 'a'},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 'a'},
   {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 'a'},
   {KEY_F15, 0, 'm', ',', ';', '-', 'a'},
   {KEY_KP_ENTER, KEY_UP_ARROW, ' ', '.', '/', 'a', 'a'},
   {255, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 'a', 'a'}
};


uint8_t keys_mo1[COLS][ROWS] = {
   {'a', '6','8', '9', '[', ']', 'a'},
   {'a', 'y', '7', 'o', '0', 'a', 'a'},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 'a'},
   {KEY_DOWN_ARROW, 'n', '[', ']', 'l', KEY_F14, 'a'},
   {KEY_F15, 0, '{', '}', ';', '-', 'a'},
   {KEY_KP_ENTER, KEY_UP_ARROW, ' ', '.', '/', 'a', 'a'},
   {255, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 'a', 'a'}
};


uint8_t keys_mo2[COLS][ROWS] = {
   {'a', '6','8', '9', '[', ']', 'a'},
   {'a', 'y', '7', 'o', '0', 'a', 'a'},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 'a'},
   {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 'a'},
   {KEY_F15, 0, 'm', ',', ';', '-', 'a'},
   {KEY_KP_ENTER, KEY_UP_ARROW, ' ', '.', '/', 'a', 'a'},
   {255, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 'a', 'a'}
};

uint8_t left_keys[] = {
  '1', '2', '4', '5', KEY_F17, KEY_KP_ENTER, 0,
  KEY_ESC, 'w', '3', 't', KEY_F18, 0, 0,
  KEY_CAPS_LOCK, 's', 'e', 'g', 'b', 0, 0,
  KEY_LEFT_SHIFT, 'x', 'd', 'r', ' ', 0, 0,
  KEY_TAB, 'z', 'c', 'f', 254, 0, 0,
  KEY_F13, 'a', KEY_BACKSPACE, 'v', 0, 0, 0,
  KEY_LEFT_CTRL, 'q', KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F19, 0, 0
};

const uint8_t mo1_button = 32; 
bool mo1_pressed = false;
uint8_t left_keys_mo1[] = {
  KEY_F1, KEY_F2, KEY_F4, KEY_F5, KEY_F17, KEY_KP_ENTER, 'a',
  KEY_ESC, '_', KEY_F3, ',', KEY_F18, 'a', 'a',
  KEY_CAPS_LOCK, '-', '+', '.', 'b', 'a', 'a',
  KEY_LEFT_SHIFT, KEY_PAUSE, '(', '=', ' ', 'a', 'a',
  KEY_TAB, 'z', '\\', ')', 254, 'a', 'a',
  KEY_F13, '*', KEY_BACKSPACE, '`', 'a', 'a', 'a',
  KEY_LEFT_CTRL, 'q', KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F19, 'a', 'a'
};

uint8_t left_keys_mo2[] = {
  '1', '2', '4', '5', KEY_F17, KEY_KP_ENTER, 'a',
  KEY_ESC, 'w', '3', 't', KEY_F18, 'a', 'a',
  KEY_CAPS_LOCK, KEY_LEFT_ARROW, 'e', 'g', 'b', 'a', 'a',
  KEY_LEFT_SHIFT, 'x', KEY_UP_ARROW, 'r', ' ', 'a', 'a',
  KEY_TAB, 'z', KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 'a', 'a', 'a',
  KEY_F13, 'a', KEY_BACKSPACE, 'v', 'a', 'a', 'a',
  KEY_LEFT_CTRL, 'q', KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F19, 'a', 'a'
};

uint8_t left_keys_tg1[] = 
{
  0, 1, 2, 3, 't', 5, 6,
  7, 'q', 9, 'r', 'g', 12, 13,
  14, 'a', 16, 'f', 18, 19, 20,
  21, 22, 'w', 'e', 25, 26, 27,
  28, KEY_LEFT_CTRL, 's', 'd', 32, 33, 34,
  35, KEY_LEFT_SHIFT, 37, 38, 39, 40, 41,
  42, 43, 44, 45, 46, 47, 48,
};


bool pressed_buttons[COLS][ROWS]{
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0 }
};
//

void receiveData(int bytesReceived) {
    int dataReceived = Wire.read();  // Read the data sent by the Arduino Micro
    if (dataReceived < 50) {
        // Serial.print(0);
        // Serial.println(dataReceived);
        if (dataReceived == mo1_button){
            mo1_pressed = false;
            Keyboard.releaseAll();
        }
        // else if (dataReceived % 100 == mo2_button_left){
        //     pressed_buttons[mo2_button[0]][mo2_button[1] = false;
        //     Keyboard.releaseAll();
        // }
        else if (mo1_pressed){
            Keyboard.release(left_keys_mo1[dataReceived % 100]);
        }
        else if (pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            Keyboard.release(left_keys_mo2[dataReceived % 100]);
        }
        else if (tg1_pressed){
            // Serial.print("0 ");
            // Serial.println(left_keys_tg1[dataReceived % 100]);
            Keyboard.release(left_keys_tg1[dataReceived % 100]);
        }
        else{
            Keyboard.release(left_keys[dataReceived % 100]);
        }
    }
    else if (dataReceived >= 100 && dataReceived < 150) {
        // Serial.println(dataReceived);
        if (dataReceived == 100 + mo1_button){
            mo1_pressed = true;
        }
        // else if (dataReceived % 100 == mo2_button_left){
        //     pressed_buttons[mo2_button[0]][mo2_button[1] = true;
        //     Keyboard.releaseAll();
        // }
        //
        else if (mo1_pressed){
            Keyboard.press(left_keys_mo1[dataReceived % 100]);
        }
        else if (pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            Keyboard.press(left_keys_mo2[dataReceived % 100]);
        }
        else if (tg1_pressed){
            // Serial.print("1 ");
            // Serial.println(left_keys_tg1[dataReceived % 100]);
            Keyboard.press(left_keys_tg1[dataReceived % 100]);
        }
        else{
            Keyboard.press(left_keys[dataReceived % 100]);
        }
    }


    // Serial.println(dataReceived);
}

void setup() {

    Serial.begin(9600);
    Wire.begin(slaveAddress);
    Wire.onReceive(receiveData);

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
                    if (keys[i][j] != 255){
                        if (mo1_pressed){
                            Keyboard.press(keys_mo1[i][j]);
                        }
                        else if (pressed_buttons[mo2_button[0]][mo2_button[1]]){
                            Keyboard.press(keys_mo2[i][j]);
                        }
                        else{
                            Keyboard.press(keys[i][j]);
                        } 
                    }
                    pressed_buttons[i][j] = 1;;
                    // Serial.print(1);
                    // Serial.println(keys[i][j]);
                    delay(30);
                }
            }else if (pressed_buttons[i][j] == 1) {
                if (i == mo2_button[0] && j == mo2_button[1]){
                    Keyboard.releaseAll();
                }
                else if(i == tg1_button[0] && j == tg1_button[1]){
                    tg1_pressed = !tg1_pressed;
                    Keyboard.releaseAll();
                }
                else if (pressed_buttons[mo2_button[0]][mo2_button[1]]){
                    Keyboard.release(keys_mo2[i][j]);
                }
                else if (mo1_pressed){
                    Keyboard.release(keys_mo1[i][j]);
                }
                else{
                    Keyboard.release(keys[i][j]);
                } 
                // Serial.print(0);
                // Serial.println(keys[i][j]);
                pressed_buttons[i][j] = 0;
                 delay(30);
            }
        }
        
        digitalWrite(rows[i], 1);
    }

}
