
#include "right_part.h"

bool mo1_pressed = false;
bool mo2_pressed = false;
bool tg1_pressed = false;

const uint8_t SOUND_PIN = A3;
const uint8_t sound_val = 135;
const uint8_t sound_button_i = 0;
const uint8_t sound_button_j = 3;
const uint8_t sound_up_button_on_i = 1;
const uint8_t sound_up_button_on_j = 2;
const uint8_t sound_down_button_on_i = 0;
const uint8_t sound_down_button_on_j = 2;
const uint8_t sound_up_button_off_i = 0;
const uint8_t sound_up_button_off_j = 1;
const uint8_t sound_down_button_off_i = 0;
const uint8_t sound_down_button_off_j = 0;
uint8_t sound_time_on = 30;
uint8_t sound_time_off = 200;
uint8_t sound_timer = 0;
uint8_t sound_pass_timer = 0;
bool sound_press = 0;
bool sound_flag = 0;


// #define SEARCH(arr, body, size) {\
//   for(i = 0; i < size; i++)\
//     if (body)\
//       return true;\
//   return false;\
// }

// bool is_fn_key(uint8_t n){
//   register int i = 0;
//   SEARCH(fn_keys_list, (fn_keys_list[i] == n), sizeof(fn_keys_list));
// }

// bool is_F_key_left(uint8_t n) {
//   register int i = 0;
//   SEARCH(F_keys_position_list_left, (F_keys_position_list_left[i] == n), sizeof(F_keys_position_list_left));
// };

// bool is_F_key(uint8_t n, uint8_t m) {
//   register int i = 0;
//   SEARCH(F_keys_position_list, (F_keys_position_list[i][0] == n and F_keys_position_list[i][1] == m), sizeof(F_keys_position_list));
// };

bool is_fn_key(uint16_t n) {
  for (auto key : fn_keys_list)
    if (key == n)
      return true;
  return false;
}

bool is_F_key_left(uint8_t n) {
  for (auto key : F_keys_position_list_left)
    if (key == n)
      return true;
  return false;
};

bool is_F_key(uint8_t n, uint8_t m) {
  for (auto key : F_keys_position_list)
    if (key[0] == n and key[1] == m)
      return true;
  return false;
};






bool pressed_buttons[ROWS][COLS] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};



void receiveData(int bytesReceived) {
  int dataReceived = Wire.read();
  uint16_t button_index = dataReceived % 100;
  // // Serial.print(left_keys[button_index]);
  // Serial.print(" - ");
  // Serial.print("raw_data: ");
  // Serial.println(dataReceived);

  if (dataReceived < 50) {  // -------------------------release-------------------------

    if (dataReceived == mo1_button) {  // mo1 was released
      // Serial.println("left mo1 unpressed");
      mo1_pressed = false;
      Keyboard.releaseAll();
      Consumer.releaseAll();
      memset(pressed_buttons, 0, sizeof(pressed_buttons));
    }

    else if (dataReceived == mo2_button_left) {  // mo2 was released
      // Serial.print("left mo2 unpressed - ");
      // Serial.println(mo2_pressed);
      mo2_pressed = false;
      Keyboard.releaseAll();
      Consumer.releaseAll();
      memset(pressed_buttons, 0, sizeof(pressed_buttons));
    }

    else if (mo1_pressed) {  // mo1 release
      if (is_fn_key(left_keys_mo1[button_index])) {
        Consumer.release(left_keys_mo1[button_index]);
        // Serial.println("key is fn");
      } else if (is_F_key_left(button_index)) {
        Keyboard.release(KeyboardKeycode(left_keys_mo1[button_index]));
        // Serial.println("key is f");
      } else {
        // Serial.print("left mo1 button: ");
        // Serial.println(left_keys_mo1[button_index]);
        Keyboard.release(left_keys_mo1[button_index]);
      }
    }

    else if (mo2_pressed || pressed_buttons[mo2_button[0]][mo2_button[1]] == 1) {  // mo2 release
      if (is_fn_key(left_keys_mo2[button_index])) {
        Consumer.release(left_keys_mo2[button_index]);
      }
      // else if (tg1_pressed){
      //     Keyboard.release(KeyboardKeycode(left_keys_tg1[button_index]));
      // }
      else {
        // Serial.print("release mo2 button: ");
        // Serial.println(left_keys_mo2[button_index]);
        Keyboard.release(KeyboardKeycode(left_keys_mo2[button_index]));
      }
    }

    else {  // common layout release
      Keyboard.release(KeyboardKeycode(left_keys[button_index]));
    }
  }

  else if (dataReceived >= 100 and dataReceived < 150) {  // -------------------------press-------------------------

    if (dataReceived == 100 + mo1_button) {  // mo1 was pressed
      // Serial.println("mo1 pressed");
      mo1_pressed = true;
      Keyboard.releaseAll();
      Consumer.releaseAll();
      memset(pressed_buttons, 0, sizeof(pressed_buttons));

    }

    else if (dataReceived == 100 + mo2_button_left) {  // mo2 was pressed
      // Serial.println("mo2 pressed");
      mo2_pressed = true;
      Keyboard.releaseAll();
      Consumer.releaseAll();
      memset(pressed_buttons, 0, sizeof(pressed_buttons));
    }

    else if (mo1_pressed) {  // mo1 press
      if (is_fn_key(left_keys_mo1[button_index])) {
        Consumer.press(left_keys_mo1[button_index]);
        // Serial.println("key is fn");
      } else if (is_F_key_left(button_index)) {
        Keyboard.press(KeyboardKeycode(left_keys_mo1[button_index]));
        // Serial.println("key is f");
      } else {
        // Serial.print("mo1 button: ");
        // Serial.println(left_keys_mo1[button_index]);
        Keyboard.press(left_keys_mo1[button_index]);
      }
    }

    else if (mo2_pressed or pressed_buttons[mo2_button[0]][mo2_button[1]] == 1) {  // mo2 press
      if (is_fn_key(left_keys_mo2[button_index])) {
        Consumer.press(left_keys_mo2[button_index]);
      }
      // else if (tg1_pressed){
      //     Keyboard.press(KeyboardKeycode(left_keys_tg1[button_index]));
      // }
      else {
        // Serial.print("press mo2 button: ");
        // Serial.println(left_keys_mo2[button_index]);
        Keyboard.press(KeyboardKeycode(left_keys_mo2[button_index]));
      }
    }

    else {  // common layout press
      Keyboard.press(KeyboardKeycode(left_keys[button_index]));
    }

    sound_press = 1;
  }
}

void setup() {

  // Serial.begin(9600);
  Wire.begin(slaveAddress);
  Wire.onReceive(receiveData);

  Keyboard.begin();
  Consumer.begin();

  pinMode(SOUND_PIN, OUTPUT);
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

        if (pressed_buttons[i][j] == 0) {  //------------------------press------------------------
          // Serial.print("press i - j: ");
          // Serial.print(i);
          // Serial.print(" - ");
          // Serial.print(j);
          // Serial.print("; keys[i][j]: ");
          // Serial.println(keys[i][j]);

          if (i == mo2_button[0] and j == mo2_button[1]) {  // mo2 was pressed
            Keyboard.releaseAll();
            Consumer.releaseAll();
            memset(pressed_buttons, 0, sizeof(pressed_buttons));
            // Serial.println("right mo2 press");
          }

          else if (mo1_pressed) {  // mo1 press
            if (sound_button_i == i and sound_button_j == j){
              sound_flag = !sound_flag;
            } else if(sound_up_button_on_i == i and sound_up_button_on_j == j){
              if (sound_time_on < 245) sound_time_on += 5;
              // Serial.print("sound_time_on:");
              // Serial.println(sound_time_on);
            } else if(sound_down_button_on_i == i and sound_down_button_on_j == j){
              if (sound_time_on > 9) sound_time_on -= 5;
              // Serial.print("sound_time_on:");
              // Serial.println(sound_time_on);
            } else if(sound_up_button_off_i == i and sound_up_button_off_j == j){
              if (sound_time_off < 245) sound_time_off += 5;
              // Serial.print("sound_time_off:");
              // Serial.println(sound_time_off);
            } else if(sound_down_button_off_i == i and sound_down_button_off_j == j){
              if (sound_time_off > 9) sound_time_off -= 5;
              // Serial.print("sound_time_off:");
              // Serial.println(sound_time_off);
            } else if (is_F_key(i, j)) {
              Keyboard.press(KeyboardKeycode(keys_mo1[i][j]));
              // Serial.println("key is f");
            } else {
              // Serial.print("press mo1: ");
              // Serial.println(keys_mo1[i][j]);
              Keyboard.press((keys_mo1[i][j]));
            }
          } else {  // common layout press
            Keyboard.press(KeyboardKeycode(keys[i][j]));
          }
          sound_press = 1;
          pressed_buttons[i][j] = 1;
          delay(30);
          break;
        }

      } else if (pressed_buttons[i][j] == 1) {  //------------------------release------------------------
        // Serial.print("press i - j: ");
        // Serial.print(i);
        // Serial.print(" - ");
        // Serial.print(j);
        // Serial.print("; keys[i][j]: ");
        // Serial.println(keys[i][j]);

        if (i == mo2_button[0] and j == mo2_button[1]) {  // mo2 was released
          Keyboard.releaseAll();
          Consumer.releaseAll();
          memset(pressed_buttons, 0, sizeof(pressed_buttons));
          // Serial.println("right mo2 release");
        }

        else if (i == tg1_button[0] && j == tg1_button[1]) {  // tg1 was pressed
          tg1_pressed = !tg1_pressed;
          Keyboard.releaseAll();
          Consumer.releaseAll();
          memset(pressed_buttons, 0, sizeof(pressed_buttons));
          // Serial.print("tg1 was pressed - ");
          // Serial.println(tg1_pressed);
        } else if (mo1_pressed) {
          if (is_F_key(i, j)) {
            Keyboard.release(KeyboardKeycode(keys_mo1[i][j]));
          } else {
            Keyboard.release((keys_mo1[i][j]));
          }
        }

        else {  // common layout release
          Keyboard.release(KeyboardKeycode(keys[i][j]));
        }

        pressed_buttons[i][j] = 0;
        delay(30);
      }
    }

    digitalWrite(rows[i], 1);
  }

  if (sound_pass_timer > sound_time_off){
    if (sound_press && sound_flag) {
      analogWrite(SOUND_PIN, sound_val);

      if (sound_timer > sound_time_on) {
        sound_press = 0;
        sound_timer = 0;
        analogWrite(SOUND_PIN, 0);
        sound_pass_timer = 0;
      } else {
        sound_timer++;
      }
    }
  } else{
    sound_pass_timer++;
  }
}
// 





