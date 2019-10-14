#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

extern int auton;

void runAuto(){
  while (!GyroGetValid()) sleep(10);
  switch(auton){
  case 1:
    auto1();  break;
  case 2:
    auto2();  break;
  case 3:
    auto3();  break;
  case 4:
    auto4();  break;
  case 5:
    auto5();  break;
  case 6:
    auto6();  break;
  default:
    break;
  }

}

void auto1(){
  timer timer1;
  timer1.clear();
  goForward(60, 400, 1000);
  Move(-100, -100);
  sleep(500);
  spread();
  Lift(-3);
  if(!goForward(70, 370, 3000)) goto STOP;
  Stop(hold);
  Lift(0);
  turnRightWithGyroL(40, 117.5, 1200, true, 0.55, 0.0, 1.7);
  Intake(-100);
  if(!rushForward(40, 130, 2000)) goto STOP;
  Stop(hold);
  sleep(650);
  if(!rushBackward(50, -205, 2000)) goto STOP;
  Stop(hold);
  sleep(50);
  turnLeftWithGyro(50, 1, 900, true);
  turnLeftWithGyro(50, 0, 300, false);
  Stop(hold);
  Intake(50);
  rushForward(60, 600, 4000);
  Stop(coast);
  sleep(100);
  Intake(100);
  LeftMotor2.resetRotation();
  while(LeftMotor2.rotation(deg) > -690){
    float speed = 0.11 * LeftMotor2.rotation(deg) + 100;
    Move(-speed, -speed);
  }
  Stop(hold);
  if(GyroGetAngle() < 0)  turnRightWithGyro(100, 0, 90, true);
  turnRightWithGyro(40, 117.5, 1200, true, 0.4, 0.0, 1.3);
  Intake(100);
  rushForward(100, 350, 1100);
  rushForward(40, 340, 2500);
  Stop(hold);
  sleep(300);
  Move(100, -100);
  sleep(350);
  Intake(0);
  // turnRightWithGyro(50, 110, 1500, false);
  turnRightWithGyro(50, 170, 800, false);
  Intake(0);
  Tray(30);
  Move(70, 70);
  sleep(300);
  sleep(350);
  Move(-10, -10);
  sleep(100);
  Move(5, 5);
  Stop();
  Tray(100, coast, 600);
  Tray(80, coast, 800);
  Tray(60, coast, 1100);
  Tray(50);
  sleep(200);
  Move(30, 30);
  sleep(50);
  Move(0, 0);
  sleep(100);
  Tray(0, coast);
  while(timer1.time(msec) < 16000){
    Move(-100, -100);
  }
  Stop(hold);
  goto STOP;
STOP:
  Stop(hold);
  Tray(0, hold);
  Lift(0);
  Intake(0);
}

void auto2(){
//   Lift(-15);
//   if(!goForward(5, 700, 3000))  goto INTERRUPT;
//   // Stop(brake);
//   // sleep(200);
//   // Lift(-5);
//   sleep(5000);
//   backToWall(7, 0, 1800, 0, 0, 0, true);
//   goto INTERRUPT;
//   Move(-20, -20);
//   sleep(0);
//   if(!goForward(42, 700, 4200)) goto INTERRUPT;
//   Stop(hold);
//   sleep(400);
//   if(!goBackward(60, 350, 2000))  goto INTERRUPT;
//   Stop(brake);
//   sleep(600);
//   // if(!turnLeftWithGyro(60, -160, 1200)) goto INTERRUPT;
//   Stop(hold);
//   sleep(200);
//   // Tray(80);
//   goForward(50, 120, 500);
//   // Tray(0, hold);
//   Move(20, 20);
//   sleep(500);
//   Move(-50, -50);
//   sleep(50);
//   Move(0, 0);
//   goto INTERRUPT;
//   Tray(127);
//   sleep(400);
//   Intake(-20);
//   Tray(80);
//   sleep(100);
//   Intake(0);
//   sleep(250);
//   Stop();
//   return;
// INTERRUPT:
//   Stop();
//   Intake(0);
//   return;
}

void auto3(){
  float angleErr = 0.0;
  spread();
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
  }
  if(!goForward(35, 760, 2300)) goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  // turnRightWithGyro(60, 46.0, 650, true);
  turnRightWithGyro(60, 46.5, 850, true, 0.33, 0.00001, 1.1);
  Stop(hold);
  sleep(100);
  if(!rushBackward(100, -700, 3000))  goto INTERRUPT;
  Move(-45, -30);
  sleep(760);
  Move(-20, -20);
  sleep(410);
  Stop();
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    float speed = 180 - LeftMotor1.rotation(deg);
    Move(CONSTRAIN(speed, 42, 90), CONSTRAIN(speed, 42, 90));
  }
  if(!goForward(32, 820, 3800))  goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  sleep(90);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
    else                    turnLeftWithGyro(60, 0, 500, false);
  }
  LeftMotor1.resetRotation();
  if(!goBackward(100, -330, 2000)) goto INTERRUPT;
  Intake(0);
  TrayMotor.startRotateTo(320, deg);
  turnLeftWithGyro(85, -185.0 - angleErr, 1450, false);
  Move(70, 70);
  sleep(650);
  Move(-10, -10);
  sleep(100);
  Stop();
  Tray(100, coast, 600);
  Tray(80, coast, 800);
  Tray(60, coast, 1100);
  Tray(50);
  sleep(230);
  Move(30, 30);
  sleep(200);
  Move(0, 0);
  sleep(450);
  Tray(0, coast);
  Move(-100, -100);
  sleep(700);
  goto INTERRUPT;
INTERRUPT:
  Intake(0);
  Stop(brake);
  return;
}

void auto4(){
//   timer timer1;
//   timer1.clear();
//   spread();
//   goForward(70, 600, 3000);
//   // if(!rushForward(70, 400, 1500)) goto INTERRUPT;
//   // if(!rushForward(50, 100, 1700)) goto INTERRUPT;
//   // if(!rushForward(30, 100, 900))   goto INTERRUPT;
//   Stop(hold);
//   Intake(2);
//   // turnLeftWithGyro(50, -114, 1500, false);
//   turnRightWithGyro(50, 114, 1500, false);
//   goto INTERRUPT;
//   Stop(brake);
//   Intake(-50);
//   rushForward(40, 130, 2000);
//   Stop(hold);
//   sleep(680);
//   rushBackward(50, -130, 2000);
//   Stop(brake);
//   sleep(50);
//   turnLeftWithGyro(50, -1, 850, true);
//   turnRightWithGyro(50, 1, 300, true);
//   Stop(hold);
//   Intake(50);
//   rushForward(60, 600, 4000);
//   Stop(coast);
//   sleep(50);
//   LeftMotor2.resetRotation();
//   while(LeftMotor2.rotation(deg) > -600){
//     float speed = 0.137 * LeftMotor2.rotation(deg) + 100;
//     Move(-speed, -speed);
//   }
//   Stop(hold);
//   if(GyroGetAngle() < 0)  turnRightWithGyro(100, 0, 90, true);
//   turnRightWithGyro(100, 112, 1800, true);
//   Intake(100);
//   rushForward(35, 790, 2500);
//   Stop(hold);
//   sleep(300);
//   Intake(0);
//   Move(100, -100);
//   sleep(300);
//   Tray(46);
//   turnRightWithGyro(50, 110, 1500, false);
//   // turnRightWithGyro(100, 170, 1200, false);
//   Move(70, 70);
//   sleep(300);
//   Tray(0, hold);
//   sleep(350);
//   Move(-10, -10);
//   sleep(100);
//   Move(5, 5);
//   Stop();
//   Tray(100, coast, 600);
//   Tray(80, coast, 800);
//   Tray(60, coast, 1100);
//   Tray(50);
//   sleep(200);
//   Move(30, 30);
//   sleep(50);
//   Move(0, 0);
//   sleep(100);
//   Tray(0, coast);
//   while(timer1.time(msec) < 15000){
//     Move(-100, -100);
//   }
//   Stop(hold);
//   sleep(700);
// INTERRUPT:
//   Intake(0);
//   Stop(hold);
//   Tray(0, coast);
//   return;
}

void auto5(){//8cube
  timer timer1;
  timer1.clear();
  spread();
  float angleErr = 0.0;
  spread();
  RightMotor1.resetRotation();
  while(RightMotor1.rotation(deg) < 150){
    Move(200 - RightMotor1.rotation(deg), 200 - RightMotor1.rotation(deg));
  }
  Lift(-3);
  if(!goForward(35, 790, 2300)) goto STOP;
  Lift(0);
  Stop(hold);
  angleErr += GyroGetAngle();
  turnLeftWithGyro(60, -46.5, 850, true, 0.33, 0.00001, 1.1);
  Stop(hold);
  sleep(100);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) > -700){//500
    Move(-100, -100);
  }
  Move(-30, -75);
  sleep(600);
  Move(-20, -20);
  sleep(150);
  Stop();
  RightMotor1.resetRotation();
  while(RightMotor1.rotation(deg) < 150){
    float speed = 180 - LeftMotor1.rotation(deg);
    Move(CONSTRAIN(speed, 42, 90), CONSTRAIN(speed, 42, 90));
  }
  Lift(-5);
  if(!goForward(30, 950, 4500))  goto STOP;
  Lift(0);
  Stop(hold);
  angleErr += GyroGetAngle();
  sleep(90);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnLeftWithGyro(60, 0, 500, true);
    else                    turnRightWithGyro(60, 0, 500 ,true);
  }
  if(!goBackward(100, -370, 2500)) goto STOP;
  Intake(-20);
  turnRightWithGyro(85, 174.3 - angleErr, 1500, false, 0.33, 0.00001, 1.25);
  Stop(hold);
  Intake(0);
  TrayMotor.startRotateTo(320, deg);
  Move(60, 60);
  sleep(670);
  Move(70, 0);
  sleep(50);
  Move(0, 70);
  sleep(50);
  Move(-10, -10);
  sleep(100);
  Stop();
  Tray(70, coast, 600);
  Intake(-10);
  Tray(60, coast, 800);
  Intake(0);
  Tray(50, coast, 1060);
  Tray(30);
  Move(30, 30);
  sleep(150);
  Move(0, 0);
  sleep(450);
  Tray(0, coast);
  Move(-100, -100);
  sleep(700);
  while(timer1.time(msec) < 16500);
  goto STOP;
STOP:
  Stop(hold);
  Lift(0);
  Intake(0);
  Tray(0, hold);
}

void auto6(){
  timer timer1;
  timer1.clear();
  goForward(60, 400, 1000);
  Move(-100, -100);
  spread();
  Lift(-3);
  goForward(70, 640, 3000);
  Stop(hold);
  Lift(0);
  Move(-10, -10);
  sleep(10);
  Stop(hold);
  Intake(2);
  Stop(hold);
  Move(-100, 100);
  sleep(500);
  turnLeftWithGyro(100, -117.5, 1500, true, 0.35, 0.0, 0.34);
  Stop(hold);
  goto STOP;
  Stop(brake);
  Intake(-50);
  rushForward(40, 130, 2000);
  Stop(hold);
  sleep(680);
  rushBackward(50, -130, 2000);
  Stop(brake);
  sleep(50);
  turnRightWithGyro(50, -1, 850, true);
  turnLeftWithGyro(50, 1, 300, true);
  Stop(hold);
  Intake(50);
  rushForward(60, 600, 4000);
  Stop(coast);
  sleep(50);
  LeftMotor2.resetRotation();
  while(LeftMotor2.rotation(deg) > -690){
    float speed = 0.137 * LeftMotor2.rotation(deg) + 100;
    Move(-speed, -speed);
  }
  Stop(hold);
  if(GyroGetAngle() < 0)  turnRightWithGyro(100, 0, 90, true);
  turnLeftWithGyro(100, -117.5, 1500, true, 0.35, 0.0, 0.34);
  Intake(100);
  rushForward(35, 790, 2500);
  goto STOP;
//   Stop(hold);
//   sleep(300);
//   Intake(0);
//   Move(100, -100);
//   sleep(300);
//   Tray(46);
//   turnRightWithGyro(50, 110, 1500, false);
//   // turnRightWithGyro(100, 170, 1200, false);
//   Move(70, 70);
//   sleep(300);
//   Tray(0, hold);
//   sleep(350);
//   Move(-10, -10);
//   sleep(100);
//   Move(5, 5);
//   Stop();
//   Tray(100, coast, 600);
//   Tray(80, coast, 800);
//   Tray(60, coast, 1100);
//   Tray(50);
//   sleep(200);
//   Move(30, 30);
//   sleep(50);
//   Move(0, 0);
//   sleep(100);
//   Tray(0, coast);
//   while(timer1.time(msec) < 15000){
//     Move(-100, -100);
//   }
//   Stop(hold);
//   sleep(700);
STOP:
  Intake(0);
  Stop(hold);
  Tray(0, coast);
  return;
}