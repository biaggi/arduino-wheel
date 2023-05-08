# Code Documentation

## Description
This is an Arduino program that uses a numeric keypad, two buttons, two rotary encoders, and the HID-Project library to simulate button presses of a joystick on a computer. It is used in the configuration of a racing simulation wheel with a Simucube.

## Libraries
- ezButton.h
- Arduino.h
- Key.h
- Keypad.h
- HID-Project.h
- HID-Settings.h
- RotaryEncoder.h

## Variables and Constants
- `DEBUG`: boolean variable that turns on or off the serial debugging information output. If `true`, debugging information will be displayed through the serial port at a baud rate of 9600.
- `PIN_IN1`, `PIN_IN2`, `PIN_BT1`, `PIN_IN11`, `PIN_IN21`, `PIN_BT2`: constants that indicate the pins used by the rotary encoders and buttons.
- `rows`, `cols`: constants that indicate the number of rows and columns of the numeric keypad.
- `keys`: matrix containing the keys of the numeric keypad.
- `rowPins`, `colPins`: arrays that contain the pins used for the rows and columns of the numeric keypad.
- `keypad`: Keypad object used to read the keys of the numeric keypad.
- `encoder`, `encoder1`: RotaryEncoder objects used to read the position of the rotary encoders.
- `lastPos`, `lastPos1`: variables containing the last registered position of the rotary encoders.
- `reposo`, `release`: constants indicating the state of the buttons, at rest or released.
- `pendingExecution`: boolean variable indicating if there is a pending button press execution.
- `button`, `button1`: ezButton objects used to read the buttons.

## Functions
- `setup()`: function that runs once at the beginning of the program. Initializes the objects and variables used by the program.
- `loop()`: function that runs repeatedly during the program execution. Reads the values of the numeric keypad and rotary encoders, and executes the simulation of button presses on the computer.
- `debugPrint(const char *message, int value)`: function that displays debugging information through the serial port if the `DEBUG` variable is `true`.
- `checkButton(ezButton &button, int buttonNumber)`: function that checks if a button has been pressed and executes the corresponding button press simulation.
- `checkEncoder(RotaryEncoder &encoder, int &lastPos, int buttonCW, int buttonCCW)`: function that checks if one of the rotary encoders has been rotated and executes the corresponding button press simulation.
- `pushButton(int button)`: function that simulates a button press on the computer.
- `pushButtonWithDelay(int button)`: function that simulates a button press on the computer with a delay for debouncing purposes.
- `pushButtonWithDelay(int button)`: function that simulates a button press on the computer with a delay for debouncing purposes.