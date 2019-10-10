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
  if(!turnLeftWithGyro(60, -160, 1200)) goto INTERRUPT;
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
  // bool turn = true;
  float angleErr = 0.0;
  spread();
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(100, 100);
  }
  if(!goForward(35, 760, 2300)) goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  turnRightWithGyro(60, 47.0, 800);
  Stop(hold);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) > -760){
    Move(-100, -100);
  }
  Move(-55, -20);
  sleep(500);
  Move(-20, -20);
  sleep(200);
  Stop();
  if(!goForward(30, 950, 3500))  goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  sleep(150);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500);
    else                    turnLeftWithGyro(60, 0, 500);
  }
  LeftMotor1.resetRotation();
  TrayMotor.startRotateTo(300, deg);
  if(!goBackward(100, -540, 2000)) goto INTERRUPT;
  Intake(0);
  Tray(0,hold);
  turnLeftWithGyro(90, -174.0 + angleErr * 1.2, 1800);
  Move(60, 60);
  sleep(950 - 0 * 0.8);
  Move(-10, -10);
  sleep(100);
  Stop();
  Tray(100, brake, 500);
  Tray(50, hold, 1100);
  Tray(60);
  sleep(100);
  Move(30, 30);
  sleep(200);
  Tray(0, coast);
  goBackward(80, -400, 2000);
  goto INTERRUPT;
INTERRUPT:
  Intake(0);
  Stop(hold);
  return;
}

void auto4(){
  bool turn = true;
  float angleErr = 0.0;
  spread();
  // if(!goForward(100, 500, 2000))  goto INTERRUPT;///che man kuai er shang de kuai
  // if(!goForward(40, 400, 5000))  goto INTERRUPT;
  if(!goForward(70, 1400, 2200)) goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  if(!turnRightWithGyro(45, 29.0, 900)){
    if(fabs(29.0 - GyroGetAngle()) > 2){
      turn = false;
      if((GyroGetAngle() - 29.0) > 0) turnLeftWithGyro(100, 24.0, 200);
      else                            turnRightWithGyro(100, 34.0, 200);
    }
  }
  Move(-100,-100);
  sleep(1150);
  Move(-60, -30);
  sleep(650);
  Stop();
  if(!goForward(40, 1400, 3400))  goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  sleep(50);
  Intake(0);
  TrayMotor.startRotateTo(250, deg);
  if(GyroGetAbsAngle() > 10){
    if(GyroGetAngle() > 0)  turnRightWithGyro(60, 0, 500);
    else                    turnLeftWithGyro(60, 0, 500);
  }
  if(!goBackward(100, -1100, 2000)) goto INTERRUPT;
  sleep(70);
  Tray(0,hold);
  turnLeftWithGyro(100, -175.0 - angleErr * 0.9, 1950);
  Move(60, 60);
  sleep(950 - angleErr * 2);
  Move(-12, -12);
  sleep(100);
  Stop();
  Tray(70, hold, 850);
  Tray(60);
  Move(30, 30);
  sleep(200);
  Tray(0, coast);
  goBackward(80, -400, 2000);
INTERRUPT:
  Intake(0);
  Stop(hold);
  return;
 }