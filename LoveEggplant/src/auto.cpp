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
  Tray(-1);
  Lift(-1);
  Intake(100);
  goForward(45, 750, 0);
  Stop(hold);
  sleep(200);
  goBackward(70, 230, 0);
  Stop(hold);
  sleep(200);
  turnRightWithGyro(50, 20, 0);
  Stop(hold);
  sleep(200);
  Move(-100, -100);
  sleep(1500);
  Move(-120, -50);
  sleep(1000);
  goForward(35, 750, 0);
  Stop(hold);
  sleep(500);
  goBackward(50, 350, 0);
  Stop(hold);
  sleep(200);
  turnLeft(50, 130, 0);
  // sleep(20);
  // goForward(50, 500, 0);
  Stop();
}

void auto2(){
  // Gyro.startCalibration();
  // while(Gyro.isCalibrating()){
  //   sleep(1);
  // }
  // sleep(3000);
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