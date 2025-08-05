

#include "HID-Project.h"

#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)

#include <SD.h>
const int chipSelect = 10;
File myFile;
String filename = "keysData.txt";
bool SD_CORRECT = false;

const uint8_t ROWS = 8;
const uint8_t COLS = 9;

const uint8_t tg1_button = 63;
bool tg1_pressed = false;
const uint8_t mo1_button = 23;
bool mo1_pressed = false; 
const uint8_t mo2_buttons[] = {68, 54};
bool mo2_pressed = false; 

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


const uint16_t F_keys_list[] = {28, 29, 30, 21, 31, 27, 24, 33, 34, 35, 26, 53};
bool is_F_key(uint8_t n){
    for (auto k : F_keys_list){
        if (k == n){
            return true;
        }
    }
    return false;
};


uint8_t keys[COLS * ROWS] = 
{
  KEY_UP_ARROW, KEY_TAB, KEY_A, KEY_D, KEY_G, KEY_F19, KEY_H, KEY_L,
  KEY_QUOTE, KEY_ENTER, KEY_Z, KEY_BACKSPACE, KEY_V, KEY_LEFT_ALT, KEY_F15, KEY_SPACE,
  KEY_BACKSPACE, KEY_DELETE, KEY_F16, KEY_ESC, KEY_W, KEY_4, KEY_T, 23,
  KEY_7, KEY_I, KEY_P, KEY_6, KEY_1, KEY_2, KEY_3, KEY_5,
  KEY_F19, KEY_8, KEY_9, KEY_0, KEY_RIGHT_ARROW, KEY_F13, KEY_X, KEY_F,
  KEY_B, KEY_LEFT_ARROW, KEY_N, KEY_COMMA, KEY_F14, KEY_Y, KEY_CAPS_LOCK, KEY_Q,
  KEY_E, KEY_F17, KEY_ENTER, KEY_U, KEY_O, KEY_RIGHT_BRACE, 54, KEY_LEFT_CTRL,
  KEY_LEFT_GUI, KEY_C, KEY_SPACE, KEY_DOWN_ARROW, KEY_M, KEY_PERIOD, KEY_SLASH, 63,
  KEY_LEFT_SHIFT, KEY_S, KEY_R, KEY_F18, 68, KEY_J, KEY_K, KEY_SEMICOLON
};

uint8_t keys_mo1[COLS * ROWS] = 
{
  0, 1, '*', '(', '.', 5, '@', '&',
  8, KEY_ENTER, 0x194, 11, '`', 13, 14, 15,
  16, 17, 18, 19, '_', KEY_F4, ',', 23,
  KEY_F7, 25, KEY_F11, KEY_F6, KEY_F1, KEY_F2, KEY_F3, KEY_F5,
  32, KEY_F8, KEY_F9, KEY_F10, 36, 37, 0xCD, ')',
  40, 41, 42, '}', 44, 45, 46, 47,
  '+', 49, KEY_ENTER, 51, 52, KEY_F12, 54, 55,
  56, '\\', 58, 59, '{', 61, 62, 63,
  64, KEY_MINUS, '=', 67, 68, '[', ']', '|'
};

uint16_t left_keys_mo1[] = {
  KEY_F1, KEY_F2, KEY_F4, KEY_F5, KEY_F17, KEY_ENTER, 0,
  0, '_', KEY_F3, ',', KEY_F18, 0, 0,
  0, KEY_MINUS, '+', '.', 'b', 0, 0,
  0, 0xCD, '(', '=', ' ', 0, 0,  
  0, 0x194, '\\', ')', 0, 0, 0,
  KEY_F13, '*', 0, '`', 0, 0, 0,
  0, 'q', 0, 0, KEY_F19, 0, 0
};
uint8_t right_keys_mo1[COLS][ROWS] = {
   {0, KEY_F6, KEY_F8, KEY_F9, KEY_F11, KEY_F12, 0},
   {0, 'y', KEY_F7, 'o', KEY_F10, 0, 0},
   {KEY_LEFT_ARROW, '@', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', '[', ']', '&', KEY_F14, 0},
   {KEY_F15, 0, '{', '}', '|', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, ' ', '.', '/', 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};

uint8_t keys_mo2[COLS * ROWS] = 
{
  0, 1, 2, KEY_UP_ARROW, 4, 5, 6, 7,
  8, 9, 10, 11, 0xE9, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23,
  24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 0xEA, KEY_RIGHT_ARROW,
  40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, KEY_LEFT_CTRL,
  56, KEY_DOWN_ARROW, 58, 59, 60, 61, 62, 63,
  KEY_LEFT_SHIFT, KEY_LEFT_ARROW, 66, 67, 68, 69, 70, 71
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

uint8_t right_keys_mo2[COLS][ROWS] = {
   {0, '6','8', '9', '[', ']', 0},
   {0, 'y', '7', 'o', '0', 0, 0},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 0},
   {KEY_F15, 0, 'm', ',', ';', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, KEY_SPACE, '.', '/', 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};

uint8_t keys_tg1[] = {
  0, 1, 2, 3, KEY_T, 5, 6,
  KEY_ESC, KEY_Q, 9, KEY_R, KEY_G, 12, 13,
  14, KEY_A, 16, KEY_F, 18, 19, 20,
  21, KEY_X, KEY_W, KEY_E, KEY_SPACE, 26, 27,
  28, KEY_LEFT_CTRL, KEY_S, KEY_D, 32, 33, 34,
  35, KEY_LEFT_SHIFT, 37, KEY_V, 39, 40, 41,
  42, 43, 44, 45, 46, 47, 48,
};

bool pressed_buttons[COLS][ROWS]
{
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};


bool check_and_create_file()
{
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect)) {
        Serial.println("initialization failed!");
        return 0;
    }
    Serial.println("initialization done.");

    if (SD.exists(filename))
        Serial.println("'test.txt' exists.");
    else
    {
        Serial.println("'test.txt' doesn't exist.");
        Serial.println("Creating 'test.txt'...");
        myFile = SD.open(filename, FILE_WRITE);
        myFile.close();

        if (SD.exists(filename)){
        Serial.println("'test.txt' exists.");
        }
        else{
        Serial.println("'test.txt' doesn't exist.");
        return 0;
        }
    }
  
    myFile = SD.open(filename, FILE_WRITE);
    myFile.print('\n');
    myFile.close();
  
    return 1;
}

void receiveDataWriting(int bytesReceived) {

    int dataReceived = Wire.read();
    Serial.print("dataReceived: ");
    Serial.println(dataReceived);
    uint16_t button_index = dataReceived % 100;  //try to move to press section
    myFile = SD.open(filename, FILE_WRITE);

    if (dataReceived < 100) { //release button
        if (dataReceived == mo1_button){
            mo1_pressed = false;
            Serial.println("mo1 button was unpressed");
            Keyboard.releaseAll();
        }
        else if (dataReceived == mo2_buttons[0] || dataReceived == mo2_buttons[1]) {
            mo2_pressed = false;
            Serial.println("mo2 button was unpressed");
            Keyboard.releaseAll();
        }
        else if(dataReceived == tg1_button){
            tg1_pressed = !tg1_pressed;
        }
        else if (mo1_pressed){
            if (is_fn_key(keys_mo1[button_index])){
                Consumer.release(keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.release(KeyboardKeycode(keys_mo1[button_index]));
            }
            else{
                Keyboard.release(keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed){
            if (is_fn_key(keys_mo2[button_index])){
                Consumer.release(keys_mo2[button_index]);
            }
            else{
                Keyboard.release(KeyboardKeycode(keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            Keyboard.release(KeyboardKeycode(keys_tg1[button_index]));
        }
        else{
            Keyboard.release(KeyboardKeycode(keys[button_index]));
        }
    }
    else if (dataReceived >= 100 && dataReceived < 256) { //press button
        if (dataReceived == 100 + mo1_button){
            mo1_pressed = true;
            myFile.print(0);
            myFile.print(mo1_button);
            myFile.print(';');
            Serial.println("mo1 button was pressed");
        }
        else if (dataReceived == 100 + mo2_buttons[0] || dataReceived == 100 + mo2_buttons[1]){
            mo2_pressed = true;
            myFile.print(0);
            myFile.print(mo2_buttons[0]);
            myFile.print(';');
            Serial.println("mo2 button was pressed");
        }
        else if(dataReceived == 100 + tg1_button){
            myFile.print(0);
            myFile.print(tg1_button);
            myFile.print(';');
            return;
        }
        else if (mo1_pressed){
            myFile.print(1);
            myFile.print(button_index);
            myFile.print(';');
            if (is_fn_key(keys_mo1[button_index])){
                Consumer.press(keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.press(KeyboardKeycode(keys_mo1[button_index]));
            }
            else{
                Keyboard.press(keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed){
            myFile.print(2);
            myFile.print(button_index);
            myFile.print(';');
            if (is_fn_key(keys_mo2[button_index])){
                Consumer.press(keys_mo2[button_index]);
            }
             else{
                Keyboard.press(KeyboardKeycode(keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            myFile.print(3);
            myFile.print(button_index);
            myFile.print(';');
            Keyboard.press(KeyboardKeycode(keys_tg1[button_index]));
        }
        else{
            myFile.print(0);
            myFile.print(button_index);
            myFile.print(';');
            Keyboard.press(KeyboardKeycode(keys[button_index]));
        }
    }
    myFile.close();
}

void receiveData(int bytesReceived) {

    int dataReceived = Wire.read();
    Serial.print("dataReceived: ");
    Serial.println(dataReceived);
    
    uint16_t button_index = dataReceived % 100;  //try to move to press section
    if (dataReceived < 100) { //release button
        if (dataReceived == mo1_button){
            mo1_pressed = false;
            Serial.println("mo1 button was unpressed");
            Keyboard.releaseAll();
        }
        else if (dataReceived == mo2_buttons[0] || dataReceived == mo2_buttons[1]) {
            mo2_pressed = false;
            Serial.println("mo2 button was unpressed");
            Keyboard.releaseAll();
        }
        else if(dataReceived == tg1_button){
            tg1_pressed = !tg1_pressed;
        }
        else if (mo1_pressed){
            if (is_fn_key(keys_mo1[button_index])){
                Consumer.release(keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.release(KeyboardKeycode(keys_mo1[button_index]));
            }
            else{
                Keyboard.release(keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed){
            if (is_fn_key(keys_mo2[button_index])){
                Consumer.release(keys_mo2[button_index]);
            }
            else{
                Keyboard.release(KeyboardKeycode(keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            Keyboard.release(KeyboardKeycode(keys_tg1[button_index]));
        }
        else{
            Keyboard.release(KeyboardKeycode(keys[button_index]));
        }
    }
    else if (dataReceived >= 100 && dataReceived < 256) { //press button
        if (dataReceived == 100 + mo1_button){
            mo1_pressed = true;
            Serial.println("mo1 button was pressed");
        }
        else if (dataReceived == 100 + mo2_buttons[0] || dataReceived == 100 + mo2_buttons[1]){
            mo2_pressed = true;
            Serial.println("mo2 button was pressed");
        }
        else if(dataReceived == 100 + tg1_button){
            return;
        }
        else if (mo1_pressed){
            if (is_fn_key(keys_mo1[button_index])){
                Consumer.press(keys_mo1[button_index]);
            }
            else if (is_F_key(button_index)){
                Keyboard.press(KeyboardKeycode(keys_mo1[button_index]));
            }
            else{
                Keyboard.press(keys_mo1[button_index]);
            }
        }
        else if (mo2_pressed){
            if (is_fn_key(keys_mo2[button_index])){
                Consumer.press(keys_mo2[button_index]);
            }
             else{
                Keyboard.press(KeyboardKeycode(keys_mo2[button_index]));
            }
        }
        else if (tg1_pressed){
            Keyboard.press(KeyboardKeycode(keys_tg1[button_index]));
        }
        else{
            Keyboard.press(KeyboardKeycode(keys[button_index]));
        }
    }

}

void readFile(){  // заново открываем файл для чтения:
    myFile = SD.open(filename);
    if (myFile) {
        Serial.println("'test.txt':");

        while (myFile.available()) {
        Serial.write(myFile.read());
        }
        myFile.close();
    } else {
        Serial.println("error opening 'test.txt'");
    }
}
void setup() {

    Serial.begin(9600);

    if(check_and_create_file()){
        SD_CORRECT = true;
        Serial.println("SD_correct is true");
    }
    else{
        SD_CORRECT = false;
        Serial.println("SD_correct is false");
    }   
    Wire.begin(slaveAddress);

    if(SD_CORRECT){
        Wire.onReceive(receiveDataWriting);
        Serial.println("SD is CORRECT");
    }
    else{
        Wire.onReceive(receiveData);
        Serial.println("SD is not CORRECT");
    }

    Keyboard.begin();
    Consumer.begin();
    Serial.println("end setup");

}

void loop() {
    if(Serial.available()){
        String com = Serial.readString();
        Serial.println("string com: ");
        if (com == "read"){
            readFile();
        }
    }
}

