/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */


//this function is the autonmyous period for the red square closest to the flags
void CloseRed()
{
      //so we can exit the loop when we are done with the period
      bool isDone = false;

      while(!isDone)
      {

      //go forward from initial square
      while(encoderGet(rightEncoder) < 180 && encoderGet(leftEncoder) < 180)
      {
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
        motorSet(Mid2, 127);

        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(Mid, 127);
      }

      motorStopAll();
      encoderReset(rightEncoder);
      encoderReset(leftEncoder);

      //turn left to aim at the blue flag
      while(encoderGet(rightEncoder) < 380)
      {
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
        motorSet(Mid2, 127);

        motorSet(LeftMot, -127);
        motorSet(LeftMotT, -127);
        motorSet(Mid, -127);
      }

      motorStopAll();
      encoderReset(rightEncoder);
      encoderReset(leftEncoder);

      //go forward after turning to shoot the flag correctly
      while(encoderGet(rightEncoder) < 360 && encoderGet(leftEncoder) < 360)
      {
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
        motorSet(Mid2, 127);

        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(Mid, 127);
      }

      motorStopAll();
      encoderReset(rightEncoder);
      encoderReset(leftEncoder);
      //change this to true so we can exit the loop

      //shoot the ball at the second flag
      motorSet(PMotor, -127);
      motorSet(PMotor2, -127);

      wait(1500);

      //turn after shoooting
      while(encoderGet(rightEncoder) < 360)
      {
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
        motorSet(Mid2, 127);

        motorSet(LeftMot, -127);
        motorSet(LeftMotT, -127);
        motorSet(Mid, -127);
      }

      motorStopAll();
      encoderReset(rightEncoder);
      encoderReset(leftEncoder);


      //go forward after turning, getting ready to melee
      while(encoderGet(rightEncoder) < 300 && encoderGet(leftEncoder) < 300)
      {
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
        motorSet(Mid2, 127);

        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(Mid, 127);
      }
      //turn right, getting ready to go forward to melee
      while(encoderGet(leftEncoder) < 720)
      {
        motorSet(RightMot, -127);
        motorSet(RightMotT, -127);
        motorSet(Mid2, -127);

        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(Mid, 127);
      }

      motorStopAll();
      encoderReset(rightEncoder);
      encoderReset(leftEncoder);


      isDone = true;

      //shutdown the encoders, power will be lost and any function calls related to the encoder in the function parameters will be ignored.
      encoderShutdown(rightEncoder);
      encoderShutdown(leftEncoder);

    }

}


void autonomous()
{
  CloseRed();
}
