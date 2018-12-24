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

void pollTFly()
{
		if(joystickGetDigital(MAIN_JOY, 8, JOY_RIGHT))
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
				motorSet(PMotor, 127);
				motorSet(PMotor2, 127);
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
		if(joystickGetDigital(MAIN_JOY, 7, JOY_RIGHT))
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
}
//check if other toggle is on if we need to really stop the motor
else
{
		if(!buttonToggleR)
		{
				motorStop(LoadServ);
		}
}

	//go backwards with drum
	if(joystickGetDigital(MAIN_JOY, 7, JOY_LEFT))
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
	}
	//else, check if the forward toggle is off, then stop.
	else
	{
			if(!buttonToggleF)
			{
					motorStop(LoadServ);
			}
	}
}
//the funciton that loads the ball using a hold button
void LoadBall()
{
		//handling the main loader
		if(joystickGetDigital(MAIN_JOY, 7, JOY_UP))
		{
				motorSet(LoadMot, 127);
		}
		if(joystickGetDigital(MAIN_JOY, 7, JOY_DOWN))
		{
				motorSet(LoadMot, -127);
		}
		if(!joystickGetDigital(MAIN_JOY, 7, JOY_UP) && !joystickGetDigital(MAIN_JOY, 7, JOY_DOWN))
		{
			motorStop(LoadMot);
		}
}


//the default control for the claw bot
void AltControl()
{
		while(true)
		{
				//if we get the up button on button group 8, go back to normal controls and break out of the loop.
				if(joystickGetDigital(MAIN_JOY, 8, JOY_UP))
				{
						operatorControl();
				}

				motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 3));
				motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 3));

				motorSet(RightMot, joystickGetAnalog(MAIN_JOY, 2));
				motorSet(RightMotT, joystickGetAnalog(MAIN_JOY, 2));

				//poll the shooter, loader, and drum toggle functions
				pollTFly();
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
			LoadBall();
			pollTFly();
			//MAIN_JOY = 1 which is the main controller, 6 is the button group, and JOY_DOWN is the down button in button group 6
			//if were hitting the forward button and are attempting to turn then turn based on the analog output of the controller joysticks + the forward button.
			if(!joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) > 30 || joystickGetAnalog(MAIN_JOY, 4) < -30))
			{
					if(joystickGetAnalog(MAIN_JOY, 4) > 30)
					{
							motorSet(LeftMot, 127);
							motorSet(LeftMotT, 127);
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(RightMot, 127 - joystickGetAnalog(MAIN_JOY, 4));
							motorSet(RightMotT, 127 - joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -30)
					{
							motorSet(RightMot, 127);
							motorSet(RightMotT, 127);
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(LeftMot, 127 - -(joystickGetAnalog(MAIN_JOY, 4)));
							motorSet(LeftMotT, 127 - -(joystickGetAnalog(MAIN_JOY, 4)));
					}
			}
			//if we are not hitting the back or forward buttons, and we are attempting to turn, then rotate the car(Reverse the motors).
			//simple: turning without going backwards or forward.
			if(!joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) > 30 || joystickGetAnalog(MAIN_JOY, 4) < -30))
			{
					if(joystickGetAnalog(MAIN_JOY, 4) > 5)
					{
							motorSet(RightMot, -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(RightMotT,	-joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -5)
					{
						motorSet(RightMot, -joystickGetAnalog(MAIN_JOY, 4));
						motorSet(RightMotT, -joystickGetAnalog(MAIN_JOY, 4));
						motorSet(LeftMot, joystickGetAnalog(MAIN_JOY, 4));
						motorSet(LeftMotT, joystickGetAnalog(MAIN_JOY, 4));
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
							//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
							motorSet(LeftMot, 127 - -joystickGetAnalog(MAIN_JOY, 4));
							motorSet(LeftMotT, 127 - -joystickGetAnalog(MAIN_JOY, 4));
					}

					if(joystickGetAnalog(MAIN_JOY, 4) < -30)
					{
						motorSet(LeftMot, -127);
						motorSet(LeftMotT, -127);
						//this arithmetic makes the left motors equal to its top speed minus the Joysticks horizontal. With this, the car can achieve smooth turning.
						motorSet(RightMot, (127 - joystickGetAnalog(MAIN_JOY, 4)));
						motorSet(RightMotT, (127 - joystickGetAnalog(MAIN_JOY, 4)));
					}

			}
			//this Block of Code handles basic forward and backward functionality, and also stopping the car if there is no input

				//if we are not turning and we are hitting the backward button, then simply go backward
				if(joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) < 30 && joystickGetAnalog(MAIN_JOY, 4) > -30))
				{
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
				}
				//if we are not turning and we are hitting the forward button, then simply go forward
				if(joystickGetDigital(MAIN_JOY, 6, JOY_DOWN) && !joystickGetDigital(MAIN_JOY, 5, JOY_DOWN) && (joystickGetAnalog(MAIN_JOY, 4) < 30 && joystickGetAnalog(MAIN_JOY, 4) > -30))
				{
						motorSet(LeftMot,  127);
						motorSet(LeftMotT,  127);
						motorSet(RightMot, 127);
						motorSet(RightMotT, 127);
				}

	}
}
