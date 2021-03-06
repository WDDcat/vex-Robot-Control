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
triport::port a = Brain.ThreeWirePort.A;

/*PLC*///int motorPreset[8] = {PORT12, PORT13, PORT15, PORT14, PORT8, PORT19, PORT9, PORT5};  triport::port triPreset[4] = {Brain.ThreeWirePort.F, Brain.ThreeWirePort.A, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C}; bool liftB = false;
/*WSF*///int motorPreset[8] = {PORT3, PORT15, PORT19, PORT1, PORT11, PORT10, PORT14, PORT18}; triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C, Brain.ThreeWirePort.H}; bool liftB = false;
/*DYZ*///int motorPreset[8] = {PORT13, PORT14, PORT20, PORT19, PORT15, PORT16, PORT5, PORT6};    triport::port triPreset[4] = {Brain.ThreeWirePort.A, Brain.ThreeWirePort.C, Brain.ThreeWirePort.B, Brain.ThreeWirePort.H}; bool liftB = true;
/*YSY*///int motorPreset[8] = {PORT15, PORT12, PORT18, PORT16, PORT1, PORT19, PORT8, PORT17};  triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.C, Brain.ThreeWirePort.B, Brain.ThreeWirePort.H}; bool liftB = false;
/*SHN*///int motorPreset[8] = {PORT12, PORT11, PORT10, PORT21, PORT6, PORT5, PORT1, PORT3};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C}; bool liftB = false;
/*2020 99999v*///int motorPreset[8] = {PORT13, PORT12, PORT18, PORT20, PORT5, PORT16, PORT11, PORT1};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C}; bool liftB = false; 
/*2020 王老师idea*/int motorPreset[8] = {PORT13, PORT12, PORT18, PORT20, PORT5, PORT16, PORT11, PORT1};   triport::port triPreset[4] = {Brain.ThreeWirePort.D, Brain.ThreeWirePort.H, Brain.ThreeWirePort.B, Brain.ThreeWirePort.C}; bool liftB = false; 


motor LeftMotor1  (motorPreset[0],    gearSetting::ratio18_1, false);
motor LeftMotor2  (motorPreset[1],    gearSetting::ratio18_1, false);
motor RightMotor1 (motorPreset[2],    gearSetting::ratio18_1, true);
motor RightMotor2 (motorPreset[3],    gearSetting::ratio18_1, true);
motor LiftMotor   (motorPreset[4],    gearSetting::ratio18_1, liftB);
motor TrayMotor   (motorPreset[5],    gearSetting::ratio18_1, true);
motor LeftIntake  (motorPreset[6],    gearSetting::ratio18_1, false);
motor RightIntake (motorPreset[7],    gearSetting::ratio18_1, true);
limit LimitBack   (triPreset[0]);
limit LimitDown   (triPreset[1]);
gyro Gyro         (triPreset[3]);
line Line         (triPreset[2]);
inertial Inertial (PORT15);

vex::competition Competition;

// define your global instances of motors and other devices here
int auton = 3;
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
  
  // gyroInit();
  task setGyro(GyroTask);
  Inertial.calibrate();
  while(Inertial.isCalibrating()){  sleep(10);}
  Inertial.resetHeading();
  Inertial.resetRotation();

  // activity_loading("7258B", false);
  
  initComplete = true;
  timer lineTimer;
  lineTimer.reset();
  while(true){
    double cur = Inertial.pitch();//x轴方向角 （原点看向轴方向）顺时针为负
    double cur1 = Inertial.yaw();//z轴方向角  
    double cur2 = Inertial.roll();//y轴方向角
    cur = Inertial.angle();
    cur1 = GyroGetAngle();
    cur2 = Inertial.rotation();
    Brain.Screen.setPenColor(vex::color::cyan);
    Brain.Screen.setFont(vex::fontType::mono30);
    Brain.Screen.printAt(400, 23, "%f", cur);
    Brain.Screen.printAt(400, 47, "%f", cur1);
    Brain.Screen.printAt(400, 71, "%f", cur2);
    // double lineValue = Line.value(pct);
    // if(lineValue < linemin) linemin = lineValue;
    // if(lineValue > linemax) linemax = lineValue;
    // Brain.Screen.drawCircle(lineTimer.time(msec) / 10, (SCREEN_MAX_HEIGHT - lineValue), 2);
    // Brain.Screen.printAt(400, 23, "%f", linemin);
    // Brain.Screen.printAt(400, 47, "%f", linemax);
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
  while (!GyroGetValid()) sleep(10);
  // runAuto();
  Blue();
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

    // //Tray control
    // if(Ch2 > 15){
    //   R1 = false;
    //   if(fabs(TrayMotor.rotation(deg)) < 520){//360
    //     Tray(Ch2 * 0.9);//0.6
    //   }
    //   else{
    //     Tray(Ch2 * 0.33);//0.3
    //   }
    // }
    // else if(Ch2 < -15){
    //   if(LimitBack.pressing()){
    //     TrayMotor.resetRotation();
    //     Tray(0, hold);
    //   }
    //   else{
    //     Tray(Ch2);
    //   }
    // }
    // else{
    //   if(LimitBack.pressing())  Tray(0, hold);
    //   else  Tray(0, brake);
    // }

    // // Lift control
    // if(L1){
    //   if(TrayMotor.rotation(deg) < 385)  Tray(100);
    //   LiftMotor.setMaxTorque(2, Nm);
    //   Lift(100);
    //   LiftDown = false;
    // }
    // else if(L2){
    //   if(LimitDown.pressing()){
    //     LiftDown = true;
    //     Lift(0);
    //     LiftMotor.resetRotation();
    //   }
    //   else  Lift(-100);
    // }
    // else{
    //   if(LiftDown && !LimitDown.pressing() && TrayMotor.rotation(deg) < 200)   Lift(-5);
    //   else Lift(0);
    // }

    //Intake control
    if(L1) {
      TrayMotor.spin(fwd, -100, pct);
    }
    else if(L2) {
      TrayMotor.spin(fwd, 100, pct);
    }
    else {
      TrayMotor.spin(fwd, 0, pct);
    }


    if(R1) {
      Intake(100);
      LiftMotor.spin(fwd, -100, pct);
    }
    else if(R2) {
      Intake(-100);
      LiftMotor.spin(fwd, 100, pct);
    }
    else {
      Intake(0, coast);
      LiftMotor.stop(coast);
    }

    // onClickListener();

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