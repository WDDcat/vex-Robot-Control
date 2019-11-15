#include "vex.h"
#include "motorControl.h"
#include "chassisAutoControl.h"
#include "auto.h"
#include "GyroLib.h"

extern int auton;

void runAuto(){
  while (!GyroGetValid()) sleep(10);
  switch(auton){
  case -1:
    autoTest(); break;
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
    auto7();  break;
  case 8:
    auto8();  break;
  default:
    break;
  }

}

void auto1(){//Blue small with eight tubes
  spread();
  sleep(350);
  Lift(-15);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
  }
  if(!goForward(32, 790, 2700)) goto STOP;
  Stop(hold);
  Lift(0);
  sleep(200);
  turnRightWithGyro(60, 48.7, 870, true, 0.33, 0.00001, 1.1);
  Stop(hold);
  sleep(100);
  if(!rushBackward(100, -700, 3000))  goto STOP;
  Move(-60, -30);
  sleep(460);
  Move(-30, -30);
  sleep(380);
  Stop();
  Lift(-10);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    float speed = 180 - LeftMotor1.rotation(deg);
    Move(CONSTRAIN(speed, 30, 90), CONSTRAIN(speed, 30, 90));
  }
  if(!goForward(23, 870, 4400))  goto STOP;
  Stop(hold);
  Lift(0);
  sleep(100);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
    else                    turnLeftWithGyro(60, 0, 500, false);
  }
  LeftMotor1.resetRotation();
  // if(!goBackward(100, -350, 2000)) goto STOP;
  Move(-85, 85);
  sleep(750);
  Intake(0);
  TrayMotor.startRotateTo(440, deg);
  turnLeftWithGyro(100, -194.0, 1550, false, 0.37, 0.0, 0.95);
  rushForward(100, 400, 1500);
  rushForward(70, 100, 800);
  rushForward(50, 100, 800);
  Move(40, 40);
  sleep(400);
  Move(-10, -10);
  sleep(100);
  Stop();
  Move(5, 5);
  Tray(70, coast, 600);
  Tray(60, coast, 800);
  Tray(50, coast, 1100);
  Tray(35);
  sleep(230);
  Move(30, 30);
  sleep(200);
  Move(0, 0);
  sleep(250);
  Tray(0, coast);
  Move(-50, -50);
  sleep(700);
  Stop(coast);
STOP:
  Intake(0);
  Stop(brake);
  return;
}

void auto2(){ //Blue Big 8
  spread();
  Intake(0);
  if(!rushForward(50, 630, 2000)) goto STOP;
  turnRightWithGyroL(40, 30.2, 1000, true, 0.6, 0.0, 1);
  Intake(45);
  Lift(-5);
  if(!rushForward(15, 275, 3300)) goto STOP;
  Intake(100);
  if(!rushForward(40, 380, 2500)) goto STOP;
  Stop(hold);
  turnRightWithGyro(70, 235.5, 1800, true, 0.33, 0.00001, 1.25);
  Lift(0);
  if(!rushForward(50, 700, 2500)) goto STOP;
  Stop(hold);
  sleep(250);
  turnLeftWithGyro(40, 119, 1400, true, 0.34, 0.0001, 1.7);
  rushForward(60, 670, 1900);
  Stop(hold);
  sleep(100);
  turnRightWithGyro(62, 165.3, 1200, false);
  Intake(0);
  TrayMotor.startRotateTo(240, deg);
  Move(40, 40);
  sleep(400);
  Move(-10, -10);
  sleep(50);
  Move(5, 5);
  sleep(500);
  Stop();
  Tray(60, coast, 800);
  Tray(40, coast, 1100);
  Tray(20);
  sleep(350);
  Tray(0);
  Move(30, 30);
  sleep(100);
  Move(0, 0);
  sleep(200);
  Tray(0, coast);
  Move(-70, -70);
  sleep(700);
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Tray(0, coast);
  return;
}

void auto3(){ // blue big 7
  spread();
  Intake(0);
  if(!rushForward(50, 630, 2000)) goto STOP;
  turnRightWithGyroL(40, 30.2, 1000, true, 0.6, 0.0, 1);
  Intake(45);
  Lift(-5);
  if(!rushForward(15, 275, 3300)) goto STOP;
  Intake(100);
  if(!rushForward(40, 380, 2500)) goto STOP;
  Stop(hold);
  turnRightWithGyro(70, 235.5, 1800, true, 0.33, 0.00001, 1.25);
  Lift(0);
  if(!rushForward(50, 700, 2500)) goto STOP;
  Stop(hold);
  sleep(250);
  turnLeftWithGyro(40, 156, 1500, false, 0.34, 0.0001, 1.7);
  rushForward(60, 550, 1900);
  Stop(hold);
  // sleep(100);
  // turnRightWithGyro(62, 165.3, 1200, false);
  Intake(0);
  TrayMotor.startRotateTo(240, deg);
  Move(10, 40);
  sleep(800);
  Move(-10, -10);
  sleep(100);
  Move(5, 5);
  sleep(500);
  Stop();
  Tray(60, coast, 800);
  Tray(40, coast, 1100);
  Tray(20);
  sleep(350);
  Tray(0);
  Move(30, 30);
  sleep(100);
  Move(0, 0);
  sleep(200);
  Tray(0, coast);
  Move(-70, -70);
  sleep(700);
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Tray(0, coast);
  return;
}

void auto4(){

}

void auto5(){//Red small with eight tubes
  spread();
  sleep(350);
  Lift(-15);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
  }
  if(!goForward(35, 790, 2700)) goto STOP;
  Stop(hold);
  Lift(0);
  sleep(200);
  turnLeftWithGyro(60, -47.7, 870, true, 0.33, 0.00001, 1.1);
  Stop(hold);
  sleep(100);
  if(!rushBackward(100, -700, 3000))  goto STOP;
  Move(-30, -45);
  sleep(660);
  Move(-20, -20);
  sleep(310);
  Stop();
  Lift(-10);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    float speed = 180 - LeftMotor1.rotation(deg);
    Move(CONSTRAIN(speed, 30, 90), CONSTRAIN(speed, 30, 90));
  }
  if(!goForward(25, 870, 4400))  goto STOP;
  Stop(hold);
  Lift(0);
  sleep(100);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
    else                    turnLeftWithGyro(60, 0, 500, false);
  }
  LeftMotor1.resetRotation();
  if(!goBackward(100, -350, 2000)) goto STOP;
  Intake(0);
  TrayMotor.startRotateTo(440, deg);
  turnRightWithGyro(85, 182.0, 1550, false);
  Move(75, 75);
  sleep(600);
  Move(-10, -10);
  sleep(100);
  Stop();
  Move(5, 5);
  Tray(80, coast, 600);
  Tray(65, coast, 800);
  Tray(50, coast, 1100);
  Tray(30);
  sleep(230);
  Move(30, 30);
  sleep(200);
  Move(0, 0);
  sleep(250);
  Tray(0, coast);
  Move(-50, -50);
  sleep(700);
  Stop(coast);
STOP:
  Intake(0);
  Stop(brake);
  return;
}

void auto6(){//red Big 8
  spread();
  Intake(0);
  if(!rushForward(50, 630, 2000)) goto STOP;
  turnLeftWithGyroR(40, -30.2, 1000, true, 0.6, 0.0, 1);
  Intake(37);
  Lift(-5);
  if(!rushForward(25, 375, 3300)) goto STOP;
  Intake(100);
  if(!rushForward(40, 280, 2500)) goto STOP;
  Stop(hold);
  turnLeftWithGyro(70, -235.5, 1800, true, 0.33, 0.00001, 1.25);
  Lift(0);
  if(!rushForward(45, 700, 2500)) goto STOP;
  Stop(hold);
  sleep(250);
  turnRightWithGyro(40, -119, 1400, true, 0.34, 0.0001, 1.7);
  rushForward(54, 670, 1900);
  Stop(hold);
  sleep(100);
  turnLeftWithGyro(62, -165.3, 1200, false);
  Intake(0);
  TrayMotor.startRotateTo(240, deg);
  Move(70, 70);
  sleep(400);
  Move(-10, -10);
  sleep(50);
  Move(5, 5);
  sleep(500);
  Stop();
  Tray(85, coast, 600);
  Tray(65, coast, 800);
  Tray(55, coast, 1100);
  Tray(30);
  sleep(350);
  Tray(0);
  Move(30, 30);
  sleep(250);
  Tray(0, coast);
  Move(-70, -70);
  sleep(700);
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Tray(0, coast);
  return;
}

void auto7(){
  
}

void auto8(){
  
}

void autoTest(){
  timer T1;
  T1.clear();
  spread();
  Lift(-15);
  rushForward(90, 180, 1500, true);
  rushForward(27, 570, 3500, false);
  Stop(hold);
  Lift(0);
  while(GyroGetAngle() < 50.7){
    LeftMotor1.spin(fwd, 58 - GyroGetAngle(), rpm);//62
    LeftMotor2.spin(fwd, 58 - GyroGetAngle(), rpm);
    RightMotor1.stop(hold);
    RightMotor2.stop(hold);
  }
  Stop(hold);
  if(!rushBackward(100, -600, 3000, true))  goto STOP;
  Move(-50, -50);
  sleep(200);
  Move(-70, -30);
  sleep(500);
  Move(-20, -20);
  sleep(15);
  Stop();
  goto STOP;
  rushForward(86, 150, 1500, true);
  rushForward(22, 710, 4400, false);
  Stop(hold);
  Lift(0);
  Intake(0, hold);
  TrayMotor.startRotateTo(560, deg);
  turnLeftWithGyro(100, -170.0, 1550, false, 0.39, 0.0, 0.42);
  rushForward(100, 300, 1800, true);
  rushForward(60, 220, 1500, false);
  Move(40, 40);
  sleep(50);
  Move(-10, -10);
  sleep(100);
  Stop();
  Move(5, 5);
  Tray(80, coast, 750);
  Tray(75, coast, 800);
  Tray(70, coast, 1100);
  Tray(35);
  Move(15, 15);
  sleep(400);
  Tray(0, coast);
  Move(-50, -50);
  while(T1.time(msec) < 15500){
    sleep(5);
  }
  Stop(coast);
STOP:
  Intake(0);
  Stop(coast);
  Tray(0, coast);
  Lift(0);
  return;
}