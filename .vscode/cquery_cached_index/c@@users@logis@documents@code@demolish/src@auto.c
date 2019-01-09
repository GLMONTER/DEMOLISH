#include "main.h"

void reset()
{
    encoderReset(rightEncoder);
    encoderReset(leftEncoder);
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
 	motorStopAll();
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
 	//stop all motors and reset encoders to zero
 	motorStopAll();
 	encoderReset(rightEncoder);
 	encoderReset(leftEncoder);
 }


 //a funciton that turns right, if deg is equal zero or default then turn exactly 90 degrees.
 void turnRight(int deg)
 {
 	if(deg == 0)
 			deg = 280;

 	motorStopAll();
 	encoderReset(rightEncoder);
 	encoderReset(leftEncoder);

 	//turn left to aim at the blue flag
 	while(encoderGet(leftEncoder) > -deg)
 	{
 			motorSet(RightMot, -90);
 			motorSet(RightMotT, -90);

 			motorSet(LeftMot, 90);
 			motorSet(LeftMotT, 90);
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

 			motorSet(LeftMot, -127);
 			motorSet(LeftMotT, -127);
 	}
 	motorStopAll();
 	encoderReset(rightEncoder);
 	encoderReset(leftEncoder);
 }

void farBlue()
{
    goForward(-500);

    motorStopAll();

    turnRight(340);

    goForward(-1400);

}

 void closeBlue()
 {
   shoot(4000);
   motorSet(LoadServ, 127);
   delay(1000);
   motorStopAll();

   turnLeft(310);

   goForward(-750);

   turnLeft(360);

   goForward(-1500);

   reset();
   //shutdown the encoders, power will be lost and any function calls related to the encoder in the function parameters will be ignored.
   encoderShutdown(rightEncoder);
   encoderShutdown(leftEncoder);
 }
 //the auto period for the square closest for the flag
 void closeRed()
 {
       shoot(4000);
       motorSet(LoadServ, 127);
       delay(1000);
       motorStopAll();

       turnRight(310);

       goForward(-750);

       turnRight(360);

       goForward(-1500);

       reset();
       //shutdown the encoders, power will be lost and any function calls related to the encoder in the function parameters will be ignored.
       encoderShutdown(rightEncoder);
       encoderShutdown(leftEncoder);
 }

void autonomous()
{
  farBlue();
}
