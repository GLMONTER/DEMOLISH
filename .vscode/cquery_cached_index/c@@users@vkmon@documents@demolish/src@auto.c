#include "main.h"

 //a shoot funciton, if the shooter is set right the delay time is just enough to fire the shooter during an auto period
 void shoot()
 {
   	motorSet(PMotor, -127);
   	motorSet(PMotor2, -127);

   	delay(2000);

    motorStop(PMotor);
    motorStop(PMotor2);
 }
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
      shoot();
      goForward(1600);
 }
 //the auto period for the square closest for the flag
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
  //closeRed();
}
