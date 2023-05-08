#include <ezButton.h>
#include <Arduino.h>
#include <Key.h>
#include <Keypad.h>
#include <HID-Project.h>
#include <HID-Settings.h>
#include <RotaryEncoder.h>

// Debug flag
#define DEBUG false

// Pin definitions
#define PIN_IN1 21
#define PIN_IN2 20
#define PIN_BT1 19
#define PIN_IN11 18
#define PIN_IN21 15
#define PIN_BT2 14

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  { '1', '2', '3', '4' },
  { '5', '6', '7', '8' },
  { '9', '0', 'a', 'b' },
  { 'c', 'd', 'e', 'f' }
};

byte rowPins[rows] = { 2, 3, 10, 6 };
byte colPins[cols] = { 7, 16, 4, 5 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::FOUR3);
RotaryEncoder encoder1(PIN_IN11, PIN_IN21, RotaryEncoder::LatchMode::FOUR3);

int lastPos = -1;
int lastPos1 = -1;
int reposo = 100;
int release = 101;
bool pendingExecution = false;

ezButton button(PIN_BT1);
ezButton button1(PIN_BT2);

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    while (!Serial);
  }

  encoder.setPosition(10);
  encoder1.setPosition(10);

  button.setDebounceTime(50);
  button1.setDebounceTime(50);
  keypad.setHoldTime(1000000);

  Gamepad.begin();
}

int pushed = reposo;

void loop() {
  if (pushed != reposo) {
    pushed = release;
  }

  char key = keypad.getKey();

  if (key != NO_KEY) {
    int buttonNum = -1;

    if (key >= '1' && key <= '9') {
      buttonNum = key - '1' + 1;
    } else if (key >= 'a' && key <= 'f') {
      buttonNum = key - 'a' + 10;
    }

    if (buttonNum != -1) {
      pushButton(buttonNum);
      debugPrint("Key pressed: ", key);
    }
  }

  checkButton(button, 17);
  checkButton(button1, 20);

  encoder.tick();
  encoder1.tick();

  checkEncoder(encoder, lastPos, 18, 19);
  checkEncoder(encoder1, lastPos1, 21, 22);

  if (pushed == release && keypad.getState() == 0) {
    if (!pendingExecution) {
      Gamepad.releaseAll();
      Gamepad.write();
      pushed = reposo;
      pendingExecution = false;
    }
  }

  if (pendingExecution) {
    Gamepad.write();
    pendingExecution = false;
    delay(50); // debounce
  }
}

void debugPrint(const char *message, int value) {
  if (DEBUG) {
    Serial.print(message);
    Serial.println(value);
  }
}

void checkButton(ezButton &button, int buttonNumber) {
  button.loop();
  if (button.isPressed()) {
    pushButtonWithDelay(buttonNumber);
    debugPrint("Button pressed: ", buttonNumber);
  }
}

void checkEncoder(RotaryEncoder &encoder, int &lastPos, int buttonCW, int buttonCCW) {
  int newPos = encoder.getPosition();

  if (lastPos != newPos) {
    if (lastPos > newPos) {
      pushButtonWithDelay(buttonCW);
      debugPrint("Encoder CCW: ", buttonCCW);
    } else {
      pushButtonWithDelay(buttonCCW);
      debugPrint("Encoder CW: ", buttonCW);
    }
    lastPos = newPos;
  }
}

void pushButton(int button) {
  Gamepad.press(button);
  pushed = button;
  pendingExecution = true;
}

void pushButtonWithDelay(int button) {
  pushButton(button);
  delay(50);
}

  