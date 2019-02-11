//include main.h that includes api.h and all of the motor and sensor defines
#include "main.h"

//define the operator control function for use in switching to alt control with the toggle button
void operatorControl();

//toggle and press bool for forward motion of drum
int buttonToggleF = 0;
int buttonPressedF = 0;

//toggle and press bool for backward motion of drum
int buttonToggleR = 0;
int buttonPressedR = 0;


int flyToggle = 0;
int flyPressed = 0;

int reverseToggle = 0;
int reversePressed = 0;

void raceControl();

void pollTFly()
{
		if(joystickGetDigital(MAIN_JOY, 6, JOY_UP))
		{
				if(!flyPressed)
				{
						flyToggle = 1 - flyToggle;

						flyPressed = 1;
				}
		}
		else
			flyPressed = 0;

		if(flyToggle)
		{
				motorSet(PMotor, -127);
				motorSet(PMotor2, -127);
		}
		else
			if(!flyToggle)
			{
					motorStop(PMotor);
					motorStop(PMotor2);
			}
}

//for toggling the drum and soon other toggles
void pollToggles()
{
		//go forward with drum
		if(joystickGetDigital(MAIN_JOY, 5, JOY_UP))
		{
				//if the forward button toggle isn't on then continute
				if(!buttonPressedF)
				{
						//actaully flip the toggle, this is why the type has to be int
						buttonToggleF = 1 - buttonToggleF;
						//changed button pressed to true
						buttonPressedF = 1;
						//change the backward toggle to false so we don't try to go backwards and forwards
						buttonToggleR = false;
				}
		}
		//switch back to normal buttton state but leave toggle on if button isn't pressed.
		else
			buttonPressedF = 0;

//if our forward toggle is on, then eat the balls :D
if(buttonToggleF == true)
{
		motorSet(LoadServ, 127);
		motorSet(LoadServ2, 127);
}
//check if other toggle is on if we need to really stop the motor
else
{
		if(!buttonToggleR)
		{
				motorStop(LoadServ);
				motorStop(LoadServ2);
		}
}

	//go backwards with drum
	if(joystickGetDigital(MAIN_JOY, 5, JOY_DOWN))
	{
			//if we haven't pressed the button then toggle the button
			if(!buttonPressedR)
			{
					//actually toggle the button, this is why the type is int
					buttonToggleR = 1 - buttonToggleR;

					buttonPressedR = 1;

					//so we stop going forward.
					buttonToggleF = false;

			}
	}
	//else, then turn button pressed to false
	else
		buttonPressedR = 0;

	//if backward button toggle is on, then start the motor backward
	if(buttonToggleR == true)
	{
			motorSet(LoadServ, -127);
			motorSet(LoadServ2, -127);
	}
	//else, check if the forward toggle is off, then stop.
	else
	{
			if(!buttonToggleF)
			{
					motorStop(LoadServ);
					motorStop(LoadServ2);
			}
	}
}

bool rev = false;
//the default control for the claw bot
void clawControl()
{
		while(true)
		{
			if(joystickGetDigital(MAIN_JOY, 6, JOY_DOWN))
			{
					if(!reversePressed)
					{
							reverseToggle = 1 - reverseToggle;

							reversePressed = 1;
					}
			}
			else
				reversePressed = 0;

			if(reverseToggle)
			{
					rev = true;
			}
			else
			{
				if(!reverseToggle)
				{
						rev = false;
				}
			}

				//printf("Right %d\n", encoderGet(rightEncoder));
				if(!rev)
				{
						motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 3));
						motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 3));

						motorSet(RightMot, joystickGetAnalog(MAIN_JOY, 2));
						motorSet(RightMotT, joystickGetAnalog(MAIN_JOY, 2));
				}
				else
				{
						motorSet(LeftMot, -joystickGetAnalog(MAIN_JOY, 2));
						motorSet(LeftMotT, -joystickGetAnalog(MAIN_JOY, 2));

						motorSet(RightMot, -joystickGetAnalog(MAIN_JOY, 3));
						motorSet(RightMotT, -joystickGetAnalog(MAIN_JOY, 3));
				}
				//poll the shooter, loader, and drum toggle functions
				pollTFly();
				pollToggles();
				printf("right : %d\n", encoderGet(rightEncoder));
				printf("left : %d\n", encoderGet(leftEncoder));
		}
}

void operatorControl()
{
		clawControl();
}
