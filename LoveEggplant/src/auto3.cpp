#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

void auto3(){ // blue big 7
  task setCube(locateCube);
  setCube.suspend();
  timer autoTime;
  spread(false);
  sleep(1400);
  Intake(0);
  goForward(55, 630, 2000);
  turnRightWithGyroL(45, 30.2, 1000, true, 0.6, 0.0, 1);
  // turnLeftWithGyroR(47, -32.2, 1030, true, 0.6, 0.0, 1);
  Intake(45);
  Lift(-5);
  if(!rushForward(17, 325, 3600)) goto STOP;
  LeftIntake.spin(fwd, 8, voltageUnits::volt);
  RightIntake.spin(fwd, 12.8, voltageUnits::volt);
  if(!rushForward(30, 340, 3000)) goto STOP;
  Stop(hold);
  Intake(100);
  turnRightWithGyro(65, 242.5, 1800, true, 0.33, 0.00001, 1.25);
  rushForward(65, 800, 2000);
  Stop(hold);
  sleep(200);
  setCube.resume();
  turnLeftWithGyro(50, 172, 1500, false, 0.34, 0.0001, 1.7);
  Lift(0);
  Intake(0);
  // sleep(100);
  // turnRightWithGyro(62, 165.3, 1200, false);
  TrayMotor.startRotateTo(500, deg);
  rushForward(85, 480, 2600);
  Move(10, 80);//50,10
  sleep(150);//600
  Move(-10, -10);
  sleep(100);
  Tray(50);
  Move(5, 5);
  sleep(300);
  Stop();
  Tray(70, coast, 800);
  Tray(55, coast, 1100);
  Tray(40);
  sleep(200);
  Tray(0);
  Move(30, 30);
  sleep(100);
  Move(0, 0);
  sleep(400);
  Tray(0, coast);
  Move(-55, -55);
  LeftMotor1.resetRotation();
  while(autoTime.time(msec) < 15000){
    if(fabs(LeftMotor1.rotation(deg)) > 200)  break;
    sleep(5);
  }
  setCube.stop();
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono30);
  Brain.Screen.printAt(400, 95, "%f", 14800 - autoTime.time(msec));
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Lift(0);
  Tray(0, coast);
  return; 
}