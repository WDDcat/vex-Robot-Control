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
  case 7:
    auto7(); break;
  case 8:
    auto8(); break;
  default:
    break;
  }

}

void auto1(){
  timer autoTimer;
  autoTimer.clear();
  spread();
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
  }
  if(!goForward(38, 790, 2700)) goto STOP;
  Stop(hold);
  sleep(650);
  turnRightWithGyro(60, 47.7, 870, true, 0.33, 0.00001, 1.1);
  Stop(hold);
  sleep(100);
  if(!rushBackward(100, -700, 3000))  goto STOP;
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
  if(!goForward(27, 870, 4400))  goto STOP;
  Stop(hold);
  sleep(500);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
    else                    turnLeftWithGyro(60, 0, 500, false);
  }
  LeftMotor1.resetRotation();
  if(!goBackward(100, -350, 2000)) goto STOP;
  Intake(0);
  TrayMotor.startRotateTo(320, deg);
  turnLeftWithGyro(85, -187.0, 1550, false);
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
  while(autoTimer.time(msec) < 15000){
    Move(-100, -100);
  }
  // Move(-100, -100);
  // sleep(700);
  Stop(coast);
STOP:
  Intake(0);
  Stop(brake);
  return;
}

void auto2(){
  spread();
  if(!rushForward(50, 630, 2000)) goto STOP;
  turnRightWithGyroL(40, 32.5, 1000, true, 0.6, 0.0, 1);
  Intake(50);
  if(!rushForward(60, 200, 2000)) goto STOP;
  if(!rushForward(26, 270, 2500)) goto STOP;
  Intake(100);
  if(!rushForward(26, 200, 2500)) goto STOP;
  Stop(hold);
  turnRightWithGyro(70, 235.5, 1700, true, 0.33, 0.00001, 1.25);
  if(!rushForward(40, 700, 2500)) goto STOP;
  turnLeftWithGyro(40, 117, 1400, true, 0.34, 0.0001, 1.7);
  rushForward(50, 670, 1900);
  turnRightWithGyro(60, 171.3, 1200, false);
  Intake(0);
  TrayMotor.startRotateTo(240, deg);
  Move(40, 40);
  sleep(400);
  Move(-10, -10);
  sleep(100);
  Move(9, 9);
  sleep(500);
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
  Move(-100, -100);
  // while(timer1.time(msec) < 15000){
    // Move(-100, -100);
  // }
  sleep(700);
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Tray(0, coast);
  return;
}

void auto3(){
  
}

void auto4(){

}

void auto5(){
  
}

void auto6(){
  
}

void auto7(){
  
}

void auto8(){
  
}