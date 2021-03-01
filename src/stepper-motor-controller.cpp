/*
 * Program Name: stepper-motor-controller
 * Program Description: Use the ESP32 board and buttons to drive multiple bipolar stepper motors.
 * Board Type: ESP2 DOIT-DEVKIT-V1
 * Date Started: Feb/24/2021
 * Author: Kacper Bazan
 * Author Link: https://github.com/KacperBazan
 * 
 * I am happy to recieve pull requests and comments!
 */

/*
 * References:
 * ESP_Wroom_32 Pinout: https://circuits4you.com/wp-content/uploads/2018/12/ESP32-Pinout.jpg
 * DroneBot Workshop Video: https://www.youtube.com/watch?v=0qwrnUeSpYQ
 */

#include <Arduino.h>

/*
 * CONSTANTS
 */
const int LED = 16;
const int STEPS = 200; //The particular motor I'm using has 200 steps.
const int BUTTON[2] = {17, 18};
const int TOGGLEBUTTON = 1; //Default button used for toggling enables.
const int ENABLE[1] = {5};
const int MOTORS[1][2] = {{2, 4}}; //dirPin followed by stepPin

/*
 * VARIABLES
 */
int buttonState[2] = {0, 0};
int lastButtonState[2] = {0, 0};
int toggle = 0;
int curTime = 0;
int td = 50;
int moveCounter = 0;

void setup()
{
  Serial.begin(115200);
  Serial.flush();

  pinMode(LED, OUTPUT);

  pinMode(BUTTON[0], INPUT);
  pinMode(BUTTON[1], INPUT);

  for (int i = 0; i < 1; i++)
  {
    pinMode(ENABLE[i], OUTPUT);
    /*
    * The enable pin is active low.
    * When it is tied high, the motors cannot spin.
    * This is done to prevent any motor motion upon initialization.
    */
    digitalWrite(ENABLE[i], HIGH);
    for (int j = 0; j < 2; j++)
    {
      pinMode(MOTORS[i][j], OUTPUT);
    }
  }
}

void ToggleEnables(int state)
{
  for (int i = 0; i < 1; i++)
  {
    digitalWrite(ENABLE[i], state);
  }
}

//Check the rising edge of a particular button and invert a toggle variable
void ToggleButton(int num)
{
  num--;
  if (millis() - curTime > td) //Set a time delay to prevent immediate bouncing of the toggle value.
  {
    buttonState[num] = digitalRead(BUTTON[num]);
    if (buttonState[num] != lastButtonState[num])
    {
      if (buttonState[num])
      {
        toggle = !toggle;
        ToggleEnables(!toggle);
        digitalWrite(LED, toggle);
      }
    }
    lastButtonState[num] = buttonState[num];
    curTime = millis();
  }
}

bool ReadButton(int num)
{
  num--;
  buttonState[num] = digitalRead(BUTTON[num]);
  if (buttonState[num] != lastButtonState[num])
  {
    if (buttonState[num])
    {
      lastButtonState[num] = buttonState[num];
      return true;
    }
  }
  lastButtonState[num] = buttonState[num];
  return false;
}

/*
 * motor -> which motor you're selecting ranging from 1 to 6.
 * d     -> direction motor will spin (clockwise or anti-clockwise).
 * s     -> how many steps the motor will spin.
 * t     -> time in milliseconds the motor will take to complete steps.
 */
void Rotate(int motor, int d, int s, int t)
{
  motor--;
  digitalWrite(MOTORS[motor][0], d);
  int c = 0;
  for (int i = 0; i < 2 * s; i++)
  {
    c = !c;
    digitalWrite(MOTORS[motor][1], c);
    delay(t / (2 * s));
  }
}

void loop()
{
  ToggleButton(1);
  if (ReadButton(2))
    switch (moveCounter)
    {
    case 0: //90 degree turn Clockwise
      Rotate(1, 1, STEPS / 4, 250);
      moveCounter++;
      break;
    case 1: //90 degree turn Counter - Clockwise
      Rotate(1, 0, STEPS / 4, 250);
      moveCounter++;
      break;
    case 2: //180 degree turn Clockwise
      Rotate(1, 1, STEPS / 2, 500);
      moveCounter++;
      break;
    case 3: //180 degree turn Counter - Clockwise
      Rotate(1, 0, STEPS / 2, 500);
      moveCounter++;
      break;
    case 4: //270 degree turn Clockwise
      Rotate(1, 1, (STEPS * 3) / 4 , 750);
      moveCounter++;
      break;
    case 5: //270 degree turn Counter - Clockwise
      Rotate(1, 0, (STEPS * 3) / 4 , 750);
      moveCounter++;
      break;
    case 6: //360 degree turn Clockwise
      Rotate(1, 1, STEPS , 1000);
      moveCounter++;
      break;
    case 7: //360 degree turn Clockwise
      Rotate(1, 0, STEPS , 1000);
      moveCounter = 0;
      break;
    default:
      break;
    }
}