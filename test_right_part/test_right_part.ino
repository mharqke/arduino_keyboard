/*
#define SHIFT_MASK		0x40
#define KEYCODE_TYPE		uint8_t

#define KEY_MEDIA_VOLUME_INC    0x01
#define KEY_MEDIA_VOLUME_DEC    0x02
#define KEY_MEDIA_MUTE          0x04
#define KEY_MEDIA_PLAY_PAUSE    0x08
#define KEY_MEDIA_NEXT_TRACK    0x10
#define KEY_MEDIA_PREV_TRACK    0x20
#define KEY_MEDIA_STOP          0x40
#define KEY_MEDIA_EJECT         0x80

#define ASCII_20	KEY_SPACE				// 32  
#define ASCII_21	KEY_1 + SHIFT_MASK			// 33 !
#define ASCII_22	KEY_QUOTE + SHIFT_MASK			// 34 "
#define ASCII_23	KEY_3 + SHIFT_MASK			// 35 #
#define ASCII_24	KEY_4 + SHIFT_MASK			// 36 $
#define ASCII_25	KEY_5 + SHIFT_MASK			// 37 %
#define ASCII_26	KEY_7 + SHIFT_MASK			// 38 &
#define ASCII_27	KEY_QUOTE				// 39 '  
#define ASCII_28	KEY_9 + SHIFT_MASK			// 40 ( 
#define ASCII_29	KEY_0 + SHIFT_MASK			// 41 )
#define ASCII_2A	KEY_8 + SHIFT_MASK			// 42 *
#define ASCII_2B	KEY_EQUAL + SHIFT_MASK			// 43 +
#define ASCII_2C	KEY_COMMA				// 44 ,
#define ASCII_2D	KEY_MINUS				// 45 -
#define ASCII_2E	KEY_PERIOD				// 46 .
#define ASCII_2F	KEY_SLASH				// 47 /
#define ASCII_30	KEY_0					// 48 0
#define ASCII_31	KEY_1					// 49 1
#define ASCII_32	KEY_2					// 50 2
#define ASCII_33	KEY_3					// 51 3
#define ASCII_34	KEY_4					// 52 4
#define ASCII_35	KEY_5					// 53 5
#define ASCII_36	KEY_6					// 54 6
#define ASCII_37	KEY_7					// 55 7
#define ASCII_38	KEY_8					// 55 8
#define ASCII_39	KEY_9					// 57 9
#define ASCII_3A	KEY_SEMICOLON + SHIFT_MASK		// 58 :
#define ASCII_3B	KEY_SEMICOLON				// 59 ;
#define ASCII_3C	KEY_COMMA + SHIFT_MASK			// 60 <
#define ASCII_3D	KEY_EQUAL				// 61 =
#define ASCII_3E	KEY_PERIOD + SHIFT_MASK			// 62 >
#define ASCII_3F	KEY_SLASH + SHIFT_MASK			// 63 ?
#define ASCII_40	KEY_2 + SHIFT_MASK			// 64 @
#define ASCII_41	KEY_A + SHIFT_MASK			// 65 A
#define ASCII_42	KEY_B + SHIFT_MASK			// 66 B
#define ASCII_43	KEY_C + SHIFT_MASK			// 67 C
#define ASCII_44	KEY_D + SHIFT_MASK			// 68 D
#define ASCII_45	KEY_E + SHIFT_MASK			// 69 E
#define ASCII_46	KEY_F + SHIFT_MASK			// 70 F
#define ASCII_47	KEY_G + SHIFT_MASK			// 71 G
#define ASCII_48	KEY_H + SHIFT_MASK			// 72 H
#define ASCII_49	KEY_I + SHIFT_MASK			// 73 I
#define ASCII_4A	KEY_J + SHIFT_MASK			// 74 J
#define ASCII_4B	KEY_K + SHIFT_MASK			// 75 K
#define ASCII_4C	KEY_L + SHIFT_MASK			// 76 L
#define ASCII_4D	KEY_M + SHIFT_MASK			// 77 M
#define ASCII_4E	KEY_N + SHIFT_MASK			// 78 N
#define ASCII_4F	KEY_O + SHIFT_MASK			// 79 O
#define ASCII_50	KEY_P + SHIFT_MASK			// 80 P
#define ASCII_51	KEY_Q + SHIFT_MASK			// 81 Q
#define ASCII_52	KEY_R + SHIFT_MASK			// 82 R
#define ASCII_53	KEY_S + SHIFT_MASK			// 83 S
#define ASCII_54	KEY_T + SHIFT_MASK			// 84 T
#define ASCII_55	KEY_U + SHIFT_MASK			// 85 U
#define ASCII_56	KEY_V + SHIFT_MASK			// 86 V
#define ASCII_57	KEY_W + SHIFT_MASK			// 87 W
#define ASCII_58	KEY_X + SHIFT_MASK			// 88 X
#define ASCII_59	KEY_Y + SHIFT_MASK			// 89 Y
#define ASCII_5A	KEY_Z + SHIFT_MASK			// 90 Z
#define ASCII_5B	KEY_LEFT_BRACE				// 91 [
#define ASCII_5C	KEY_BACKSLASH				// 92 
#define ASCII_5D	KEY_RIGHT_BRACE				// 93 ]
#define ASCII_5E	KEY_6 + SHIFT_MASK			// 94 ^
#define ASCII_5F	KEY_MINUS + SHIFT_MASK			// 95 _
#define ASCII_60	KEY_TILDE				// 96 `
#define ASCII_61	KEY_A					// 97 a
#define ASCII_62	KEY_B					// 98 b
#define ASCII_63	KEY_C					// 99 c
#define ASCII_64	KEY_D					// 100 d
#define ASCII_65	KEY_E					// 101 e
#define ASCII_66	KEY_F					// 102 f
#define ASCII_67	KEY_G					// 103 g
#define ASCII_68	KEY_H					// 104 h
#define ASCII_69	KEY_I					// 105 i
#define ASCII_6A	KEY_J					// 106 j
#define ASCII_6B	KEY_K					// 107 k
#define ASCII_6C	KEY_L					// 108 l
#define ASCII_6D	KEY_M					// 109 m
#define ASCII_6E	KEY_N					// 110 n
#define ASCII_6F	KEY_O					// 111 o
#define ASCII_70	KEY_P					// 112 p
#define ASCII_71	KEY_Q					// 113 q
#define ASCII_72	KEY_R					// 114 r
#define ASCII_73	KEY_S					// 115 s
#define ASCII_74	KEY_T					// 116 t
#define ASCII_75	KEY_U					// 117 u
#define ASCII_76	KEY_V					// 118 v
#define ASCII_77	KEY_W					// 119 w
#define ASCII_78	KEY_X					// 120 x
#define ASCII_79	KEY_Y					// 121 y
#define ASCII_7A	KEY_Z					// 122 z
#define ASCII_7B	KEY_LEFT_BRACE + SHIFT_MASK		// 123 {
#define ASCII_7C	KEY_BACKSLASH + SHIFT_MASK		// 124 |
#define ASCII_7D	KEY_RIGHT_BRACE + SHIFT_MASK		// 125 }
#define ASCII_7E	KEY_TILDE + SHIFT_MASK			// 126 ~
#define ASCII_7F	KEY_BACKSPACE				// 127
// #include <Keyboard.h>
*/

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
const uint16_t F_keys_list[] = {
  KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 
  KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24
};

bool is_F_key(uint8_t n){
    for (auto k : F_keys_list){
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
   {0, '6','8', '9', '[', ']', 0},
   {0, 'y', '7', 'o', '0', 0, 0},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', '[', ']', 'l', KEY_F14, 0},
   {KEY_F15, 0, '{', '}', ';', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, ' ', '.', '/', 0, 0},
   {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
};

uint8_t keys_mo2[COLS][ROWS] = {
   {0, '6','8', '9', '[', ']', 0},
   {0, 'y', '7', 'o', '0', 0, 0},
   {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 0},
   {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 0},
   {KEY_F15, 0, 'm', ',', ';', '-', 0},
   {KEY_ENTER, KEY_UP_ARROW, ' ', '.', '/', 0, 0},
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
  0, 0xCD, '(', '=', KEY_SPACE, 0, 0,
  0, 0x194, '\\', ')', 0, 0, 0,
  KEY_F13, '*', 0, '`', 0, 0, 0,
  0, 'q', 0, 0, KEY_F19, 0, 0
};


uint8_t left_keys_mo2[] = {
  '1', '2', '4', '5', KEY_F17, KEY_ENTER, 0,
  KEY_ESC, 'w', '3', 't', KEY_F18, 0, 0,
  KEY_CAPS_LOCK, KEY_LEFT_ARROW, 'e', 'g', 'b', 0, 0,
  KEY_LEFT_SHIFT, 0xEA, KEY_UP_ARROW, 'r', ' ', 0, 0,
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
            if (is_fn_key(left_keys_mo1[dataReceived % 100])){
                Consumer.release(left_keys_mo1[dataReceived % 100]);
            }
            else if (is_F_key(left_keys_mo1[dataReceived % 100])){
                Keyboard.release(KeyboardKeycode(left_keys_mo1[dataReceived % 100]));
            }
            else{
                Keyboard.release(left_keys_mo1[dataReceived % 100]);
            }
        }
        else if (mo2_pressed || pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            if (is_fn_key(left_keys_mo2[dataReceived % 100])){
                Consumer.release(left_keys_mo2[dataReceived % 100]);
            }
            else{
                Keyboard.release(KeyboardKeycode(left_keys_mo2[dataReceived % 100]));
            }
        }
        else if (tg1_pressed){
            Keyboard.release(KeyboardKeycode(left_keys_tg1[dataReceived % 100]));
        }
        else{
            Keyboard.release(KeyboardKeycode(left_keys[dataReceived % 100]));
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
            if (is_fn_key(left_keys_mo1[dataReceived % 100])){
                Consumer.press(left_keys_mo1[dataReceived % 100]);
            }
            else if (is_F_key(left_keys_mo1[dataReceived % 100])){
                Keyboard.press(KeyboardKeycode(left_keys_mo1[dataReceived % 100]));
            }
            else{
                Keyboard.press(left_keys_mo1[dataReceived % 100]);
            }
        }
        else if (mo2_pressed || pressed_buttons[mo2_button[0]][mo2_button[1]] == 1){
            if (is_fn_key(left_keys_mo2[dataReceived % 100])){
                Consumer.press(left_keys_mo2[dataReceived % 100]);
            }
             else{
                Keyboard.press(KeyboardKeycode(left_keys_mo2[dataReceived % 100]));
            }
        }
        else if (tg1_pressed){
            Keyboard.press(KeyboardKeycode(left_keys_tg1[dataReceived % 100]));
        }
        else{
            Keyboard.press(KeyboardKeycode(left_keys[dataReceived % 100]));
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
//   delay(5000);fjhjlh
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