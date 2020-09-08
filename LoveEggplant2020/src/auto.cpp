#include "vex.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

extern int auton;

void runAuto(){
  
  switch(auton){
  case -1:
    autoTest(); break;
  case 1:
    auto1();  break;
  case 2:
    auto2();  break;
  case 3:
    auto3();   break;
  case 4:
    auto4();  break;
  case 5:
    auto5();  break;
  case 6:
    auto6();  break;
  case 7:
    auto7(); break;
  case 8:
    auto8();  break;
  default:
    break;
  }

}
void auto1(){}
void auto2(){}
void auto3(){}
void auto4(){}
void auto5(){}
void auto6(){}
void auto7(){}
void auto8(){}
void autoTest(){}