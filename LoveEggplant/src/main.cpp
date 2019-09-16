/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vex-gdfz                                         */
/*    Created:      Mon Aug 19 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "screen.h"
#include "motorControl.h"

#define sleep(a) vex::task::sleep(a)

using namespace vex;

brain Brain;
controller Controller = controller();

motor LeftMotor1(PORT4, gearSetting::ratio18_1, false);
motor LeftMotor2(PORT11, gearSetting::ratio18_1, false);
motor RightMotor1(PORT10, gearSetting::ratio18_1, true);
motor RightMotor2(PORT20, gearSetting::ratio18_1, true);
motor LiftMotor(PORT1, gearSetting::ratio18_1, false);
motor TrayMotor(PORT3, gearSetting::ratio18_1, true);
motor LeftIntake(PORT7, gearSetting::ratio18_1, false);
motor RightIntake(PORT8, gearSetting::ratio18_1, true);
limit LimitBack(Brain.ThreeWirePort.G);
limit LimitFront(Brain.ThreeWirePort.A);

vex::competition Competition;

// define your global instances of motors and other devices here
int auton = 1;

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
  activity_loading("7258A");
  while(true){
    LeftIntake.spin(fwd, 100, pct);
    RightIntake.spin(fwd, 100, pct);
    onClickListener();
    sleep(50);
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

void usercontrol( void ) {
  // User control code here, inside the loop
  int Ch1, Ch2, Ch3, Ch4;
  bool L1, L2, R1, R2, BtnA, BtnB, BtnX, BtnY, BtnU, BtnD, BtnL, BtnR;
  go_forward(100, 250, 0);
  Stop();
  /*while (1) {
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

    if(abs(Ch3) > 10 || abs(Ch1) > 10){
      Move(Ch3 + Ch1, Ch3 - Ch1);
    }
    else Move(0, 0);

    Tray(Ch2);

    if(L1)      Lift(100);
    else if(L2) Lift(-100);
    else        Lift(0);

    if(R1)      Intake(100);
    else if(R2) Intake(-100);
    else        Intake(0);

    sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }*/
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}