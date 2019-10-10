#include "vex.h"
#include "screen.h"

int activity = ACTIVITY_MAIN;

void activityMain(int selection);
void autoSelect(int selection);
void sensorValue(int selection);
void motorInfo(int selection);
void robotTest(int selection);

void activityControl(int selection){
  if(selection == -1){
    activity = ACTIVITY_MAIN;
    activity_main();
    return;
  }
  switch(activity){
  case ACTIVITY_MAIN:
    activityMain(selection);
    break;
  case ACTIVITY_AUTOSELECT:
    autoSelect(selection);
    break;
  case ACTIVITY_SENSORVALUE:
    sensorValue(selection);
    break;
  case ACTIVITY_MOTORINFO:
    motorInfo(selection);
    break;
  case ACTIVITY_ROBOTTEST:
    robotTest(selection);
    break;
  default:
    break;
  }
}

void onClickListener(){
  if(Brain.Screen.pressing()){
    switch(activity){
    case ACTIVITY_MAIN:
      activity_main_onClickListener(); 
      break;
    case ACTIVITY_AUTOSELECT:
      activity_autoSelect_onClickListener();
      break;
    case ACTIVITY_SENSORVALUE:
      activity_sensorValue_onClickListener();
      break;
    case ACTIVITY_MOTORINFO:
      activity_motorInfo_onClickListener();
      break;
    case ACTIVITY_ROBOTTEST:
      activity_robotTest_onClickListener();
      break;
    default:
      break;
    }
    return;
  }
  if(activity == ACTIVITY_MOTORINFO){
    activity_refreshMotorInfo();
    return;
  }
  if(activity == ACTIVITY_SENSORVALUE){
    activity_refreshSensorValue();
    return;
  }
}

void activityMain(int selection){
  switch(selection){
  case 1:
    activity = ACTIVITY_AUTOSELECT;
    activity_autoSelect();
    break;
  case 2:
    activity = ACTIVITY_SENSORVALUE;
    activity_sensorValue();
    break;
  case 3:
    activity = ACTIVITY_MOTORINFO;
    activity_motorInfo();
    break;
  case 4:
    activity = ACTIVITY_ROBOTTEST;
    activity_robotTest();
    break;
  default:
    break;
  }
}

void autoSelect(int selection){
  auton = selection;
  activity_autoSelect();
}
void sensorValue(int selection){

}
void motorInfo(int selection){

}
void robotTest(int selection){

}