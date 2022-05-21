/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

//直行PID
#define KP 0.6
#define KI 0.07
#define KD 4.0
//陀螺仪转向PID
#define KP_TURN 0.33
#define KI_TURN 0.000
#define KD_TURN 1.25
//KI作用范围(行驶至多少百分比开始)
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
extern motor UpperRoller;
extern motor LowerRoller;
extern motor LeftIntake;
extern motor RightIntake;
extern limit LimitBack;
extern limit LimitDown;
extern line Line;
extern gyro Gyro;
extern inertial Inertial;

extern int auton;