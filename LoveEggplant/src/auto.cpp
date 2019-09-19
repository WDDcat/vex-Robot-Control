#include "vex.h"
#include "motorControl.h"
#include "auto.h"

void runAuto(){
  switch(auton){
  case 1:
    auto1();
    break;
  default:
    break;
  }
}

void auto1(){
  spread();
  Tray(-5);
  Intake(100);
  goForward(50, 650, 0);
  sleep(20);
  backToWall(70, 70, 320, 570, 100, 1200, 1);
  sleep(50);
  goForward(40, 600, 0);
  sleep(20);
  Turn(50, 220, 0);
  sleep(20);
  goForward(50, 500, 0);
  Stop();
}