#include <iostream>
#include <iomanip>
#include "cmath"

using namespace std;

#define CONSTRAIN(x,lower, upper) ( (x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

float actualSpeed = 0.0;
float err = 0.0;
float err_last = 0.0;
float err_next = 0.0;
float Kp = 0.4;
float Ki = 0.2;
float Kd = 0.2;
float voltage = 0.0;
float integral = 0.0;
int count = 0;

//float PID_realize(float speed){//位置型 (position)
//	float setSpeed = speed;
//	err = setSpeed - actualSpeed;
//	integral += err;
//	voltage = Kp * err + Ki * integral + Kd * (err - err_last);
//	err_last = err;
//	actualSpeed = voltage * 1;
//	return actualSpeed;
//}

//float PID_realize(float speed){//增量型 (increment)
//	float setSpeed = speed;
//	err = setSpeed - actualSpeed;
//	float incrementSpeed = Kp * (err - err_next) + Ki * err + Kd * (err - 2*err_next + err_last);
//	actualSpeed += incrementSpeed;
//	err_last = err;
//	err_next = err;
//	return actualSpeed;
//}

//float PID_realize(float speed){//积分分离型 (integral separate)
//	float setSpeed = speed;
//	err = setSpeed - actualSpeed;
//	
//	int index = 0;
//	if(abs(err) > 200){
//		index = 0;
//	}
//	else{
//		index = 1;
//		integral += err;
//	}
//	voltage = Kp * err + index * Ki * integral + Kd * (err - err_last);
//	err_last = err;
//	actualSpeed = voltage * 1;
//	return actualSpeed;
//}

//float PID_realize(float speed){//梯形积分型 (trapezoid integral)
//	float setSpeed = speed;
//	err = setSpeed - actualSpeed;
//	
//	int index = 0;
//	if(abs(err) > 200){
//		index = 0;
//	}
//	else{
//		index = 1;
//		integral += err / 2;
//	}
//	voltage = Kp * err + index * Ki * integral + Kd * (err - err_last);
//	integral += err / 2;
//	err_last = err;
//	actualSpeed = voltage * 1.0;
//	return actualSpeed;
//}

float PID_realize(float speed){//变积分型 (changeable integral)
	float setSpeed = speed;
	err = setSpeed - actualSpeed;
	
	float index = 0;
	if(abs(err) > 200){
		index = 0;
	}
	else if(abs(err) < 180){
		index = 1;
		integral += err / 2;
	}
	else{
		index = (200 - abs(err)) / 20;
		integral += err / 2;
	}
	voltage = Kp * err + index * Ki * integral + Kd * (err - err_last);
	integral += err / 2;
	err_last = err;
	actualSpeed = voltage * 1.0;
	return actualSpeed;
}

int main(){
	for(int i = 0; i < 1000; i++){
		cout << setw(3) << i << " : "<< PID_realize(200) << endl;
	}
}
