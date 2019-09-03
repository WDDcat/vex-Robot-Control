#include <iostream>
#include <iomanip>
#include "cmath"

using namespace std;

#define CONSTRAIN(x,lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

float actualSpeed = 0.0;
float err = 0.0;
float err_last = 0.0;
float err_next = 0.0;
float Kp = 0.4;
float Ki = 0.04;
float Kd = 0.2;
float voltage = 0.0;
float voltage_last = 0.0;
float integral = 0.0;
int count = 0;

float PID_realize(float target, float distance){//变积分型 (changeable integral)
	err = target - distance;
	voltage_last = voltage;
	
	float index = 0;
	if(abs(err) > target){
		index = 0;
	}
	else if(abs(err) < target * 0.2){
		index = 1;
		integral += err / 2;
	}
	else{
		index = (target - abs(err)) / 0.1 * target;
		integral += err / 2;
	}
	voltage = Kp * err + index * Ki * integral + Kd * (err - err_last);
	integral += err / 2;
	err_last = err;
	
	return CONSTRAIN(voltage - voltage_last, 0, 100);
}

int main(){
	float distance = 0.0, target = 2000.0;
	for(int i = 0; i < 500; i++){
		distance += PID_realize(target, distance);
		cout << setw(3) << i << " : "<< distance << endl;
	}
}
