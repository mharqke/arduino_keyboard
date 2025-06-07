

#include "HID-Project.h"

#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)



const uint8_t ROWS = 7;
const uint8_t COLS = 7;

uint8_t rows[ROWS] = {21,20,19,18,15,14,9};
uint8_t cols[COLS] = {8,7,6,5,4,16,30};

bool tg1_pressed = false;
const uint8_t tg1_button[] = {4, 1};
const uint8_t mo2_button[] = {6, 0};
const uint8_t mo2_button_left = 39; //raw receive data 
bool mo2_pressed = false; 
//mo(1) - [4][4]
//mo(2) - [5][4]
const uint16_t fn_keys_list[] = {
  MEDIA_VOL_UP, MEDIA_VOL_DOWN, 0xCD,0x194
};

bool is_fn_key(uint16_t n){
    for (auto k : fn_keys_list){
        if (k == n){
          return true;
        }
    }
    return false;
}


bool is_F_key(uint8_t n){
    static uint16_t F_keys_position_list[] = {0,1,2,3,4,9,11,35,46};
    for (auto k : F_keys_position_list){
        if (k == n){
            return true;
        }
    }
    return false;
};

uint8_t keys[COLS][ROWS] = {
   {0, KEY_6, KEY_8, KEY_9, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, 0},
   {0, KEY_Y, KEY_7, KEY_O, KEY_0, 0, 0},
   {KEY_LEFT_ARROW, KEY_H, KEY_U, KEY_I, KEY_P, KEY_QUOTE, 0},
   {KEY_DOWN_ARROW, KEY_N, KEY_J, KEY_K, KEY_L, KEY_F14, 0},
   {KEY_F15, 0, KEY_M, KEY_COMMA, KEY_SEMICOLON, KEY_MINUS, 0},
   {KEY_ENTER, KEY_UP_ARROW, KEY_SPACE, KEY_PERIOD, KEY_SLASH, 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};

uint8_t keys_mo1[COLS][ROWS] = {
   {0, KEY_F6, KEY_F8, KEY_F9, '[', ']', 0},
   {0, 'y', KEY_F7, 'o', KEY_F10, 0, 0},
   {KEY_LEFT_ARROW, '@', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', '[', ']', '&', KEY_F14, 0},
   {KEY_F15, 0, '{', '}', '|', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, ' ', '.', '/', 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};

uint8_t keys_mo2[COLS][ROWS] = {
   {0, '6','8', '9', '[', ']', 0},
   {0, 'y', '7', 'o', '0', 0, 0},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 0},
   {KEY_F15, 0, 'm', ',', ';', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, KEY_SPACE, '.', '/', 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};


uint8_t left_keys[] = {
  KEY_1, KEY_2, KEY_4, KEY_5, KEY_F17, KEY_ENTER, 0,
  KEY_ESC, KEY_W, KEY_3, KEY_T, KEY_F18, 0, 0,
  KEY_CAPS_LOCK, KEY_S, KEY_E, KEY_G, KEY_B, 0, 0,
  KEY_LEFT_SHIFT, KEY_X, KEY_D, KEY_R, KEY_SPACE, 0, 0,
  KEY_TAB, KEY_Z, KEY_C, KEY_F, 0, 0, 0,
  KEY_F13, KEY_A, KEY_BACKSPACE, KEY_V, 0, 0, 0,
  KEY_LEFT_CTRL, KEY_Q, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F19, 0, 0
};

const uint16_t mo1_button = 32; 
bool mo1_pressed = false;
// 0xCD - pause
// 0x194 - file
uint16_t left_keys_mo1[] = {
  KEY_F1, KEY_F2, KEY_F4, KEY_F5, KEY_F17, KEY_ENTER, 0,
  0, '_', KEY_F3, ',', KEY_F18, 0, 0,
  0, KEY_MINUS, '+', '.', 'b', 0, 0,
  0, 0xCD, '(', '=', ' ', 0, 0,
  0, 0x194, '\\', ')', 0, 0, 0,
  KEY_F13, '*', 0, '`', 0, 0, 0,
  0, 'q', 0, 0, KEY_F19, 0, 0
};


uint8_t left_keys_mo2[] = {
  '1', '2', '4', '5', KEY_F17, KEY_ENTER, 0,
  KEY_ESC, 'w', '3', 't', KEY_F18, 0, 0,
  KEY_CAPS_LOCK, KEY_LEFT_ARROW, 'e', 'g', 'b', 0, 0,
  KEY_LEFT_SHIFT, 0xEA, KEY_UP_ARROW, 'r', KEY_SPACE, 0, 0,
  KEY_TAB, 'z', KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 0, 0, 0,
  KEY_F13, KEY_A, KEY_BACKSPACE, 0xE9, 0, 0, 0,
  KEY_LEFT_CTRL, 'q', KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_F19, 0, 0
};

uint8_t left_keys_tg1[] = {
  0, 1, 2, 3, KEY_T, 5, 6,
  7, KEY_Q, 9, KEY_R, KEY_G, 12, 13,
  14, KEY_A, 16, KEY_F, 18, 19, 20,
  21, 22, KEY_W, KEY_E, 25, 26, 27,
  28, KEY_LEFT_CTRL, KEY_S, KEY_D, 32, 33, 34,
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

void receiveData(int bytesReceived) {
    int dataReceived = Wire.read();
    Serial.print("raw_data: ");
    Serial.println(dataReceived);
    uint16_t button_index = dataReceived % 100;
    if (dataReceived < 50) {
        if (dataReceived == mo1_button){
            mo1_pressed = false;
            Keyboard.releaseAll();
        }
        else if (dataReceived == mo2_button_left) {
            mo2_pressed = false;
            Keyboard.releaseAll();
        }
        else if (mo1_pressed){
            if (is_fn_key(left_keys_mo1[button_index])){
                Consumer.release(left_keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.release(KeyboardKeycode(left_keys_mo1[button_index]));
            }
            else{
                Keyboard.release(left_keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed || pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            if (is_fn_key(left_keys_mo2[button_index])){
                Consumer.release(left_keys_mo2[button_index]);
            }
            else{
                Keyboard.release(KeyboardKeycode(left_keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            Keyboard.release(KeyboardKeycode(left_keys_tg1[button_index]));
        }
        else{
            Keyboard.release(KeyboardKeycode(left_keys[button_index]));
        }
    }
    else if (dataReceived >= 100 && dataReceived < 150) {
        if (dataReceived == 100 + mo1_button){
            mo1_pressed = true;
        }
        else if (dataReceived == 100 + mo2_button_left){
            mo2_pressed = true;
        }
        else if (mo1_pressed){
            if (is_fn_key(left_keys_mo1[button_index])){
                Consumer.press(left_keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.press(KeyboardKeycode(left_keys_mo1[button_index]));
            }
            else{
                Keyboard.press(left_keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed || pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            if (is_fn_key(left_keys_mo2[button_index])){
                Consumer.press(left_keys_mo2[button_index]);
            }
             else{
                Keyboard.press(KeyboardKeycode(left_keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            Keyboard.press(KeyboardKeycode(left_keys_tg1[button_index]));
        }
        else{
            Keyboard.press(KeyboardKeycode(left_keys[button_index]));
        }
    }

}

void setup() {

    Serial.begin(9600);
    Wire.begin(slaveAddress);
    Wire.onReceive(receiveData);

    Keyboard.begin();
    Consumer.begin();
    
    for (int i = 0; i < ROWS; i++) {
        pinMode(rows[i], OUTPUT);
    }
    for (int i = 0; i < COLS; i++) {
        pinMode(cols[i], INPUT_PULLUP);
    }
    for (int i = 0; i < COLS; i++) {
        digitalWrite(rows[i], 1);
    }
// 
}

void loop() {
        
    for (int8_t i = 0; i < ROWS; i++) {
        digitalWrite(rows[i], 0);
        for (uint8_t j = 0; j < COLS; j++) {
            if (digitalRead(cols[j]) == 0) {
                Serial.print(i);
                Serial.print(" - ");
                Serial.println(j);
                if (pressed_buttons[i][j] == 0) {
                    if (mo1_pressed){
                        Keyboard.press((keys_mo1[i][j]));
                    }
                    else if (pressed_buttons[mo2_button[0]][mo2_button[1]]){
                        Keyboard.press(KeyboardKeycode(keys_mo2[i][j]));
                    }
                    else{
                        Keyboard.press(KeyboardKeycode(keys[i][j]));
                    } 
                    pressed_buttons[i][j] = 1;;
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
                    Keyboard.release(KeyboardKeycode(keys_mo2[i][j]));
                }
                else if (mo1_pressed){
                    Keyboard.release((keys_mo1[i][j]));
                }
                else{
                    Keyboard.release(KeyboardKeycode(keys[i][j]));
                } 
                pressed_buttons[i][j] = 0;
                 delay(30);
            }
        }
        
        digitalWrite(rows[i], 1);
    }

}














