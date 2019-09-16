#include "vex.h"
#include "screen.h"

void activity_sensorValue(){
  Brain.Screen.clearScreen();
  displayTeamNum();

  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono40);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2 - 50, 30, "<<");

  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono20);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, 30, "Sensor Value");

  Brain.Screen.setFont(vex::fontType::mono15);
  Brain.Screen.printAt(0, 56, "PORT A:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4, 56, "PORT B:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 2, 56, "PORT C:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, 56, "PORT D:");

  Brain.Screen.printAt(0, 150, "PORT E:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4, 150, "PORT F:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 2, 150, "PORT G:");
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, 150, "PORT H:");
}

void activity_refreshSensorValue(){
  double temp = LeftMotor1.temperature(temperatureUnits::celsius);
  temp = 0;
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 6 * 2 + 20, "%.2lf", LeftMotor1.rotation(deg));

}

void activity_sensorValue_onClickListener(){
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