#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

void auto1(){//Blue small with eight tubes
  task setCube(locateCube);
  setCube.suspend();
  timer autoTime;
  spread(false);
  sleep(350);
  Lift(-15);
  LeftMotor1.resetRotation();
  rushForward(65, 150, 1400);
  if(!goForward(45, 700, 2500, 1, 0.007, 0.4)) goto STOP;
  Stop(hold);
  LiftMotor.stop(coast);
  turnRightWithGyro(70, 35.2, 1270, true, 0.43, 0.00001, 0.7);
  Stop(hold);
  if(!rushBackward(100, -720, 3000))  goto STOP;
  Move(-70, -30);
  sleep(390);
  Move(-35, -35);
  sleep(300);
  Move(-20, -20);
  sleep(180);
  Stop();
  Lift(-10);
  LeftMotor1.resetRotation();
  setCube.resume();
  rushForward(60, 170, 2000);
  if(!goForward(37, 825, 4400))  goto STOP;
  Stop(hold);
  Lift(0);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500, false);
    else                    turnLeftWithGyro(60, 0, 500, false);
  }
  else sleep(2300);
  LeftMotor1.resetRotation();
  // if(!goBackward(100, -350, 2000)) goto STOP;
  Intake(0);
  TrayMotor.setVelocity(80.0, rpm);
  TrayMotor.startRotateTo(430, deg);
  turnLeftWithGyro(100, -158.0, 1850, false, 0.33, 0.0, 1.0);
  rushForward(100, 400, 1500);
  rushForward(75, 100, 800);
  rushForward(60, 100, 800);
  Move(40, 40);
  sleep(700);
  Move(-10, -10);
  sleep(50);
  Stop();
  Move(7, 7);
  Tray(90, coast, 600);
  Tray(75, coast, 800);
  Tray(60, coast, 1100);
  Tray(45);
  sleep(10);
  Move(25, 25);
  sleep(100);
  Move(0, 0);
  sleep(250);
  Tray(0, coast);
  Move(-50, -50);
  sleep(500);
  Stop(coast);
  setCube.stop();
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono30);
  Brain.Screen.printAt(400, 95, "%f", 15000 - autoTime.time(msec));
  goto STOP;
STOP:
  Intake(0);
  Lift(0);
  Tray(0, brake);
  Stop(brake);
  return;
}