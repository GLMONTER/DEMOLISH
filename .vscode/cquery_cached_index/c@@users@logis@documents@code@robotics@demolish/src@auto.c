#include "main.h"

void reset()
{
    encoderReset(rightEncoder);
    encoderReset(leftEncoder);
}

void stopDrive()
{
    motorStop(LeftMot);
    motorStop(LeftMotT);
    motorStop(RightMot);
    motorStop(RightMotT);
}

void brake(enum BrakeType b)
{
    if(b == Normal)
    {
        motorSet(LeftMot, -127);
        motorSet(LeftMotT, -127);
        motorSet(RightMot, -127);
        motorSet(RightMotT, -127);
    }
    if(b == Opposing)
    {
        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
    }
    if(b == Left)
    {
        motorSet(LeftMot, 127);
        motorSet(LeftMotT, 127);
        motorSet(RightMot, -127);
        motorSet(RightMotT, -127);
    }
    if(b == Right)
    {
        motorSet(LeftMot, -127);
        motorSet(LeftMotT, -127);
        motorSet(RightMot, 127);
        motorSet(RightMotT, 127);
    }
  delay(50);
  stopDrive();
  reset();
}


void load(unsigned int mili)
{
    motorSet(LoadServ, 127);
    delay(mili);
    motorStop(LoadServ);
}

void loadF()
{
    motorSet(LoadServ, 127);
}

void shoot(unsigned int mili)
{
    motorSet(PMotor, -127);
    motorSet(PMotor2, -127);
    delay(mili);
}

 //a shoot funciton, if the shooter is set right the delay time is just enough to fire the shooter during an auto period
 //go forward for a number of degrees,
 void goForward(int rotDeg)
 {
    stopDrive();

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
   	//if rotDeg less than zero then go backward until the encoder reads rotDeg
   	if(rotDeg < 0)
   	{
   		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) > rotDeg)
   		{
   				motorSet(RightMot, -100);
   				motorSet(RightMotT, -100);

   				motorSet(LeftMot, -100);
   				motorSet(LeftMotT, -100);
   		}
   	}
   	//if rotDeg is not less than zero then go forward until encoder reads rotDeg
   	else
   	{
   		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) < rotDeg)
   		{
   				motorSet(RightMot, 100);
   				motorSet(RightMotT, 100);

   				motorSet(LeftMot, 100);
   				motorSet(LeftMotT, 100);
   		}
   	}
    if(rotDeg < 0)
    {
        brake(Opposing);
    }
    else
      brake(Normal);

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
 }


 //a shoot funciton, if the shooter is set right the delay time is just enough to fire the shooter during an auto period
 //go forward for a number of degrees,
 void goForwardFast(int rotDeg)
 {
    stopDrive();

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
   	//if rotDeg less than zero then go backward until the encoder reads rotDeg
   	if(rotDeg < 0)
   	{
   		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) > rotDeg)
   		{
   				motorSet(RightMot, -127);
   				motorSet(RightMotT, -127);

   				motorSet(LeftMot, -127);
   				motorSet(LeftMotT, -127);
   		}
   	}
   	//if rotDeg is not less than zero then go forward until encoder reads rotDeg
   	else
   	{
   		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) < rotDeg)
   		{
   				motorSet(RightMot, 127);
   				motorSet(RightMotT, 127);

   				motorSet(LeftMot, 127);
   				motorSet(LeftMotT, 127);
   		}
   	}
    if(rotDeg < 0)
    {
        brake(Opposing);
    }
    else
      brake(Normal);

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
 }


 //a funciton that turns right, if deg is equal zero or default then turn exactly 90 degrees.
 void turnRight(int deg)
 {
   	if(deg == 0)
   			deg = 260;
    if(deg == 6969)
        deg = 305;

    stopDrive();

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);

   	//turn left to aim at the blue flag
   	while(encoderGet(rightEncoder) > (deg * -1))
   	{
   			motorSet(RightMot, -100);
   			motorSet(RightMotT, -100);

   			motorSet(LeftMot, 100);
   			motorSet(LeftMotT, 100);
   	}

    stopDrive();

    //this delay is to prevent the encoder from counting past zero after we shutoff the drive motors due to the bot still spinning.

    brake(Right);

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
 }
 void turnLeft(int deg)
 {
   	if(deg == 0)
   			deg = 260;
    if(deg == 6969)
      deg = 305;

    stopDrive();

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);

 	//turn left to aim at the blue flag
   	while(encoderGet(rightEncoder) < deg)
   	{
   			motorSet(RightMot, 100);
   			motorSet(RightMotT, 100);

   			motorSet(LeftMot, -100);
   			motorSet(LeftMotT, -100);
   	}

    stopDrive();

    //this delay is to prevent the encoder from counting past zero after we shutoff the drive motors due to the bot still spinning.

    brake(Left);

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
 }
//line up with 4th block with tick closest to flag.
void farBlue()
{
  shoot(4000);
  loadF();
  delay(750);
  motorStop(PMotor);
  motorStop(PMotor2);
  //turnRight(230);
  goForward(400);
  turnRight(400);
  goForward(-1800);
}

 void closeBlue()
 {
   //shoot the ball at the 3rd flag
   motorSet(PMotor, -127);
   motorSet(PMotor2, -127);
   goForward(250);
   delay(3000);
   loadF();
   delay(500);

   goForward(-350);


   //turn right towards cap
   turnLeft(270);

   //toggle cap and get ball
   goForward(1000);

   //give enough time to load ball
   delay(500);

   motorStop(LoadServ);

   goForward(-100);

   turnRight(340);

   loadF();

   //delay(2000);

   goForward(-1100);

 }
//auton for far red square, you want fourth mark with back wheel lining up with tick closest to flag.
void farRed()
{
    shoot(4000);
    loadF();
    delay(750);
    motorStop(PMotor);
    motorStop(PMotor2);
    //turnRight(230);
    goForward(480);
    turnLeft(350);
    goForward(-1850);
}

 //the auto period for the square closest for the flag
 void closeRed()
 {
       //shoot the ball at the 3rd flag
       motorSet(PMotor, -127);
       motorSet(PMotor2, -127);
       goForward(250);
       delay(3000);
       loadF();
       delay(500);

       //move forward and melee the bottom flag
       goForward(800);

       //go back and get ready to turn right
       goForward(-1275);


       //turn right towards cap
       turnRight(6969);

       //toggle cap and get ball
       goForward(1100);

       //give enough time to load ball
       delay(500);

       motorStop(LoadServ);

       turnLeft(240);

       loadF();

       delay(3000);

       goForward(-1500);

       turnRight(75);

       loadF();

       delay(1500);

 }

//the auton code for the 1 min skills run starting in the far red square
void skills()
{

}

void autonomous()
{
  closeBlue();
}
