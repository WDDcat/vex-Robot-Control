#include "vex.h"
#include "motorControl.h"

void Move(int lSpeed, int rSpeed){
  LeftMotor1.spin(fwd, lSpeed, pct);
  LeftMotor2.spin(fwd, lSpeed, pct);
  RightMotor1.spin(fwd, rSpeed, pct);
  RightMotor2.spin(fwd, rSpeed, pct);
}

void Lift(int speed){
  if(speed == 0){
    LiftMotor.stop(hold);
  }
  else{
    LiftMotor.spin(fwd, speed, pct);
  }
}

void Tray(int speed){
  if(speed < -15){
    if(LimitBack.pressing()){
      TrayMotor.resetRotation();
      TrayMotor.stop(hold);
    }
    else{
      TrayMotor.spin(fwd, speed, pct);
    }
  }
  else if(speed > 15){
    if(abs((int) TrayMotor.rotation(deg)) < 370){
      TrayMotor.spin(fwd, speed, pct);
    }
    else{
      TrayMotor.spin(fwd, speed * 0.4, pct);
    }
  }
  else{
    if(LimitBack.pressing())  TrayMotor.stop(hold);
    else                      TrayMotor.stop(brake);
  }
}

void Intake(int speed){
  LeftIntake.spin(fwd, speed, pct);
  RightIntake.spin(fwd, speed, pct);
}