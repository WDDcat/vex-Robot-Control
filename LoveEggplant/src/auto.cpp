#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

extern int auton;

void runAuto(){
  //spread();
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
  default:
    break;
  }

}

void auto1(){
  if(!goForward(47, 700, 3000))  goto INTERRUPT;
  Lift(-15);
  Stop(brake);
  sleep(200);
  Lift(-5);
  if(!goBackward(75, 350, 1200))  goto INTERRUPT;
  Stop(hold);
  sleep(700);
  if(!turnRightWithGyro(65, 23, 1000)) goto INTERRUPT;
  Stop(hold);
  sleep(230);
  Move(-100, -100);
  sleep(1000);
  Move(-120, -50);
  sleep(500);
  if(!goForward(42, 700, 4200)) goto INTERRUPT;
  Stop(hold);
  sleep(400);
  if(!goBackward(60, 350, 2000))  goto INTERRUPT;
  Stop(brake);
  sleep(600);
  if(!turnLeftWithGyro(60, -140, 1200)) goto INTERRUPT;
  Stop(hold);
  sleep(200);
  // Tray(80);
  goForward(50, 120, 500);
  // Tray(0, hold);
  Move(20, 20);
  sleep(500);
  Move(-50, -50);
  sleep(50);
  Move(0, 0);
  goto INTERRUPT;
  Tray(127);
  sleep(400);
  Intake(-20);
  Tray(80);
  sleep(100);
  Intake(0);
  sleep(250);
  Stop();
  return;
INTERRUPT:
  Stop();
  Intake(0);
  return;
}

void auto2(){
  Lift(-15);
  if(!goForward(5, 700, 3000))  goto INTERRUPT;
  // Stop(brake);
  // sleep(200);
  // Lift(-5);
  sleep(5000);
  backToWall(7, 0, 1800, 0, 0, 0, true);
  goto INTERRUPT;
  Move(-20, -20);
  sleep(0);
  if(!goForward(42, 700, 4200)) goto INTERRUPT;
  Stop(hold);
  sleep(400);
  if(!goBackward(60, 350, 2000))  goto INTERRUPT;
  Stop(brake);
  sleep(600);
  if(!turnLeftWithGyro(60, -140, 1200)) goto INTERRUPT;
  Stop(hold);
  sleep(200);
  // Tray(80);
  goForward(50, 120, 500);
  // Tray(0, hold);
  Move(20, 20);
  sleep(500);
  Move(-50, -50);
  sleep(50);
  Move(0, 0);
  goto INTERRUPT;
  Tray(127);
  sleep(400);
  Intake(-20);
  Tray(80);
  sleep(100);
  Intake(0);
  sleep(250);
  Stop();
  return;
INTERRUPT:
  Stop();
  Intake(0);
  return;
}

void auto3(){
  turnRightWithGyro(50, 90, 0);
  Stop();
  while(true){
    double cur = Gyro.value(vex::analogUnits::mV);
    Brain.Screen.setPenColor(vex::color::cyan);
    Brain.Screen.setFont(vex::fontType::mono20);
    Brain.Screen.printAt(40, 141, "%f", cur);
  }
  Intake(50);
}

void auto4(){
  Intake(100);
  if(!goForward(60, 700, 3000))  goto INTERRUPT;
  Stop(hold);
  sleep(700);
  if(!turnRightWithGyro(60, 33.3, 8000)) goto INTERRUPT;
  Move(-100,-100);
  sleep(1000);
  Stop(coast);
  sleep(200);
  Move(-35, -35);
  sleep(800);
  Stop();
  if(!goForward(30, 700, 3000))  goto INTERRUPT;
  goto INTERRUPT;
INTERRUPT:
  Intake(20);
  Stop();
  return;
}