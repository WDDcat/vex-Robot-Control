/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Shiyu Wang---gdfz                                         */
/*    Created:      Mon Aug 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "screen.h"
#include "motorControl.h"
#include "auto.h"
#include "GyroLib.h"

using namespace vex;

brain Brain;
controller Controller = controller();
//PeiLianChe   //12 13 15 14 8 19 9 5 F E C

/*WSF*//*AEFCH*///int motorPreset[8] = {PORT3, PORT15, PORT7, PORT6, PORT4, PORT10, PORT11, PORT14};
/*DYZ*//*DEBCH*/int motorPreset[8] = {PORT6, PORT11, PORT15, PORT20, PORT1, PORT2, PORT8, PORT19};
motor LeftMotor1  (motorPreset[0],    gearSetting::ratio18_1, false);
motor LeftMotor2  (motorPreset[1],    gearSetting::ratio18_1, false);
motor RightMotor1 (motorPreset[2],    gearSetting::ratio18_1, true);
motor RightMotor2 (motorPreset[3],    gearSetting::ratio18_1, true);
motor LiftMotor   (motorPreset[4],    gearSetting::ratio18_1, false);
motor TrayMotor   (motorPreset[5],    gearSetting::ratio18_1, true);
motor LeftIntake  (motorPreset[6],    gearSetting::ratio18_1, false);
motor RightIntake (motorPreset[7],    gearSetting::ratio18_1, true);
limit LimitBack   (Brain.ThreeWirePort.D);
// limit LimitFront  (Brain.ThreeWirePort.E);
limit LimitDown   (Brain.ThreeWirePort.B);
gyro Gyro         (Brain.ThreeWirePort.C);
//line Line         (Brain.ThreeWirePort.H);

vex::competition Competition;

// define your global instances of motors and other devices here
int auton = -1;
double Ldeg = 0.0;
double Rdeg = 0.0;
bool initComplete = false;

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
  LeftIntake.setBrake(coast);
  RightIntake.setBrake(coast);
  ResetMotor();
  
  gyroInit();
  task setGyro(GyroTask);
  initComplete = true;

  activity_loading("7258A", false);
  while(true){
    double cur = GyroGetAngle();
    double cur1 = LeftMotor2.rotation(deg) - Ldeg;
    double cur2 = RightMotor2.rotation(deg) - Rdeg;
    Brain.Screen.setPenColor(vex::color::cyan);
    Brain.Screen.setFont(vex::fontType::mono30);
    Brain.Screen.printAt(250, 23, "Gyro: %f", cur);
    Brain.Screen.printAt(250, 53, "Left: %f", cur1);
    Brain.Screen.printAt(250, 83, "Right %f", cur2);
    onClickListener();
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
  runAuto();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
  bool LiftDown = true;
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
    
    if(!initComplete) continue;

    //Move control
    if(abs(Ch3) > 10 || abs(Ch4) > 10){
      Move(Ch3 + Ch4, Ch3 - Ch4);
    }
    else if(BtnU || BtnD || BtnL || BtnR){
      Move(20 && BtnU - 20 && BtnD + 30 && BtnR - 30 && BtnL,
           20 && BtnU - 20 && BtnD - 30 && BtnR + 30 && BtnL);
    }
    else Stop(coast);

    //Tray control
    if(Ch2 > 15){
      R1 = false;
      if(fabs(TrayMotor.rotation(deg)) < 360){//360
        Tray(Ch2*0.6);//0.6
      }
      else{
        Tray(Ch2 * 0.3);//0.3
      }
    }
    else if(Ch2 < -15){
      if(LimitBack.pressing()){
        TrayMotor.resetRotation();
        Tray(0, hold);
      }
      else{
        Tray(Ch2);
      }
    }
    else{
      if(LimitBack.pressing())  Tray(0, hold);
      else  Tray(0, brake);
    }

    if(L1){
      if(TrayMotor.rotation(deg) < 380)  Tray(100);
      Lift(100);
      LiftDown = false;
    }
    else if(L2){
      if(LimitDown.pressing()){
        LiftDown = true;
        Lift(0);
        LiftMotor.resetRotation();
      }
      else  Lift(-100);
    }
    else{
      if(LiftDown && !LimitDown.pressing()) Lift(-10); 
      else  Lift(0);
    }


    if(BtnA /*&& Line.value(pct) > 10*/)      Intake(100);
    else if(R1) Intake(100);
    else if(R2) Intake(-100);
    else        Intake(1);

    onClickListener();

    sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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