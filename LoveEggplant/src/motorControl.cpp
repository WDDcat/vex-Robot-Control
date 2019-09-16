#include "vex.h"
#include "motorControl.h"

void Move(int lSpeed, int rSpeed){
  LeftMotor1.spin(fwd, lSpeed, pct);
  LeftMotor2.spin(fwd, lSpeed, pct);
  RightMotor1.spin(fwd, rSpeed, pct);
  RightMotor2.spin(fwd, rSpeed, pct);
}

void Stop(){
  LeftMotor1.stop(hold);
  LeftMotor2.stop(hold);
  RightMotor1.stop(hold);
  RightMotor2.stop(hold);
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

//////////////////////AUTO CONTROL////////////////////////
bool go_forward(int speed, float target, float timeLimit){
	float errL = 0.0;
  float errR = 0.0;
	float err_lastL = 0.0;
  float err_lastR = 0.0;
	float voltL = 0.0;
  float voltR = 0.0;
	float integralL = 0.0;
  float integralR = 0.0;
	float indexL = 0.0;
  float indexR = 0.0;
  LeftMotor2.resetRotation();
  RightMotor2.resetRotation();
	while(1){
    float curL = LeftMotor2.rotation(deg);
    float curR = RightMotor2.rotation(deg);
		errL = target - curL;
    errR = target - curR;
		
		if(abs((int) errL) > target){
			indexL = 0;
		}
		else if(abs((int) errL) < target * KI_START_PERCENT){
			indexL = 1;
			integralL += errL / 2;
		}
		else{
			indexL = (target - abs((int) errL)) / KI_INDEX_PAR;
			integralL += errL / 2;
		}

    if(abs((int) errR) > target){
			indexR = 0;
		}
		else if(abs((int) errR) < target * KI_START_PERCENT){
			indexR = 1;
			integralR += errR / 2;
		}
		else{
			indexR = (target - abs((int) errR)) / KI_INDEX_PAR;
			integralR += errR / 2;
		}
		
		voltL = KP * errL + indexL * KI * integralL + KD * (errL - err_lastL);
    voltR = KP * errR + indexR * KI * integralR + KD * (errR - err_lastR);
    if(voltL < 0.01 || voltR < 0.01) return true;
		integralL += errL / 2;
    integralR += errR / 2;
		err_lastL = errL;
    err_lastR = errR;
		
    float rpmAdjust = 1.0 * (LeftMotor1.velocity(rpm) - RightMotor2.velocity(rpm));
		float rotationAdjust = 2.0 * (LeftMotor2.rotation(deg) - RightMotor2.rotation(deg));
    Move(CONSTRAIN(voltL - rpmAdjust - rotationAdjust, 0, speed),
         CONSTRAIN(voltR + rpmAdjust + rotationAdjust, 0, speed));
	}
  return false;
}