
#include "HID-Project.h"
#include <Wire.h>
const int slaveAddress = 8;  // Address of the Arduino Nano (Slave)
// 2 - SDA, 3 - SCL

const uint8_t rows[] = { 9, 10, 16, 14, 15, 18, 19, 20 };
const uint8_t cols[] = { 4, 5, 6, 7, 8 };

const uint8_t ROWS = sizeof(rows);
const uint8_t COLS = sizeof(cols);

const uint8_t tg1_button[] = { 3, 3 };
const uint8_t mo2_button[] = { 5, 3 };
const uint8_t mo2_button_left = 19;  //raw receive data

const uint8_t fn_keys_list[] = {
  MEDIA_VOL_UP, MEDIA_VOL_DOWN, MEDIA_PLAY_PAUSE /*0xCD*/, 0x194 /*CONSUMER_EXPLORER	*/
};

const uint8_t F_keys_position_list[][2] = {{0,3},{1,2},{0,2},{0,1},{0,0},{1,0},{2,0}};

const uint8_t F_keys_position_list_left[] = { 0, 1, 2, 3, 4, 13, 18, 7, 25, 24 };

const uint8_t keys[ROWS][COLS] = {
  { KEY_0, KEY_9, KEY_8, KEY_6, 0 },
  { KEY_P, KEY_I, KEY_7, KEY_F15, 0 },
  { KEY_RIGHT_BRACE, KEY_O, KEY_U, KEY_Y, 0 },
  { KEY_SEMICOLON, KEY_K, KEY_J, KEY_F17, 0 },
  { KEY_QUOTE, KEY_L, KEY_H, KEY_UP_ARROW, 0 },
  { KEY_SLASH, KEY_PERIOD, KEY_M, 0, KEY_DOWN_ARROW },
  { KEY_F16, KEY_COMMA, KEY_N, KEY_RIGHT_ARROW, KEY_LEFT_ARROW },
  { KEY_DELETE, KEY_BACKSPACE, KEY_SPACE, KEY_ENTER, KEY_F18 }
};

const uint8_t keys_mo1[ROWS][COLS] = {
  { KEY_F10, KEY_F9, KEY_F8, KEY_F6, 0 },
  { KEY_F11, 0, KEY_F7, 0, 0 },
  { KEY_F12, 0, 0, 0, 0 },
  { '|', ']', '[', 0, 0 },
  { 0, '&', '@', 0, 0 },
  { 0, 0, '{', 0, 0 },
  { 0, '}', 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
 
// use Keyboard.press(KeyboardKeycode(keys_mo2[i][j]));
// uint8_t keys_mo2[ROWS][COLS] = {
//   { 0, 1, 2, 3, 4 },
//   { 5, 6, 7, 8, 9 },
//   { 10, 11, 12, 13, 14 },
//   { 15, 16, 17, 18, 19 },
//   { 20, 21, 22, 23, 24 },
//   { 25, 26, 27, 28, 29 },
//   { 30, 31, 32, 33, 34 },
//   { 35, 36, 37, 38, 39 }
// };
// {
//    {0, '6','8', '9', '[', ']', 0},
//    {0, 'y', '7', 'o', '0', 0, 0},
//    {KEY_LEFT_ARROW, 'h', 'u', 'i', 'p', '\'', 0},
//    {KEY_DOWN_ARROW, 'n', 'j', 'k', 'l', KEY_F14, 0},
//    {KEY_F15, 0, 'm', ',', ';', '-', 0},
//    {KEY_ENTER, KEY_UP_ARROW, KEY_SPACE, '.', '/', 0, 0},
//    {0, KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_F16, 0, 0}
// };


const uint8_t left_keys[] = {
  KEY_1, KEY_2, KEY_3, KEY_5, KEY_F20,
  KEY_ESC, KEY_W, KEY_4, KEY_T, 0,
  KEY_CAPS_LOCK, KEY_Q, KEY_E, KEY_F22, KEY_ENTER,
  KEY_LEFT_SHIFT, KEY_S, KEY_R, KEY_F21, 0,
  KEY_TAB, KEY_A, KEY_D, KEY_G, KEY_F23,
  KEY_F13, KEY_X, KEY_F, KEY_B, 0,
  KEY_Z, KEY_BACKSPACE, KEY_V, KEY_LEFT_ALT, 0,
  KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_C, KEY_SPACE, 0
};

const uint8_t mo1_button = 9;



const uint8_t left_keys_mo1[] = 
{
  KEY_F1, KEY_F2, KEY_F3, KEY_F5, KEY_F16,
  0, '_', KEY_F4, ',', 0,
  0, 0, '+', KEY_F14, 0,
  0, KEY_MINUS, '=', KEY_F15, 0,
  0, '*', '(', '.', 0,
  KEY_F13, MEDIA_PLAY_PAUSE, ')', 0, 0,
  CONSUMER_EXPLORER, 0, '`', 0, 0,
  0, 0, '\\', ' ', 0
};

const uint8_t left_keys_mo2[] =
{
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    KEY_LEFT_SHIFT, KEY_LEFT_ARROW, 0, 0, 0,
    0, KEY_A, KEY_UP_ARROW, 0, 0,
    0, MEDIA_VOL_DOWN, KEY_RIGHT_ARROW, 0, 0,
    0, KEY_BACKSPACE, MEDIA_VOL_UP, 0, 0,
    KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_DOWN_ARROW, KEY_SPACE, 0
  };


const uint8_t left_keys_tg1[] = {
  0, 1, 2, 3, 4,
  5, 6, 7, 8, 9,
  10, 11, 12, 13, 14,
  15, 16, 17, 18, 19,
  20, 21, 22, 23, 24,
  25, 26, 27, 28, 29,
  30, 31, 32, 33, 34,
  35, 36, 37, 38, 39
};
// {
//   0, 1, 2, 3, KEY_T, 5, 6,
//   KEY_ESC, KEY_Q, 9, KEY_R, KEY_G, 12, 13,
//   14, KEY_A, 16, KEY_F, 18, 19, 20,
//   21, KEY_X, KEY_W, KEY_E, KEY_SPACE, 26,         27,
//   28, KEY_LEFT_CTRL, KEY_S, KEY_D, 32, 33, 34,
//   35, KEY_LEFT_SHIFT, 37, KEY_V, 39, 40, 41,
//   42, 43, 44, 45, 46, 47, 48,
// };


