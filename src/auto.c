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


void shoot()
{
	motorSet(PMotor, -127);
	motorSet(PMotor2, -127);

	delay(2000);
}
void goForward(int rotDeg)
{
	motorStopAll();
	encoderReset(rightEncoder);
	encoderReset(leftEncoder);

	if(rotDeg < 0)
	{
		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) > rotDeg)
		{
				motorSet(RightMot, -127);
				motorSet(RightMotT, -127);
				motorSet(Mid2, -127);

				motorSet(LeftMot, -127);
				motorSet(LeftMotT, -127);
				motorSet(Mid, -127);
		}
	}
	else
	{
		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) < rotDeg)
		{
				motorSet(RightMot, 127);
				motorSet(RightMotT, 127);
				motorSet(Mid2, 127);

				motorSet(LeftMot, 127);
				motorSet(LeftMotT, 127);
				motorSet(Mid, 127);
		}
	}

	motorStopAll();
	encoderReset(rightEncoder);
	encoderReset(leftEncoder);
}

void turnRight(int deg)
{
	if(deg == 0)
			deg = 280;

	motorStopAll();
	encoderReset(rightEncoder);
	encoderReset(leftEncoder);

	//turn left to aim at the blue flag
	while(encoderGet(leftEncoder) < deg)
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
}
void turnLeft(int deg)
{
	if(deg == 0)
			deg = 280;
	motorStopAll();
	encoderReset(rightEncoder);
	encoderReset(leftEncoder);

	//turn left to aim at the blue flag
	while(encoderGet(rightEncoder) < deg)
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
}
void closeRed()
{
      //so we can exit the loop when we are done with the period
      bool isDone = false;

      while(!isDone)
      {
      shoot();

      turnLeft(17);
      //go forward from initial square
      goForward(1400);

      goForward(-1600);


			turnRight(0);

			goForward(2000);
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
  closeRed();
}
