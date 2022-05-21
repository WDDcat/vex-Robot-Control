#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

extern int auton;

//根据auton的值选择运行的自动编号
//auton值的定义在main.cpp中第46行
void runAuto(){
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

//详细写各个自动程序
void auto1(){

}
void auto2(){}
void auto3(){}
void auto4(){}
void auto5(){}
void auto6(){}
void auto7(){}
void auto8(){}
void autoTest(){
  Move(50, 50);
  wait(500, msec);
  Stop(hold);

  while(Line.value(mV) < 10) {
    Roll(100);
  }
  Roll(0, hold);
  rushForward(100, 1000, 5000, true);
  goForward(100, 1000, 5000);
  goForward(20, 100, 1000, 0.8, 0.01, 5.0);
  turnLeftWithGyro(100, 100, 1000, true, 10);
}