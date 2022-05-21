/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Shiyu Wang---gdfz                                         */
/*    Created:      Mon Aug 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

using namespace vex;

brain Brain;
controller Controller;

//定义端口统一位置
/*2020 99999v*/   //int motorPreset[8] = {PORT13, PORT14, PORT20, PORT19, PORT16, PORT15, PORT5, PORT6};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C}; 
                  //bool motorDirection[8] = {true, true, false, false, false, false, false, true};
/*2020 10955*/    int motorPreset[8] = {PORT13, PORT12, PORT18, PORT20, PORT16, PORT2, PORT11, PORT1};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.A, Brain.ThreeWirePort.C};
                  bool motorDirection[8] = {false, false, true, true, true, true, false, true};
/*2020 王老师idea*///int motorPreset[8] = {PORT13, PORT12, PORT18, PORT20, PORT16, PORT2, PORT11, PORT1};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.A, Brain.ThreeWirePort.C};
                  //bool motorDirection[8] = {false, false, true, true, false, true, true, false};

motor LeftMotor1  (motorPreset[0],  gearSetting::ratio18_1, motorDirection[0]);
motor LeftMotor2  (motorPreset[1],  gearSetting::ratio18_1, motorDirection[1]);
motor RightMotor1 (motorPreset[2],  gearSetting::ratio18_1, motorDirection[2]);
motor RightMotor2 (motorPreset[3],  gearSetting::ratio18_1, motorDirection[3]);
motor UpperRoller (motorPreset[4],  gearSetting::ratio18_1, motorDirection[4]);
motor LowerRoller (motorPreset[5],  gearSetting::ratio18_1, motorDirection[5]);
motor LeftIntake  (motorPreset[6],  gearSetting::ratio18_1, motorDirection[6]);
motor RightIntake (motorPreset[7],  gearSetting::ratio18_1, motorDirection[7]);
limit LimitBack   (triPreset[0]);
limit LimitDown   (triPreset[1]);
line Line         (triPreset[2]);
gyro Gyro         (triPreset[3]);
inertial Inertial (PORT15);

competition Competition;

// define your global instances of motors and other devices here
int auton = -1;
bool initComplete = false;
timer driverTimer;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  //初始化电机
  LeftIntake.setBrake(coast);
  RightIntake.setBrake(coast);
  ResetMotor();
  
  //初始化陀螺仪，下面一行在需要使用陀螺仪时取消备注，需等待3秒左右，等待期间禁止触碰机器人
  // gyroInit();
  task setGyro(GyroTask);
  Inertial.calibrate();
  while(Inertial.isCalibrating()){sleep(10);}
  Inertial.resetHeading();
  Inertial.resetRotation();
  
  initComplete = true;
  timer lineTimer;
  lineTimer.reset();

  //主控显示参数区域
  double cur1 = 0.0, cur2 = 0.0, cur3 = 0.0;
  while(true){
    //将传感器等参数赋值进行显示
    cur1 = LeftMotor1.rotation(deg);
    cur2 = driverTimer.time(msec);
    Brain.Screen.setPenColor(vex::color::cyan);
    Brain.Screen.setFont(vex::fontType::mono30);
    Brain.Screen.printAt(400, 23, "%f", cur1);
    Brain.Screen.printAt(400, 47, "%f", cur2);
    Brain.Screen.printAt(400, 71, "%f", cur3);
  }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  //陀螺仪初始化完成前不运行自动
  while (!GyroGetValid()) sleep(10);
  //见auto.cpp
  runAuto();
  auto1();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void drivercontrol( void ) {
  // User control code here, inside the loop
  int Ch1, Ch2, Ch3, Ch4;
  bool L1, L2, R1, R2, BtnA, BtnB, BtnX, BtnY, BtnU, BtnD, BtnL, BtnR;
  bool lastL1;
  while (1) {
    Ch1 = Controller.Axis1.value();
    Ch2 = Controller.Axis2.value();
    Ch3 = Controller.Axis3.value();
    Ch4 = Controller.Axis4.value();
    L1 = Controller.ButtonL1.pressing();
    L2 = Controller.ButtonL2.pressing();
    R1 = Controller.ButtonR1.pressing();
    R2 = Controller.ButtonR2.pressing();
    BtnA = Controller.ButtonA.pressing();
    BtnB = Controller.ButtonB.pressing();
    BtnX = Controller.ButtonX.pressing();
    BtnY = Controller.ButtonY.pressing();
    BtnU = Controller.ButtonUp.pressing();
    BtnD = Controller.ButtonDown.pressing();
    BtnL = Controller.ButtonLeft.pressing();
    BtnR = Controller.ButtonRight.pressing();
    
    //未初始化完成前机器人不受手柄操控
    if(!initComplete) continue;

    //Move control
    //单杆
    if(abs(Ch3) > 10 || abs(Ch4) > 10){
      Move(Ch3 + Ch4, Ch3 - Ch4);
    }
    else Stop(coast);

    //Seperate intake control
    //上下滚子不联动
    // if(L1) { 
    //   UpRoll(100);
    // } 
    // else if(L2) { 
    //   UpRoll(-100); 
    // } 
    // else {
    //   UpRoll(0, coast); 
    // }

    // if(R1 && R2) {
    //   Roll(100);
    //   Intake(0);
    // }
    // else if(R1) {
    //   Intake(100);
    //   LowRoll(100);
    // }
    // else if(R2) { Intake(-100); LowRoll(-100); }
    // else { Intake(0, coast); LowRoll(0, coast); }

    //Unite intake control
    //上下滚子联动
    if(L1) {
      if(!lastL1) {
        driverTimer.reset();
      }
      Roll(100);//(120 - (driverTimer.time(msec) * 0.03)); //球道滚轮减速
    } 
    else if(L2) { 
      Roll(-100); 
      UpperRoller.resetRotation(); 
    } 
    else { 
      Roll(0, coast); 
    }

    if(R1) { 
      Intake(100);
      if(Line.value(pct) < 50 && !L1 && !L2) {
        driverTimer.reset();
        UpperRoller.resetRotation();
        Roll(40); 
      }
      else if(UpperRoller.rotation(deg) > 50){//if(driverTimer.time(msec) > 300) {
        if(!L1 && !L2) {
          Roll(0, hold); 
        }
      }
      else {
        if(!L1 && !L2) {
          Roll(60);
        }
      }
    }
    else if(R2) { Intake(-100); }
    else { Intake(0, coast); }

    sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    lastL1 = L1;
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( drivercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      sleep(50);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}