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
   		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) < -rotDeg)
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
   		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) > -rotDeg)
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
 void goForwardSlow(int rotDeg)
 {
    stopDrive();

   	encoderReset(rightEncoder);
   	encoderReset(leftEncoder);
   	//if rotDeg less than zero then go backward until the encoder reads rotDeg
   	if(rotDeg < 0)
   	{
   		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) < -rotDeg)
   		{
   				motorSet(RightMot, -50);
   				motorSet(RightMotT, -50);

   				motorSet(LeftMot, -50);
   				motorSet(LeftMotT, -50);
   		}
   	}
   	//if rotDeg is not less than zero then go forward until encoder reads rotDeg
   	else
   	{
   		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) > -rotDeg)
   		{
   				motorSet(RightMot, 50);
   				motorSet(RightMotT, 50);

   				motorSet(LeftMot, 50);
   				motorSet(LeftMotT, 50);
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
   		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) < -rotDeg)
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
   		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) > -rotDeg)
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
 void turnRightSlow(int deg)
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
   			motorSet(RightMot, -50);
   			motorSet(RightMotT, -50);

   			motorSet(LeftMot, 50);
   			motorSet(LeftMotT, 50);
   	}

    stopDrive();

    //this delay is to prevent the encoder from counting past zero after we shutoff the drive motors due to the bot still spinning.

    brake(Right);

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

 void turnLeftSlow(int deg)
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
         motorSet(RightMot, 50);
         motorSet(RightMotT, 50);

         motorSet(LeftMot, -50);
         motorSet(LeftMotT, -50);
     }

    stopDrive();

    //this delay is to prevent the encoder from counting past zero after we shutoff the drive motors due to the bot still spinning.

    brake(Left);

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
//front fourth tick
 void closeBlue()
 {
   //shoot the ball at the 3rd flag
   motorSet(PMotor, -127);
   motorSet(PMotor2, -127);
   goForward(250);
   delay(3000);
   loadF();
   delay(500);

   motorStop(PMotor);
   motorStop(PMotor2);

   goForward(-400);

   //turn right towards cap
   turnLeft(270);

   //toggle cap and get ball
   goForward(1000);

   //give enough time to load ball
   delay(500);

   goForward(-100);

   motorStop(LoadServ);

   turnRight(340);

   goForward(-1150);

   turnLeft(40);

   loadF();

   delay(1500);

 }
//auton for far red square, you want fourth mark with back wheel lining up with tick farthest to flag.
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

 //the auto period for the square closest for the flag, back of fourth tick
 void closeRed()
 {
       //shoot the ball at the 3rd flag
       motorSet(PMotor, -127);
       motorSet(PMotor2, -127);
       goForward(250);
       delay(3000);
       loadF();
       delay(500);

       goForward(-400);

       //turn right towards cap
       turnRight(340);

       //toggle cap and get ball
       goForward(1000);

       //give enough time to load ball
       delay(500);

       goForward(-100);

       motorStop(LoadServ);

       turnLeft(6969);

       goForward(-1300);

       turnRight(75);

       loadF();

       delay(1500);

 }

//start on back of fourth tick(farthest from flags), and as close to the center of the field.
void skills()
{
  //go forward and shoot the ball at the 2nd flag

  motorSet(PMotor, -127);
  motorSet(PMotor2, -127);
  goForwardSlow(250);
  delay(3000);
  loadF();
  delay(500);
  motorStop(LoadServ);

  //go back, turn left, then go for the cap
  goForwardSlow(-320);
  turnRightSlow(360);
  goForwardSlow(1050);
  loadF();
  delay(500);
  motorStop(LoadServ);

  //go backward, turn left, go backward, then shoot.
  goForward(-1500);

  goForwardSlow(200);

  turnLeftSlow(330);

  goForwardSlow(-1000);

  loadF();
  delay(1000);
  //motorStop(LoadServ);

  goForwardSlow(-250);

  turnRightSlow(320);
  goForward(-750);
  goForwardSlow(1350);
  delay(250);
  motorStop(LoadServ);

  //get out of cap
  goForwardSlow(-200);

  turnLeftSlow(235);

  loadF();
  delay(1000);
  motorStop(LoadServ);


  turnLeftSlow(360);

  goForward(1250);

  goForwardSlow(-300);

  turnRightSlow(370);


  goForwardSlow(700);

  turnLeftSlow(380);

  goForwardFast(-2850);
}

void autonomous()
{
  skills();
}
