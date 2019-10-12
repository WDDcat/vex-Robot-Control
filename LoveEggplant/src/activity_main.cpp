#include "vex.h"
#include "screen.h"
#include "autoPreset.h"

void activity_main(){
  Brain.Screen.clearScreen();
  displayTeamNum();
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono20);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5, "Auto Select");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 2, "Sensor Value");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 3, "Motor Info");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 4, "About");
  
  if(auton <= 4)  {
    Brain.Screen.setPenColor(vex::color(0x0000ff));
    Brain.Screen.printAt(10, 60, (blueAuto[auton - 1] + " is selected").c_str());
  }
  else  {
    Brain.Screen.setPenColor(vex::color(0xff0000));
    Brain.Screen.printAt(10, 60, (redAuto[auton - 5] + " is selected").c_str());
  }
}

void activity_main_onClickListener(){
  int selection = 0;
  while(Brain.Screen.pressing()){
    if(Brain.Screen.xPosition() >= SCREEN_MAX_WIDTH / 2 && Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5){
      if(selection != 1){
        selection = 1;
        activity_main();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5, "Auto Select");
    }
    else if(Brain.Screen.xPosition() >= SCREEN_MAX_WIDTH / 2 && Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 2){
      if(selection != 2){
        selection = 2;
        activity_main();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 2, "Sensor Value");
    }
    else if(Brain.Screen.xPosition() >= SCREEN_MAX_WIDTH / 2 && Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 3){
      if(selection != 3){
        selection = 3;
        activity_main();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 3, "Motor Info");
    }
    else if(Brain.Screen.xPosition() >= SCREEN_MAX_WIDTH / 2 && Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 4){
      if(selection != 4){
        selection = 4;
        activity_main();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 4, "About");
    }
  }
  while(Controller.ButtonA.pressing() && Controller.ButtonB.pressing()){
    selection = 1;
    Brain.Screen.setPenColor(vex::color::orange);
    Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5, "Auto Select");
  }
  activity_main();
  activityControl(selection);
}