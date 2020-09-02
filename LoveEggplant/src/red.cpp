#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

void Red(){
  task setCube(locateCube);
  setCube.suspend();
  timer autoTime;
  spread(false);
  sleep(1400);
  Intake(0);
  goForward(63, 620, 2000);
  turnLeftWithGyroR(45, -30.2, 1000, true, 0.59, 0.0, 1);
  Intake(45);
  RightIntake.stop();
  Lift(-5);
  if(!rushForward(20, 225, 3600)) goto STOP;
  Intake(70);
  LeftIntake.spin(fwd, 0.128 * 40, voltageUnits::volt);
  if(!rushForward(35, 445, 3000)) goto STOP;
  Stop(hold);
  sleep(100);
  Intake(100);
  turnLeftWithGyro(65, -246, 1800, true, 0.32, 0.00001, 1.27);
  rushForward(70, 735, 2000);
  Stop(coast);
  Move(-3, -3);
  sleep(150);
  Intake(100);
  setCube.resume();
  turnRightWithGyro(50, -165, 2000, false, 0.33, 0.0001, 0.9);
  Lift(0);
  Intake(0);
  // sleep(100);
  // turnRightWithGyro(62, 165.3, 1200, false);
  rushForward(70, 550, 3000);
  Move(40, 5);//50,10
  sleep(321);//600
  Move(-10, -10);
  sleep(100);
  Tray(50);
  Move(5, 5);
  sleep(300);
  Stop();
  Tray(70, coast, 800);
  Tray(60, coast, 1100);
  Tray(33);
  sleep(350);
  Tray(0);
  Move(0, 0);
  sleep(580);
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