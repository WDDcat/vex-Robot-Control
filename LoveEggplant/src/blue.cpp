#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

void Blue(){ // blue big 7
  task setCube(locateCube);
  setCube.suspend();
  timer autoTime;
  spread(false);
  sleep(1400);
  Intake(0);
  goForward(63, 630, 2000);
  Lift(-10);
  turnRightWithGyroL(45, 28, 1000, true, 0.59, 0.0, 1);
  Intake(43);
  LeftIntake.spin(fwd, 0.128 * 20, voltageUnits::volt);
  Lift(-5);
  if(!rushForward(28, 225, 3600)) goto STOP;
  Intake(70);
  if(!rushForward(30, 452, 3000)) goto STOP;
  Stop(hold);
  sleep(100);
  Intake(100);
  turnRightWithGyro(65, 195, 1800, true, 0.32, 0.00001, 1.27);
  rushForward(70, 735, 2000);
  Stop(coast);
  Move(-8, -8);
  sleep(150);
  Intake(100);
  setCube.resume();
  turnLeftWithGyro(50, 120, 2000, false, 0.39, 0.0001, 0.60);
  Lift(0);
  Intake(0);
  // sleep(100);
  // turnRightWithGyro(62, 165.3, 1200, false);
  rushForward(80, 460, 3000);
  Move(5, 50);//50,10
  sleep(321);//600
  Move(15, 15);
  sleep(300);
  Move(-10, -10);
  sleep(100);
  Tray(50);
  Move(5, 5);
  sleep(300);
  Stop();
  Tray(70, coast, 800);
  Tray(60, coast, 1100);
  Tray(40);
  sleep(170);
  Tray(0);
  Move(0, 0);
  sleep(500);
  Move(-70, -70);
  LeftMotor1.resetRotation();
  while(autoTime.time(msec) < 15000){
    if(fabs(LeftMotor1.rotation(deg)) > 95)  break;
    sleep(5);
  }
  Tray(0, coast);
  setCube.stop();
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono30);
  Brain.Screen.printAt(400, 95, "%f", 15000 - autoTime.time(msec));
  goto STOP;
STOP:
  Intake(0);
  Stop(coast);
  Lift(0);
  Tray(0, coast);
  return; 
}