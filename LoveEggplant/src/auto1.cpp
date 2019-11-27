#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

void auto1(){//Blue small with eight tubes
//   spread(false);
//   sleep(350);
//   Lift(-15);
//   LeftMotor1.resetRotation();
//   while(LeftMotor1.rotation(deg) < 150){
//     Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
//   }
//   if(!goForward(32, 790, 2700)) goto STOP;
//   Stop(hold);
//   Lift(0);
//   sleep(200);
//   turnRightWithGyro(60, 48.7, 870, true, 0.33, 0.00001, 1.1);
//   Stop(hold);
//   sleep(100);
//   if(!rushBackward(100, -700, 3000))  goto STOP;
//   Move(-60, -30);
//   sleep(460);
//   Move(-30, -30);
//   sleep(380);
//   Stop();
//   Lift(-10);
//   LeftMotor1.resetRotation();
//   while(LeftMotor1.rotation(deg) < 150){
//     float speed = 180 - LeftMotor1.rotation(deg);
//     Move(CONSTRAIN(speed, 30, 90), CONSTRAIN(speed, 30, 90));
//   }
//   if(!goForward(23, 870, 4400))  goto STOP;
//   Stop(hold);
//   Lift(0);
//   sleep(100);
//   if(GyroGetAbsAngle() > 10){
//     if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
//     else                    turnLeftWithGyro(60, 0, 500, false);
//   }
//   LeftMotor1.resetRotation();
//   // if(!goBackward(100, -350, 2000)) goto STOP;
//   Move(-85, 85);
//   sleep(750);
//   Intake(0);
//   TrayMotor.startRotateTo(440, deg);
//   turnLeftWithGyro(100, -194.0, 1550, false, 0.37, 0.0, 0.95);
//   rushForward(100, 400, 1500);
//   rushForward(70, 100, 800);
//   rushForward(50, 100, 800);
//   Move(40, 40);
//   sleep(400);
//   Move(-10, -10);
//   sleep(100);
//   Stop();
//   Move(5, 5);
//   Tray(70, coast, 600);
//   Tray(60, coast, 800);
//   Tray(50, coast, 1100);
//   Tray(35);
//   sleep(230);
//   Move(30, 30);
//   sleep(200);
//   Move(0, 0);
//   sleep(250);
//   Tray(0, coast);
//   Move(-50, -50);
//   sleep(700);
//   Stop(coast);
// STOP:
//   Intake(0);
//   Stop(brake);
//   return;
}