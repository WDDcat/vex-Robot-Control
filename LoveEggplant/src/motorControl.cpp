#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_units.h"
#include "vex.h"
#include "motorControl.h"
#include <ctime>

void gyroInit(){
  Gyro.startCalibration();
  while(Gyro.isCalibrating()){
    sleep(1);
  }
  sleep(3000);
}

// void Move(int lPower, int rPower){
//   LeftMotor1.spin(fwd, lPower, pct);
//   LeftMotor2.spin(fwd, lPower, pct);
//   RightMotor1.spin(fwd, rPower, pct);
//   RightMotor2.spin(fwd, rPower, pct);
// }

void Move(double lPower, double rPower){
  LeftMotor1.spin(fwd, lPower, voltageUnits::volt);
  LeftMotor2.spin(fwd, lPower, voltageUnits::volt);
  RightMotor1.spin(fwd, rPower, voltageUnits::volt);
  RightMotor2.spin(fwd, rPower, voltageUnits::volt);
}

void Stop(brakeType type){
  LeftMotor1.stop(type);
  LeftMotor2.stop(type);
  RightMotor1.stop(type);
  RightMotor2.stop(type);
}

void Lift(int power){
  if(power == 0){
    LiftMotor.stop(hold);
  }
  else{
    LiftMotor.spin(fwd, power, voltageUnits::volt);
  }
}

void Tray(int power, brakeType type){
  if(power == 0){
    TrayMotor.stop(type);
  }
  else{
    TrayMotor.spin(fwd, power, pct);
  }
}

void Intake(int speed){
  LeftIntake.spin(fwd, speed, voltageUnits::volt);
  RightIntake.spin(fwd, speed, voltageUnits::volt);
}

void Intake(float power){
  LeftIntake.spin(fwd, power, voltageUnits::volt);
  RightIntake.spin(fwd, power, voltageUnits::volt);
}

//////////////////////AUTO CONTROL////////////////////////
void spread(){
  while(!LimitBack.pressing()){
    Tray(-100);
  }
  Tray(-5);
  sleep(20);
  Tray(0, hold);
  Intake(100);
}

bool goForward(int power, float target, float timeLimit){
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
  Brain.resetTimer();
	while(Brain.timer(msec) < timeLimit){
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
    if(voltL < 1 || voltR < 1) return true;
		integralL += errL / 2;
    integralR += errR / 2;
		err_lastL = errL;
    err_lastR = errR;
		
    float rpmAdjust = 1.5 * (LeftMotor1.velocity(rpm) - RightMotor2.velocity(rpm)) * (curL / target);
		float rotationAdjust = 0.5 * (LeftMotor2.rotation(deg) - RightMotor2.rotation(deg)) * (curL / target);
    Move(CONSTRAIN(voltL - rpmAdjust - rotationAdjust, 0, power),
         CONSTRAIN(voltR + rpmAdjust + rotationAdjust, 0, power));
	}
  return false;
}

bool goBackward(int power, float target, float timeLimit){
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
  Brain.resetTimer();
	while(Brain.timer(msec) < timeLimit){
    float curL = LeftMotor2.rotation(deg);
    float curR = RightMotor2.rotation(deg);
		errL = target + curL;
    errR = target + curR;
		
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
		
		voltL = 0.5 * KP * errL + indexL * KI * integralL + KD * (errL - err_lastL);
    voltR = 0.5 * KP * errR + indexR * KI * integralR + KD * (errR - err_lastR);
    if(voltL < 1 || voltR < 1) return true;
		integralL += errL / 2;
    integralR += errR / 2;
		err_lastL = errL;
    err_lastR = errR;
		
    float rpmAdjust = 1.5 * (LeftMotor1.velocity(rpm) - RightMotor2.velocity(rpm)) * (-curL / target);
		float rotationAdjust = 0.5 * (LeftMotor2.rotation(deg) - RightMotor2.rotation(deg)) * (-curL / target);
    Move(CONSTRAIN(- voltL + rpmAdjust + rotationAdjust, -power, 0),
         CONSTRAIN(- voltR - rpmAdjust - rotationAdjust, -power, 0));
	}
  return false;
}

void backToWall(float power, int dis1, int dis2, int dis3, int dis4, int time, bool left){
  float k1 = 0.5;
  float k2 = 0.3;
  LeftMotor2.resetRotation();
  while(LeftMotor2.rotation(vex::rotationUnits::deg) > -dis1) {
    Move(-power, -power);
  }
  if(left){
    RightMotor2.resetRotation();
    while(RightMotor2.rotation(deg) > -dis2) {
      Move(-power * k1, -power);
    }
  }
  else{
    LeftMotor2.resetRotation();
    while(LeftMotor2.rotation(deg) > -dis2) {
      Move(-power, -power *k1);
    }
  }

  LeftMotor2.resetRotation();
  while(LeftMotor2.rotation(vex::rotationUnits::deg) > -dis3) {
    Move(-100, -100);
  }

  if(left){
    LeftMotor2.resetRotation();
    while(LeftMotor2.rotation(vex::rotationUnits::deg) > -dis4) {
      Move(-power, -power * k2);
    }
  }
  else{
    RightMotor2.resetRotation();
    while(RightMotor2.rotation(vex::rotationUnits::deg) > -dis4) {
      Move(-power * k2, -power);
    }
  }

  Move(-power, -power);
  sleep(time);
}

bool turnLeft(int power, float target, float timeLimit){
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
		errL = target + curL;
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
		float rotationAdjust = 0;//2.0 * (LeftMotor2.rotation(deg) - RightMotor2.rotation(deg));
    Move(CONSTRAIN(- voltL + rpmAdjust + rotationAdjust, -power, 0),
         CONSTRAIN(voltR + rpmAdjust + rotationAdjust, 0, power));
	}
  return false;
}

bool turnRight(int power, float target, float timeLimit){
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
    errR = target + curR;
		
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
		float rotationAdjust = 0;//2.0 * (LeftMotor2.rotation(deg) - RightMotor2.rotation(deg));
    Move(CONSTRAIN(voltL - rpmAdjust - rotationAdjust, 0, power),
         CONSTRAIN(- voltR - rpmAdjust - rotationAdjust, -power, 0));

    sleep(5);
	}
  return false;
}

bool turnLeftWithGyro(int power, float target, float timeLimit){
  target = target / 90.0 * 800.0;
	float err = 0.0;
	float err_last = 0.0;
  float err_next = 0.0;
	float volt = 0.0;
	//float integral = 0.0;
  Brain.resetTimer();
	while(Brain.timer(msec) < timeLimit){
    double cur = Gyro.value(vex::analogUnits::mV);
		if(cur < target){
      return true;
    }

    err = cur - target;
    volt = KP_TURN * (err - err_next) + KI_TURN * err + KD_TURN * (err - 2*err_next + err_last);
	  err_last = err;
	  err_next = err;
    Move(-volt, volt);

    sleep(2);
	}
  return false;
}

bool turnRightWithGyro(int power, float target, float timeLimit){
	float err = 0.0;
	float err_last = 0.0;
  float err_next = 0.0;
	float volt = 0.0;
  Brain.resetTimer();
	while(Brain.timer(msec) < timeLimit){
    double cur = Gyro.value(vex::analogUnits::mV);
		if(cur > target){
      return true;
    }

    err = target - cur;
    volt = KP_TURN * (err - err_next) + KI_TURN * err + KD_TURN * (err - 2*err_next + err_last);
	  err_last = err;
	  err_next = err;
    Move(volt, -volt);

    sleep(2);
	}
  return false;
}