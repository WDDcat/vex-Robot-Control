#include "vex.h"
#include "screen.h"
#include "autoPreset.h"
#include <string.h>

using namespace std;

int xStart = 30, yStart = 227, width = 26;

void drawMap();
void drawStart(int x, int y);

void activity_autoSelect(){
  Brain.Screen.clearScreen();
  displayTeamNum();

  Brain.Screen.setPenColor(vex::color::cyan);
  Brain.Screen.setFont(vex::fontType::mono40);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2 - 50, 30, "<<");

  Brain.Screen.setFont(vex::fontType::mono20);
  if(auton <= 4)  {
    Brain.Screen.setPenColor(vex::color(0x0000ff));
    Brain.Screen.printAt(10, 60, (blueAuto[auton - 1] + " is selected").c_str());
  }
  else  {
    Brain.Screen.setPenColor(vex::color(0xff0000));
    Brain.Screen.printAt(10, 60, (blueAuto[auton - 5] + " is selected").c_str());
  }

  Brain.Screen.setPenColor(vex::color::blue);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5, ("1." + blueAuto[0]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 2, ("2." + blueAuto[1]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 3, ("3." + blueAuto[2]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 4, ("4." + blueAuto[3]).c_str());
  Brain.Screen.setPenColor(vex::color::red);
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5, ("5." + redAuto[0]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 2, ("6." + redAuto[1]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 3, ("7." + redAuto[2]).c_str());
  Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 4, ("8." + redAuto[3]).c_str());

  drawMap();
  drawStart(startPosition[auton - 1][0], startPosition[auton - 1][1]);
}

void activity_autoSelect_onClickListener(){
  int selection = 0;
  while(Brain.Screen.pressing()){
    if(Brain.Screen.xPosition() > 190 && Brain.Screen.xPosition() < 240 && Brain.Screen.yPosition() < 30){
      if(selection != -1){
        selection = -1;
        activity_autoSelect();
      }
      Brain.Screen.setPenColor(vex::color::orange);
      Brain.Screen.setFont(vex::fontType::mono40);
      Brain.Screen.printAt(190, 30, "<<");
    }
    else if(Brain.Screen.xPosition() >= 240 && Brain.Screen.xPosition() < 360){
      if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5){
        if(selection != 1){
          selection = 1;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5, ("1." + blueAuto[0]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 2){
        if(selection != 2){
          selection = 2;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 2, ("2." + blueAuto[1]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 3){
        if(selection != 3){
          selection = 3;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 3, ("3." + blueAuto[2]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 4){
        if(selection != 4){
          selection = 4;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 2, SCREEN_MAX_HEIGHT / 5 * 4, ("4." + blueAuto[3]).c_str());
      }
    }
    else if(Brain.Screen.xPosition() > 360){
      if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5){
        if(selection != 5){
          selection = 5;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5, ("5." + redAuto[0]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 2){
        if(selection != 6){
          selection = 6;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 2, ("6." + redAuto[1]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 3){
        if(selection != 7){
          selection = 7;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 3, ("7." + redAuto[2]).c_str());
      }
      else if(Brain.Screen.yPosition() < SCREEN_MAX_HEIGHT / 5 * 4){
        if(selection != 8){
          selection = 8;
          activity_autoSelect();
        }
        Brain.Screen.setPenColor(vex::color::orange);
        Brain.Screen.printAt(SCREEN_MAX_WIDTH / 4 * 3, SCREEN_MAX_HEIGHT / 5 * 4, ("8." + redAuto[3]).c_str());
      }
    }
  }
  activity_autoSelect();
  activityControl(selection);
}

void drawStart(int x, int y){
  Brain.Screen.setPenColor(vex::color(0xffffff));
  Brain.Screen.drawCircle(xStart + (x-1) * width + width / 2, yStart - (y-1) * width - width / 2, width * 0.325, vex::color::white);
}

void drawMap(){
  Brain.Screen.setPenColor(vex::color(0x333333));//field
  Brain.Screen.drawLine(xStart, yStart, xStart + 6 * width, yStart);
  Brain.Screen.drawLine(xStart, yStart - width, xStart + width * 6, yStart - width);
  Brain.Screen.drawLine(xStart, yStart - width * 2, xStart + width * 6, yStart - width * 2);
  Brain.Screen.drawLine(xStart, yStart - width * 3, xStart + width * 6, yStart - width * 3);
  Brain.Screen.drawLine(xStart, yStart - width * 4, xStart + width * 6, yStart - width * 4);
  Brain.Screen.drawLine(xStart, yStart - width * 5, xStart + width * 6, yStart - width * 5);
  Brain.Screen.drawLine(xStart, yStart - width * 6, xStart + width * 6, yStart - width * 6);

  Brain.Screen.drawLine(xStart, yStart, xStart, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width, yStart, xStart + width, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 2, yStart, xStart + width * 2, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 3, yStart, xStart + width * 3, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 4, yStart, xStart + width * 4, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 5, yStart, xStart + width * 5, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 6, yStart, xStart + width * 6, yStart - width * 6);

  Brain.Screen.setPenColor(vex::color(0x0000ff));//blue
  Brain.Screen.drawRectangle(xStart, yStart - width * 2, width, width, vex::color(0x0000ff));
  Brain.Screen.drawRectangle(xStart + width, yStart - width, width, width, vex::color(0x0000ff));
  Brain.Screen.drawLine(xStart, yStart - width / 2, xStart + width * 2 / 3, yStart - width / 2);
  Brain.Screen.drawLine(xStart + width * 2 / 3, yStart - width / 2, xStart + width * 2 / 3, yStart);
  Brain.Screen.drawLine(xStart, yStart - width * 5.5, xStart + width / 2, yStart - width * 5.5);
  Brain.Screen.drawLine(xStart + width / 2, yStart - width * 5.5, xStart + width / 2, yStart - width * 6);
  Brain.Screen.drawCircle(xStart + width * 1.5, yStart - width * 6, width / 3.5);

  Brain.Screen.setPenColor(vex::color(0xff0000));//red
  Brain.Screen.drawRectangle(xStart + width * 4, yStart - width, width, width, vex::color(0xff0000));
  Brain.Screen.drawRectangle(xStart + width * 5, yStart - width * 2, width, width, vex::color(0xff0000));
  Brain.Screen.drawLine(xStart + width * 16 / 3, yStart, xStart + width * 16 / 3, yStart - width / 2);
  Brain.Screen.drawLine(xStart + width * 16 / 3, yStart - width / 2, xStart + width * 6, yStart - width / 2);
  Brain.Screen.drawLine(xStart + width * 5.5, yStart - width * 5.5, xStart + width * 6, yStart - width * 5.5);
  Brain.Screen.drawLine(xStart + width * 5.5, yStart - width * 5.5, xStart + width * 5.5, yStart - width * 6);
  Brain.Screen.drawCircle(xStart + width * 4.5, yStart - width * 6, width / 3.5);

  Brain.Screen.setPenColor(vex::color(0xffffff));//line & tower
  Brain.Screen.drawLine(xStart + width * 2.9, yStart, xStart + width * 2.9, yStart - width * 6);
  Brain.Screen.drawLine(xStart + width * 3.1, yStart, xStart + width * 3.1, yStart - width * 6);
  Brain.Screen.drawLine(xStart, yStart - width, xStart + width, yStart - width);
  Brain.Screen.drawLine(xStart + width, yStart - width, xStart + width, yStart);
  Brain.Screen.drawLine(xStart, yStart - width * 2, xStart + width, yStart - width * 2);
  Brain.Screen.drawLine(xStart + width, yStart - width * 2, xStart + width * 2, yStart - width);
  Brain.Screen.drawLine(xStart + width * 2, yStart - width, xStart + width * 2, yStart);
  Brain.Screen.drawLine(xStart + width * 4, yStart, xStart + width * 4, yStart - width);
  Brain.Screen.drawLine(xStart + width * 4, yStart - width, xStart + width * 5, yStart - width * 2);
  Brain.Screen.drawLine(xStart + width * 5, yStart - width * 2, xStart + width * 6, yStart - width * 2);
  Brain.Screen.drawLine(xStart + width * 5, yStart, xStart + width * 5, yStart - width);
  Brain.Screen.drawLine(xStart + width * 5, yStart - width, xStart + width * 6, yStart - width);

  Brain.Screen.drawCircle(xStart + width * 3, yStart - width * 3, width / 3.5);
  Brain.Screen.drawCircle(xStart + width * 3, yStart - width * 4.5, width / 3.5);
  Brain.Screen.drawCircle(xStart + width * 3, yStart - width * 1.5, width / 3.5);
  Brain.Screen.drawCircle(xStart + width, yStart - width * 3, width / 3.5);
  Brain.Screen.drawCircle(xStart + width * 5, yStart - width * 3, width / 3.5);

}