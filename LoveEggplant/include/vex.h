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

extern int auton;