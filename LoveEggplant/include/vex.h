/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

#define SCREEN_MAX_WIDTH 480
#define SCREEN_MAX_HEIGHT 272

#define ACTIVITY_MAIN         0xFF
#define ACTIVITY_AUTOSELECT   0xFE
#define ACTIVITY_SENSORVALUE  0xFD
#define ACTIVITY_MOTORINFO    0xFC
#define ACTIVITY_ROBOTTEST    0xFB

#define KP 0.6
#define KI 0.07         //0.7
#define KD 4.0          //15.0
#define KP_TURN 0.33    //0.51  //0.42
#define KI_TURN 0.000   //0.002 //0.003
#define KD_TURN 1.25    //42.0  //35.0
#define KI_START_PERCENT 0.95
#define KI_TURN_START_PERCENT 0.92
#define KI_INDEX_PAR (1 - KI_START_PERCENT)

#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))
#define sleep(a) vex::task::sleep(a)

using namespace vex;

extern brain Brain;
extern controller Controller;
extern motor LeftMotor1;
extern motor LeftMotor2;
extern motor RightMotor1;
extern motor RightMotor2;
extern motor LiftMotor;
extern motor TrayMotor;
extern motor LeftIntake;
extern motor RightIntake;
extern limit LimitBack;
extern limit LimitFront;
extern limit LimitDown;
extern gyro Gyro;
extern line Line;

extern int auton;

extern double Ldeg;
extern double Rdeg;
