#include <Keyboard.h>

#define RED_OUT 16
#define GREEN_OUT 17
#define BLUE_OUT 18

#define RED_IN A0
#define GREEN_IN A1
#define BLUE_IN A2

#define ROTARY_0_SW 12
#define ROTARY_0_DT 13
#define ROTARY_0_CLK 14

#define ROTARY_1_SW 11
#define ROTARY_1_DT 10
#define ROTARY_1_CLK 9

const uint8_t ROW_PINS[4] = {5, 6, 7, 8};
const uint8_t COL_PINS[4] = {20, 19, 21, 22};

const uint8_t KEYMAP[4][4] = {
  {KEY_F13, KEY_F14, KEY_F15, KEY_F16},
  {KEY_F17, KEY_F18, KEY_F19, KEY_F20},
  {KEY_F21, KEY_F22, KEY_F23, KEY_F24},
  {KEY_KP_SLASH, KEY_KP_ASTERISK, KEY_KP_MINUS, KEY_KP_PLUS},
};

const uint8_t ROT_MAP[2][2] = {
  {KEY_DOWN_ARROW, KEY_UP_ARROW},
  {KEY_PAGE_DOWN, KEY_PAGE_UP},
};

const uint8_t ROT_SWITCH_MAP[2] = {KEY_HOME, KEY_END};

uint16_t prev_state = 0;
uint8_t prev_rot_0 = 0;
uint8_t prev_rot_1 = 0;
uint8_t prev_rot_sw_0 = 0;
uint8_t prev_rot_sw_1 = 0;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(BLUE_OUT, OUTPUT);
  pinMode(RED_IN, INPUT);
  pinMode(GREEN_IN, INPUT);
  pinMode(BLUE_IN, INPUT);

  for(int i = 0; i < 4; i++)
    pinMode(COL_PINS[i], OUTPUT);
  for(int i = 0; i < 4; i++)
    pinMode(ROW_PINS[i], INPUT_PULLDOWN);

  pinMode(ROTARY_0_SW, INPUT_PULLUP);
  pinMode(ROTARY_0_DT, INPUT);
  pinMode(ROTARY_0_CLK, INPUT);
  pinMode(ROTARY_1_SW, INPUT_PULLUP);
  pinMode(ROTARY_1_DT, INPUT);
  pinMode(ROTARY_1_CLK, INPUT);

  prev_rot_0 = digitalRead(ROTARY_0_CLK);
  prev_rot_1 = digitalRead(ROTARY_1_CLK);
  prev_rot_sw_0 = digitalRead(ROTARY_0_SW);
  prev_rot_sw_1 = digitalRead(ROTARY_1_SW);
}

void loop() {
  // RGB controls
  uint16_t red_val = map(analogRead(RED_IN), 0, 1024, 0, 270);
  uint16_t green_val = map(analogRead(GREEN_IN), 0, 1024, 0, 270);
  uint16_t blue_val = map(analogRead(BLUE_IN), 0, 1024, 0, 270);
  analogWrite(RED_OUT, red_val);
  analogWrite(GREEN_OUT, green_val);
  analogWrite(BLUE_OUT, blue_val);

  uint16_t state = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(COL_PINS[i], HIGH);
      if (digitalRead(ROW_PINS[j]) == HIGH) {
        state |= 1 << (j * 4 + i);
      }
      digitalWrite(COL_PINS[i], LOW);
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      unsigned short mask = 1 << (j * 4 + i);
      bool key_state = state & mask;
      bool prev_key_state = prev_state & mask;
      auto keycode = KEYMAP[j][i];
      if (key_state ^ prev_key_state) {
        if (key_state) {
          Keyboard.press(keycode);
        } else {
          Keyboard.release(keycode);
        }
      }
    }
  }
  prev_state = state;

  uint8_t rot_state = digitalRead(ROTARY_0_CLK);
  if (rot_state != prev_rot_0) {
    if (digitalRead(ROTARY_0_DT) != rot_state) {
      Keyboard.write(ROT_MAP[0][0]);
    } else {
      Keyboard.write(ROT_MAP[0][1]);
    }
  }
  prev_rot_0 = rot_state;

  rot_state = digitalRead(ROTARY_1_CLK);
  if (rot_state != prev_rot_1) {
    if (digitalRead(ROTARY_1_DT) != rot_state) {
      Keyboard.write(ROT_MAP[1][0]);
    } else {
      Keyboard.write(ROT_MAP[1][1]);
    }
  }
  prev_rot_1 = rot_state;

  if (digitalRead(ROTARY_0_SW) == LOW && prev_rot_sw_0 == HIGH) {
    Keyboard.press(ROT_SWITCH_MAP[0]);
  } else if (digitalRead(ROTARY_0_SW) == HIGH && prev_rot_sw_0 == LOW) {
    Keyboard.release(ROT_SWITCH_MAP[0]);
  }
  if (digitalRead(ROTARY_1_SW) == LOW && prev_rot_sw_1 == HIGH) {
    Keyboard.press(ROT_SWITCH_MAP[1]);
  } else if (digitalRead(ROTARY_1_SW) == HIGH && prev_rot_sw_1 == LOW) {
    Keyboard.release(ROT_SWITCH_MAP[1]);
  }
  prev_rot_sw_0 = digitalRead(ROTARY_0_SW);
  prev_rot_sw_1 = digitalRead(ROTARY_1_SW);

  delay(10);
  // put your main code here, to run repeatedly:
}
