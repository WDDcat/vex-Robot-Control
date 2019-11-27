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
vex::brain Brain;
//ma da she zhi
vex::motor Left1 = vex::motor(vex::PORT11, vex::gearSetting::ratio36_1,false);
vex::motor Right1 = vex::motor(vex::PORT1, vex::gearSetting::ratio36_1, false);
vex::motor Left2 = vex::motor(vex::PORT12, vex::gearSetting::ratio36_1,false);
vex::motor Right2 = vex::motor(vex::PORT2, vex::gearSetting::ratio36_1, false);
vex::motor Lift1 = vex::motor(vex::PORT18, vex::gearSetting::ratio18_1,false);
vex::motor Open2 = vex::motor(vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::motor Xi1 = vex::motor(vex::PORT4, vex::gearSetting::ratio36_1,false);
vex::motor Xi2 = vex::motor(vex::PORT14, vex::gearSetting::ratio36_1,true);

//chuan gan qi she zhi
vex::gyro mGyro = vex::gyro(Brain.ThreeWirePort.D);
//vex::analog_in mGyro = vex::analog_in(Brain.ThreeWirePort.D);
vex::encoder Tanbianma = vex::encoder(Brain.ThreeWirePort.E);
vex::bumper jumper1 = vex::bumper(Brain.ThreeWirePort.A);
vex::bumper jumper2 = vex::bumper(Brain.ThreeWirePort.B);

vex::bumper starttouch = vex::bumper(Brain.ThreeWirePort.H);
vex::analog_in jiaodu = vex::analog_in(Brain.ThreeWirePort.C);
//yao kong qi she zhi
vex::controller Controller1 = vex::controller(vex::controllerType::primary);
//vex::controller Controller2 = vex::controller(vex::controllerType::primary);



/////
namespace vex {
  class motor_special : public motor {
    private:
      uint32_t  _local_index;

    public:
      motor_special( int32_t index ) :  motor( index ), _local_index(index) {};  
      ~motor_special() {};

      // Allow overloading of base class methods
      using motor::spin;
      
      // This is similar, not quite the same, as new a method in the next (Nov ?) SDK release
      // voltage can be +/-12.0 volta or +/-12000 mV
      void spin_s( directionType dir, double voltage, voltageUnits units ) {
        // convert volts to mV is necessary
        int32_t voltage_mv = (units == voltageUnits::volt ? voltage * 1000.0 : voltage );

        // flip based on direction flag
        voltage_mv = (dir == directionType::fwd ? voltage_mv : -(voltage_mv) );

        if( voltage_mv == 0 ) {
          stop();
        } else {
          // send mV value to control motor open loop
          vexMotorVoltageSet( _local_index, voltage_mv );
        }
      }
  };
}

using namespace vex;

motor_special Opens2 ( vex::PORT20 );

motor_special Xis1 ( vex::PORT4 );
motor_special Xis2 ( vex::PORT14 );


motor_special LeftRun1 ( vex::PORT11 );
motor_special LeftRun2 ( vex::PORT12 );

motor_special RightRun1( vex::PORT1 );
motor_special RightRun2( vex::PORT2 );