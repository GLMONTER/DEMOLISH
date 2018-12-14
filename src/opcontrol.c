/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"


void operatorControl();

int buttonToggleF = 0;
int buttonPressedF = 0;

int buttonToggleR = 0;
int buttonPressedR = 0;

void pollToggles()
{
		if(joystickGetDigital(MAIN_JOY, 7, JOY_RIGHT))
		{
				if(!buttonPressedF)
				{
						buttonToggleF = 1 - buttonToggleF;

						buttonPressedF = 1;

						buttonToggleR = false;
				}
		}
		else
			buttonPressedF = 0;


if(buttonToggleF == true)
{
		motorSet(LoadServ, 127);
}
else
{
		if(!buttonPressedR)
		{
				motorStop(LoadServ);
		}
}

	//go backward
	if(joystickGetDigital(MAIN_JOY, 7, JOY_LEFT))
	{
			if(!buttonPressedR)
			{
					buttonToggleR = 1 - buttonToggleR;

					buttonPressedR = 1;

					//so we stop going forward.
					buttonToggleF = false;

			}
	}
	else
		buttonPressedR = 0;


	if(buttonToggleR == true)
	{
	motorSet(LoadServ, -127);
	}
	else
	{
			if(!buttonToggleF)
			{
					motorStop(LoadServ);
			}
	}
}

void LoadBall()
{

		//handling the main loader
		if(joystickGetDigital(MAIN_JOY, 7, JOY_UP))
		{
				motorSet(LoadMot, 127);
		}
		if(!joystickGetDigital(MAIN_JOY, 7, JOY_UP) && !joystickGetDigital(MAIN_JOY, 7, JOY_DOWN))
		{
			motorStop(LoadMot);
		}
		if(joystickGetDigital(MAIN_JOY, 7, JOY_DOWN))
		{
				motorSet(LoadMot, -127);
		}
}


void MovePuncher()
{
	if(joystickGetDigital(MAIN_JOY, 8, JOY_RIGHT))
	{
			motorSet(PMotor, 127);
			motorSet(PMotor2, 127);
	}

	if(joystickGetDigital(MAIN_JOY, 8, JOY_LEFT))
	{
		motorSet(PMotor, -127);
		motorSet(PMotor2, -127);
	}

	if(!joystickGetDigital(MAIN_JOY, 8, JOY_LEFT) && !joystickGetDigital(MAIN_JOY, 8, JOY_RIGHT))
	{
			motorStop(PMotor);
			motorStop(PMotor2);
	}
}


void AltControl()
{
	while(true)
	{
		//if we get the up button on button group 8, go back to normal controls and break out of the loop.
	if(joystickGetDigital(MAIN_JOY, 8, JOY_UP))
	{
		operatorControl();
	}
	motorSet(Mid2, joystickGetAnalog(MAIN_JOY, 2));
	motorSet(Mid, joystickGetAnalog(MAIN_JOY, 3));
	motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 3));
	motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 3));
	motorSet(RightMot, joystickGetAnalog(MAIN_JOY, 2));
	motorSet(RightMotT, joystickGetAnalog(MAIN_JOY, 2));
	MovePuncher();
	LoadBall();
	pollToggles();
}
}

void operatorControl()
{
	while (true)
	{
		//if we get the Down button on button group 8, go to the alt controls and break out of the loop.
		if(joystickGetDigital(MAIN_JOY, 8, JOY_DOWN))
		{
			AltControl();
		}
			pollToggles();
			MovePuncher();
			LoadBall();
			//MAIN_JOY = 1 which is the main controller, 6 is the button group, and JOY_DOWN is the down button in button group 6
			//if were hitting the forward button and are attempting to turn then turn based on the analog output of the controller joysticks + the forward button.
			if(!joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) > 30 || joystickGetAnalog(MAIN_JOY, 4) < -30))
			{
					if(joystickGetAnalog(MAIN_JOY, 4) > 30)
					{
							motorSet(LeftMot, 127);
							motorSet(LeftMotT, 127);
							motorSet(Mid, 127);
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(RightMot, 127 - joystickGetAnalog(MAIN_JOY, 4));
							motorSet(RightMotT, 127 - joystickGetAnalog(MAIN_JOY, 4));
							motorSet(Mid2, 127 - joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -30)
					{
							motorSet(RightMot, 127);
							motorSet(RightMotT, 127);
							motorSet(Mid2, 127);
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(LeftMot, 127 - -(joystickGetAnalog(MAIN_JOY, 4)));
							motorSet(LeftMotT, 127 - -(joystickGetAnalog(MAIN_JOY, 4)));
							motorSet(Mid, 127 - -(joystickGetAnalog(MAIN_JOY, 4)));
					}
			}
			//if we are not hitting the back or forward buttons, and we are attempting to turn, then rotate the car(Reverse the motors).
			//simple: turning without going backwards or forward.
			if(!joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) > 30 || joystickGetAnalog(MAIN_JOY, 4) < -30))
			{
					if(joystickGetAnalog(MAIN_JOY, 4) > 5)
					{
							motorSet(Mid2, -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(RightMot, -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(RightMotT,	-joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 4));
							motorSet(Mid, joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -5)
					{
						motorSet(Mid2, -joystickGetAnalog(MAIN_JOY, 4));
						motorSet(RightMot, -joystickGetAnalog(MAIN_JOY, 4));
						motorSet(RightMotT, -joystickGetAnalog(MAIN_JOY, 4));
						motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 4));
						motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 4));
						motorSet(Mid, joystickGetAnalog(MAIN_JOY, 4));
					}
			}
			//if hit Back button and we are attempting to turn, ajust the motors according to going backwards and the joystick analog output.
			//simple : Going back and turning at the same time
			if(joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) > 30 || joystickGetAnalog(MAIN_JOY, 4) < -30))
			{
					if(joystickGetAnalog(MAIN_JOY, 4) > 30)
					{
							motorSet(RightMot, -127);
							motorSet(RightMotT, -127);
							motorSet(Mid2, -127);
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(LeftMot, 127 - -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMotT, 127 - -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(Mid, 127 - -joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -30)
					{
						motorSet(Mid, -127);
						motorSet(LeftMot, -127);
						motorSet(LeftMotT, -127);
						//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
						motorSet(RightMot, (127 - joystickGetAnalog(MAIN_JOY, 4)));
						motorSet(RightMotT, (127 - joystickGetAnalog(MAIN_JOY, 4)));
						motorSet(Mid2, (127 - joystickGetAnalog(MAIN_JOY, 4)));
					}

			}
			//this Block of Code handles basic forward and backward functionality, and also stopping the car if there is no input
		{
					//if we are not turning and we are hitting the backward button, then simply go backward
					if(joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) < 30 && joystickGetAnalog(MAIN_JOY, 4) > -30))
					{
							motorSet(Mid, -127);
							motorSet(Mid2, -127);
							motorSet(LeftMot, -127);
							motorSet(LeftMotT, -127);
							motorSet(RightMot, -127);
							motorSet(RightMotT, -127);
					}
					//if we have no input then just stop everything
					if(!joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) < 30 && joystickGetAnalog(MAIN_JOY, 4) > -30))
					{
							motorStop(LeftMot);
							motorStop(LeftMotT);
							motorStop(RightMot);
							motorStop(RightMotT);
							motorStop(Mid);
							motorStop(Mid2);
					}
					//if we are not turning and we are hitting the forward button, then simply go forward
					if(joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) < 30 && joystickGetAnalog(MAIN_JOY, 4) > -30))
					{
							motorSet(Mid, 127);
							motorSet(Mid2, 127);
							motorSet(LeftMot,  127);
							motorSet(LeftMotT,  127);
							motorSet(RightMot, 127);
							motorSet(RightMotT, 127);
					}
		}
	}
}
