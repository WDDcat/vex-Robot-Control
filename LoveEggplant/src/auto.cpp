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
  // if(!turnRightWithGyro(65, 23, 1000)) goto INTERRUPT;
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
  // if(!turnLeftWithGyro(60, -140, 1200)) goto INTERRUPT;
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
  // if(!turnLeftWithGyro(60, -160, 1200)) goto INTERRUPT;
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
  float angleErr = 0.0;
  spread(360, 450);
  LeftMotor1.resetRotation();
  while(LeftMotor1.rotation(deg) < 150){
    Move(200 - LeftMotor1.rotation(deg), 200 - LeftMotor1.rotation(deg));
  }
  if(!goForward(35, 760, 2300)) goto INTERRUPT;
  Stop(hold);
  angleErr += GyroGetAngle();
  turnRightWithGyro(60, 46.0, 650, true);
  Stop(hold);
  sleep(100);
  Brain.resetTimer();
  if(!rushBackward(100, -700, 3000))  goto INTERRUPT;
  Move(-45, -30);
  sleep(760);
  Move(-20, -20);
  sleep(410);
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono40);
  Brain.Screen.printAt(40, 150, "%f", Brain.timer(msec));
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
  timer timer1;
  timer1.clear();
  spread(240, 270);
  goForward(70, 600, 3000);
  // if(!rushForward(70, 400, 1500)) goto INTERRUPT;
  // if(!rushForward(50, 100, 1700)) goto INTERRUPT;
  // if(!rushForward(30, 100, 900))   goto INTERRUPT;
  Stop(hold);
  Intake(2);
  // turnLeftWithGyro(50, -114, 1500, false);
  turnRightWithGyro(50, 114, 1500, false);
  goto INTERRUPT;
  Stop(brake);
  Intake(-50);
  rushForward(40, 130, 2000);
  Stop(hold);
  sleep(680);
  rushBackward(50, -130, 2000);
  Stop(brake);
  sleep(50);
  turnLeftWithGyro(50, -1, 850, true);
  turnRightWithGyro(50, 1, 300, true);
  Stop(hold);
  Intake(50);
  rushForward(60, 600, 4000);
  Stop(coast);
  sleep(50);
  LeftMotor2.resetRotation();
  while(LeftMotor2.rotation(deg) > -600){
    float speed = 0.137 * LeftMotor2.rotation(deg) + 100;
    Move(-speed, -speed);
  }
  Stop(hold);
  if(GyroGetAngle() < 0)  turnRightWithGyro(100, 0, 90, true);
  turnRightWithGyro(100, 112, 1800, true);
  Intake(100);
  rushForward(35, 790, 2500);
  Stop(hold);
  sleep(300);
  Intake(0);
  Move(100, -100);
  sleep(300);
  Tray(46);
  turnRightWithGyro(50, 110, 1500, false);
  // turnRightWithGyro(100, 170, 1200, false);
  Move(70, 70);
  sleep(300);
  Tray(0, hold);
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
  while(timer1.time(msec) < 15000){
    Move(-100, -100);
  }
  Stop(hold);
  sleep(700);
INTERRUPT:
  Intake(0);
  Stop(hold);
  Tray(0, coast);
  return;
}

void auto5(){
  // goForward(70, 600, 3000);
  // Stop(hold);
  //turnLeftWithGyro(50, -114, 1500, false);
  // turnRightWithGyro(100, 121, 2500, false);
  // turnRightWithGyro(60, 46.0, 2000, true);
  turnLeftWithGyro(85, -185.0, 1450, false);
  Stop(hold);
}