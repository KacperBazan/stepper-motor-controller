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

/* CONSTANTS */
const int LED = 16;
const int STEPS = 200;       //The particular motor I'm using has 200 steps.
const int TOGGLEBUTTON = 1; //Default button used for toggling enables.
const int ENABLE = 5;
const int BUTTON[2] = {17, 18};
const int MOTORS[1][2] = {{2, 4}}; //dirPin followed by stepPin

/* VARIABLES */
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
  pinMode(ENABLE, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON[0], INPUT);
  pinMode(BUTTON[1], INPUT);

  digitalWrite(ENABLE, LOW); // Enable pin is active low.

  for (int i = 0; i < 1; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      pinMode(MOTORS[i][j], OUTPUT);
    }
  }
}

/* Check the rising edge of a particular button and invert a toggle variable, as well as the enables of motors. */
void ToggleButton(int num)
{
  num--;
  if (millis() - curTime > td) //Prevents bouncing of toggle.
  {
    buttonState[num] = digitalRead(BUTTON[num]);
    if (buttonState[num] != lastButtonState[num])
    {
      if (buttonState[num])
      {
        toggle = !toggle;
        digitalWrite(ENABLE, !toggle);
        digitalWrite(LED, toggle);
      }
    }
    lastButtonState[num] = buttonState[num];
    curTime = millis();
  }
}

/* Reads a button and returns true or false depending if pressed down. */
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
 * Rotates a desired motor a number of steps at a desired speed.
 *
 * motor -> which motor you're selecting ranging from 1 to 6.
 * d     -> direction motor will spin (clockwise or anti-clockwise).
 * s     -> how many steps the motor will spin.
 * t     -> time in milliseconds the motor will take to complete steps.
 */
void Rotate(int motor, int d, int s, int t)
{
  digitalWrite(MOTORS[motor - 1][0], d);
  int c = 0;
  for (int i = 0; i < 2 * s; i++)
  {
    c = !c;
    digitalWrite(MOTORS[motor - 1][1], c);
    delay(t / (2 * s));
  }
}

void loop()
{
  ToggleButton(1);
  if (ReadButton(2))
  {
    int MAXSPEED = 1000;
    switch (moveCounter)
    {
    case 0: //90 degree turn Clockwise
      Rotate(1, 1, STEPS / 4, MAXSPEED / 4);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 1: //90 degree turn Counter - Clockwise
      Rotate(1, 0, STEPS / 4, MAXSPEED / 4);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 2: //180 degree turn Clockwise
      Rotate(1, 1, STEPS / 2, MAXSPEED / 2);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 3: //180 degree turn Counter - Clockwise
      Rotate(1, 0, STEPS / 2, MAXSPEED / 2);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 4: //270 degree turn Clockwise
      Rotate(1, 1, (STEPS * 3) / 4, MAXSPEED * 0.75);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 5: //270 degree turn Counter - Clockwise
      Rotate(1, 0, (STEPS * 3) / 4, MAXSPEED * 0.75);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 6: //360 degree turn Clockwise
      Rotate(1, 1, STEPS, MAXSPEED);
      moveCounter++;
      Serial.println(moveCounter);
      break;
    case 7: //360 degree turn Clockwise
      Rotate(1, 0, STEPS, MAXSPEED);
      moveCounter = 0;
      Serial.print(moveCounter);
      break;
    default:
      break;
    }
  }
}