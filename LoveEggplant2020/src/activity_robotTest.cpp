#include "vex.h"
#include "screen.h"

#define sleep(a) vex::task::sleep(a)

void activity_robotTest(){
  Brain.Screen.clearScreen();
  
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono60);

  for(int i = 0; i < 120; i++){
    Brain.Screen.printAt(80, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(150, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(220, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(290, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
  }
  Brain.Screen.printAt(80, 136, "7");

  for(int i = 0; i < 150; i++){
    Brain.Screen.printAt(150, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(220, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(290, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
  }
  Brain.Screen.printAt(150, 136, "2");

  for(int i = 0; i < 200; i++){
    Brain.Screen.printAt(220, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(290, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
  }
  Brain.Screen.printAt(220, 136, "5");

  for(int i = 0; i < 300; i++){
    Brain.Screen.printAt(290, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
  }
  Brain.Screen.printAt(290, 136, "8");

  for(int i = 0; i < 600; i++){
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", rand() % 26 + 'A');
    sleep(1);
  }
  Brain.Screen.printAt(360, 136, "A");
  
  
  Brain.Screen.setFont(vex::fontType::mono30);
  Brain.Screen.printAt(25, 170, "High School Attached to BJUT");

  Brain.Screen.setFont(vex::fontType::mono12);
  Brain.Screen.printAt(0, 240, "Version 2.0");

  Brain.Screen.setFont(vex::fontType::mono12);
  Brain.Screen.printAt(375, 240, "Powered by W.S.Y");
}

void activity_robotTest_onClickListener(){
  int selection = -1;
  while(Brain.Screen.pressing()){
    if(Brain.Screen.xPosition() > 375 && Brain.Screen.yPosition() > 240)
      selection = 1;
  }
  activityControl(selection);
}