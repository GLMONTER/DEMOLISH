#include "main.h"

//resets the left and right encoder.
void resetAllENC()
{
    encoderReset(rightEncoder);
    encoderReset(leftEncoder);
}

//simply stops all main drive motors.
void stopDrive()
{
    motorStop(LeftMot);
    motorStop(LeftMotT);
    motorStop(RightMot);
    motorStop(RightMotT);
}

//the braking function, it takes a enumeration as a brake type, depending on the brake mode,
//the motors will go against how the robot is driving, for 50 ms, then the motors will stop, then the encoders will reset.
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
    resetAllENC();
}

//turn on the loader for the specified amount of miliseconds then turns of the loader.
void load(unsigned int mili)
{
    motorSet(LoadServ, 127);
    motorSet(LoadServ2, 127);
    delay(mili);
    motorStop(LoadServ);
    motorStop(LoadServ2);
}

//turns on the loader.
void loadF()
{
    motorSet(LoadServ, 127);
    motorSet(LoadServ2, 127);
}

//turns on the shooter and wait the specified amount of miliseconds to give the shooter time to spin up.
void shoot(unsigned int mili)
{
    motorSet(PMotor, -127);
    motorSet(PMotor2, -127);
    delay(mili);
}

 //go a direction for the specified amount of ticks, negative or positive for backward and forward.
 void goDirection(int rotDeg)
 {
    stopDrive();

   	resetAllENC();
   	//if rotDeg less than zero then go backward until the encoder reads rotDeg
   	if(rotDeg < 0)
   	{
     		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) >rotDeg)
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

   	resetAllENC();
 }

 //same as "goDirection", but runs the motor at half the speed.
 void goDirectionSlow(int rotDeg)
 {
    stopDrive();

   	resetAllENC();

   	//if rotDeg less than zero then go backward until the encoder reads rotDeg
   	if(rotDeg < 0)
   	{
     		while(encoderGet(rightEncoder) > rotDeg && encoderGet(leftEncoder) > rotDeg)
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
     		while(encoderGet(rightEncoder) < rotDeg && encoderGet(leftEncoder) < rotDeg)
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

   	resetAllENC();
 }

 //same as "goDirection", but increases motor speed from 100 to 127.
 void goDirectionFast(int rotDeg)
 {
    stopDrive();

   	resetAllENC();

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

   	resetAllENC();
 }

 //turn right for the speciifed amount of ticks, defaults are in place as 260 and 305, I need to revise the defaults.
 void turnRight(int deg)
 {
     if(deg == 0)
        deg = 260;
     if(deg == 6969)
        deg = 305;

     stopDrive();

     resetAllENC();

     //turn left to aim at the blue flag
     while(encoderGet(rightEncoder) > (deg * -1))
     {
         motorSet(RightMot, -100);
         motorSet(RightMotT, -100);

         motorSet(LeftMot, 100);
         motorSet(LeftMotT, 100);
     }

     stopDrive();
     brake(Right);

     resetAllENC();
 }

 //same as "turnRight", but slows the motors down by 50%.
 void turnRightSlow(int deg)
 {
    stopDrive();

   	if(deg == 0)
   		deg = 260;
    if(deg == 6969)
      deg = 305;

   	resetAllENC();

   	while(encoderGet(rightEncoder) > (deg * -1))
   	{
   			motorSet(RightMot, -50);
   			motorSet(RightMotT, -50);

   			motorSet(LeftMot, 50);
   			motorSet(LeftMotT, 50);
   	}

    stopDrive();
    brake(Right);

   	resetAllENC();
 }

 void turnLeftSlow(int deg)
 {
     stopDrive();

      if(deg == 0)
         deg = 260;
      if(deg == 6969)
         deg = 305;

     resetAllENC();

     while(encoderGet(rightEncoder) < deg)
     {
         motorSet(RightMot, 50);
         motorSet(RightMotT, 50);

         motorSet(LeftMot, -50);
         motorSet(LeftMotT, -50);
     }

     stopDrive();
     brake(Left);

     resetAllENC();
 }


 void turnLeft(int deg)
 {
    stopDrive();

   	if(deg == 0)
   		 deg = 260;
    if(deg == 6969)
       deg = 305;

   	resetAllENC();

   	while(encoderGet(rightEncoder) < deg)
   	{
   			motorSet(RightMot, 100);
   			motorSet(RightMotT, 100);

   			motorSet(LeftMot, -100);
   			motorSet(LeftMotT, -100);
   	}

    stopDrive();
    brake(Left);

   	resetAllENC();
 }

//line up with 4th block with back tick farthest to flag.
void farBlue()
{
    //shoot
    shoot(4000);
    load(750);
    motorStop(PMotor);
    motorStop(PMotor2);

    //allign with platform, turn right, and climb.
    goDirection(400);
    turnRight(400);
    goDirectionFast(-1800);
}
//front fourth tick
 void closeBlue()
 {
     //shoot the ball at the 3rd flag
     motorSet(PMotor, -127);
     motorSet(PMotor2, -127);
     goDirection(250);
     delay(3000);
     load(500);

     goDirection(-400);

     //turn left towards cap
     turnLeft(270);

     //toggle cap and get ball
     goDirection(1000);

     //give enough time to load ball
     load(500);

     //go back to allign with platform.
     goDirection(-150);

     //turn right and climb up.
     turnRight(340);
     goDirectionFast(-1250);

     //turn left and shoot
     turnLeft(60);
     load(1500);
 }

//auton for far red square, you want fourth mark with back wheel lining up with tick farthest to flag.
void farRed()
{
    //shoot
    shoot(4000);
    load(750);
    motorStop(PMotor);
    motorStop(PMotor2);

    //go forward to line up with platform, turn left then climb
    goDirection(480);
    turnLeft(350);
    goDirection(-1850);
}

 //the auto period for the square closest for the flag, back of fourth tick
 void closeRed()
 {
     //shoot the ball at the 3rd flag
     motorSet(PMotor, -127);
     motorSet(PMotor2, -127);
     goDirectionSlow(250);
     delay(3000);
     loadF();
     delay(1000);

     //go backwards
     goDirectionSlow(-400);

     //turn right towards cap
     turnRightSlow(300);

     //get ball from cap
     goDirectionSlow(1000);

     //give enough time to load ball
     delay(700);

     motorStop(LoadServ);
     motorStop(LoadServ2);

     turnLeftSlow(210);

     goDirection(300);

     load(1500);

     goDirection(-300);

     turnRight(170);

     //get back enough to allign with the alliance platform.
     goDirectionSlow(-200);

     //turb Right to get ready to climb alliance platform.
     turnRightSlow(340);

     //actaully climb.
     goDirection(800);

     //turn right to shoot the middle top flag.
    // turnRightSlow(75);

     //turn  on the loader
    // load(1500);
 }

//start on back of fourth tick(farthest from flags), and as close to the center of the field.
void skills()
{
    //go forward and shoot the ball at the 2nd flag
    motorSet(PMotor, -127);
    motorSet(PMotor2, -127);
    goDirectionSlow(250);
    delay(3000);
    load(500);

    //go back, turn left, then go for the cap
    goDirectionSlow(-320);
    turnRightSlow(360);
    goDirectionSlow(1050);
    loadF();
    delay(500);
    motorStop(LoadServ);

    //go backward and realign on wall, go forward off wall, turn left, go backward, then shoot.
    goDirection(-1500);
    goDirectionSlow(200);
    turnLeftSlow(330);
    goDirectionSlow(-1000);
    loadF();
    delay(1000);

    //realign with square, turn right, push against wall for realign, go forward, get ball from cap.
    goDirectionSlow(-250);

    turnRightSlow(320);
    goDirection(-750);
    goDirectionSlow(1350);
    delay(250);
    motorStop(LoadServ);

    //get out of cap
    goDirectionSlow(-200);

    //turn left and shoot middle top flag.
    turnLeftSlow(235);
    load(1000);

    //turn left and go forward to realign on wall, turn right, go forward, then left. Should be alligned for climbing.
    turnLeftSlow(360);
    goDirection(1250);
    goDirectionSlow(-300);
    turnRightSlow(370);
    goDirectionSlow(700);
    turnLeftSlow(380);

    //climb, hopefully.
    goDirectionFast(-2850);
}

//what actaully runs when the competition switch activates the autonmous function.
void autonomous()
{
    closeRed();

    //disable the encoders so we can free up some processing power.
    encoderShutdown(rightEncoder);
    encoderShutdown(leftEncoder);
}
