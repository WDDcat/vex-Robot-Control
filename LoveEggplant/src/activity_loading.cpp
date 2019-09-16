#include "vex.h"
#include "screen.h"
#include <string.h>

using namespace std;
#define sleep(a) vex::task::sleep(a)

char char1 = ' ';
char char2 = ' ';
char char3 = ' ';
char char4 = ' ';
char char5 = ' ';

void displayTeamNum(){
  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono60);
  Brain.Screen.printAt(4, 41, "%c", char1);
  Brain.Screen.printAt(36, 41, "%c", char2);
  Brain.Screen.printAt(68, 41, "%c", char3);
  Brain.Screen.printAt(100, 41, "%c", char4);
  Brain.Screen.printAt(132, 41, "%c", char5);
}

void activity_loading(string teamNum){
  Brain.Screen.setFont(vex::fontType::mono60);
  char1 = teamNum.at(0);
  char2 = teamNum.at(1);
  char3 = teamNum.at(2);
  char4 = teamNum.at(3);
  if(teamNum.length() >= 5)
    char5 = teamNum.at(4);

  for(int i = 0; i <= 40; i++){
    Brain.Screen.printAt(2 * (i-1), SCREEN_MAX_HEIGHT / 2, " ");
    Brain.Screen.printAt(2 * i, SCREEN_MAX_HEIGHT / 2, "%c", char1);
    sleep(3);
  }
  sleep(5);

  for(int i = 0; i <= 68; i++){
    Brain.Screen.printAt(150, 2 * (i-1), " ");
    Brain.Screen.printAt(150, 2*i, "%c", char2);
    sleep(3);
  }
  sleep(5);

  for(int i = 0; i <= 68; i++){
    Brain.Screen.printAt(220, SCREEN_MAX_HEIGHT - 2 * (i-1), " ");
    Brain.Screen.printAt(220, SCREEN_MAX_HEIGHT - 2*i, "%c", char3);
    sleep(3);
  }
  sleep(5);

  for(int i = 0; i <= 95; i++){
    Brain.Screen.printAt(SCREEN_MAX_WIDTH - 2* (i-1), SCREEN_MAX_HEIGHT / 2, " ");
    Brain.Screen.printAt(SCREEN_MAX_WIDTH - 2*i, SCREEN_MAX_HEIGHT / 2, "%c", char4);
    sleep(3);
  }
  sleep(5);

  if(char5 != ' '){
    for(int i = 0; i < 50; i++){
      char c = rand();
      c = c % 26 + 'A';
      Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", c);
      sleep(5);
    }
    Brain.Screen.printAt(360, SCREEN_MAX_HEIGHT / 2, "%c", char5);
  }

  sleep(200);
  for(int i = 0; i < 20; i++){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(80 - 4*i, 136 - 5*i, "%c", char1);
    Brain.Screen.printAt(150 - 4*i - 2*i, 136 - 5*i, "%c", char2);
    Brain.Screen.printAt(220 - 4*i - 4*i, 136 - 5*i, "%c", char3);
    Brain.Screen.printAt(290 - 4*i - 6*i, 136 - 5*i, "%c", char4);
    Brain.Screen.printAt(360 - 4*i - 8*i, 136 - 5*i, "%c", char5);
    sleep(10);
  }
  
  activityControl(-1);
}
