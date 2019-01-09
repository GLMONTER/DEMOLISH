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
 	while(encoderGet(leftEncoder) < deg)
 	{
 			motorSet(RightMot, -127);
 			motorSet(RightMotT, -127);

 			motorSet(LeftMot, 127);
 			motorSet(LeftMotT, 127);
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
    goForward(1600);

    turnRight(0);

    goForward(2000);
}

 void closeBlue()
 {
     shoot(3000);
     motorSet(LoadServ, 127);
     delay(1000);
     motorStopAll();

     goForward(1600);
 }
 //the auto period for the square closest for the flag
 void closeRed()
 {
       shoot(3000);
       motorSet(LoadServ, 127);
       delay(1000);
       motorStopAll();

       //go forward from initial square
       goForward(1200);

      // goForward(-1200);

       /*
 			 turnRight(0);

 			 goForward(2000);
       motorStopAll();
       encoderReset(rightEncoder);
       encoderReset(leftEncoder);

*/
       reset();
       //shutdown the encoders, power will be lost and any function calls related to the encoder in the function parameters will be ignored.
       encoderShutdown(rightEncoder);
       encoderShutdown(leftEncoder);
 }

void autonomous()
{
  //closeRed();
}
