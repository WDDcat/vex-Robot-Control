#include "vex.h"
#include "screen.h"

void activity_motorInfo(){
  Brain.Screen.clearScreen();
  displayTeamNum();
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono40);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2 - 50, 30, "<<");
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono20);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, 30, "Motor Info");

  Brain.Screen.setFont(vex::fontType::mono15);
  for(int i = 1; i < 5; i++){
    for(int j = 0; j < 5; j++){
      Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * j, 10 + 46 * i, "PORT %d:", (i * 5) + j - 4);
    }
  }
  // Brain.Screen.printAt(0, 56, "PORT 1:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 1, 56, "PORT 2:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 2, 56, "PORT 3:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 3, 56, "PORT 4:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 4, 56, "PORT 5:");

  // Brain.Screen.printAt(0, 102, "PORT 6:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 1, 102, "PORT 7:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 2, 102, "PORT 8:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 3, 102, "PORT 9:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 4, 102, "PORT 10:");

  // Brain.Screen.printAt(0, 148, "PORT 11:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 1, 148, "PORT 12:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 2, 148, "PORT 13:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 3, 148, "PORT 14:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 4, 148, "PORT 15:");

  // Brain.Screen.printAt(0, 194, "PORT 16:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 1, 194, "PORT 17:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 2, 194, "PORT 18:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 3, 194, "PORT 19:");
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * 4, 194, "PORT 20:");
}

void activity_refreshMotorInfo(){
  double temp = LeftMotor1.temperature(temperatureUnits::celsius);
  temp = 0;
  Brain.Screen.setFont(vex::fontType::mono15);
  // Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 2, "R: %.2lf", motor(PORT0).rotation(deg));
  // for(int i = 1; i < 5; i++){
  //   for(int j = 0; j < 5; j++){
  //     if(motor((i * 5) + j - 5).installed())
  //       Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * j, 23 + 46 * i, "R: %.2lf", motor((i * 5) + j - 5).rotation(deg));
  //     else
  //       Brain.Screen.printAt(SCREEN_MAX_WIDTH / 5 * j, 23 + 46 * i, "R:      ");
  //   }
  // }

}

void activity_motorInfo_onClickListener(){
  int selection = 0;
  while(Brain.Screen.pressing()){
    if(Brain.Screen.xPosition() > 190 && Brain.Screen.xPosition() < 240 && Brain.Screen.yPosition() < 30){
      if(selection != -1){
        selection = -1;
        activity_motorInfo();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.setFont(vex::fontType::mono40);
      Brain.Screen.printAt(190, 30, "<<");
    }
  }
  activity_motorInfo();
  activityControl(selection);
}