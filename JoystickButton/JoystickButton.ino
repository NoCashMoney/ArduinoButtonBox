// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// Ground digital pins 9, 10, 11, and 12 to press the joystick 
// buttons 0, 1, 2, and 3.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick;

void setup() {
  // Initialize Button Pins
  pinMode(21, OUTPUT); // Row 1
  pinMode(20, OUTPUT); // Row 2
  pinMode(19, OUTPUT); // Row 3
  pinMode(18, OUTPUT); // Row 4
  pinMode(15, OUTPUT); // Row 5

  pinMode(14, INPUT_PULLUP); // Column 1
  pinMode(16, INPUT_PULLUP); // Column 2
  pinMode(10, INPUT_PULLUP); // Column 3
  pinMode(9, INPUT_PULLUP); // Column 4
  pinMode(8, INPUT_PULLUP); // Column 5

  // Initialize Rotary Encoder Pins
  pinMode(1, INPUT_PULLUP); // Encoder 1, 1
  pinMode(0, INPUT_PULLUP); // Encoder 1, 2
  pinMode(2, INPUT_PULLUP); // Encoder 2, 1
  pinMode(3, INPUT_PULLUP); // Encoder 2, 2
  pinMode(4, INPUT_PULLUP); // Encoder 3, 1
  pinMode(5, INPUT_PULLUP); // Encoder 3, 2
  pinMode(6, INPUT_PULLUP); // Encoder 4, 1
  pinMode(7, INPUT_PULLUP); // Encoder 4, 2

  // Initialize Joystick Library
  Joystick.begin();
}

// Raw, Column, Button count
int rawCount = 5;
int columnCount = 5;
int buttonCount = 24;

// Raw, Column index
int rawPinList[5] = {21, 20, 19, 18, 15};
int columnPinList[5] = {14, 16, 10, 9, 8};

// Current state of the button
int currentButtonState[5][5] = {{0,}, {0,}, {0,}, {0,}, {0,}};

// Last state of the button
int lastButtonState[5][5] = {{0,}, {0,}, {0,}, {0,}, {0,}};

void pollingButtonScan()
{
  for(int raw = 0; raw < rawCount; raw++)
  {
    digitalWrite(rawPinList[raw], LOW);

    for(int column = 0; column < columnCount; column++)
    {
      currentButtonState[raw][column] = !digitalRead(columnPinList[column]);
    }

    digitalWrite(rawPinList[raw], HIGH);
  }
}

int compareButtonState(int previous, int currnt)
{
  int isChanged = 0; // 0 = Non changed, 1 = Changed

  for(int raw = 0; raw < rawCount; raw++)
  {
    for(int column = 0; column < columnCount; column++)
    {
      if(lastButtonState[raw][column] != currentButtonState[raw][column])
      {
        isChanged = 1;
      }
    }
  }

  return isChanged;
}

void loop() {

  // // Read pin values
  // for (int index = 0; index < 2; index++)
  // {
  //   int currentButtonState = !digitalRead(index + pinToButtonMap);
  //   if (currentButtonState != lastButtonState[index])
  //   {
  //     Joystick.setButton(index, currentButtonState);
  //     lastButtonState[index] = currentButtonState;
  //   }
  // }

  compareButtonState(lastButtonState, currentButtonState);



  delay(50);
}
