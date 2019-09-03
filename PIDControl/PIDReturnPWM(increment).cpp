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
float Ki = 0.04;
float Kd = 0.2;
float voltage = 0.0;
float integral = 0.0;
int count = 0;

float PID_realize(float target, float distance){//ÔöÁ¿ÐÍ (increment)
	err = target - distance;
	float incrementSpeed = Kp * (err - err_next) + Ki * err + Kd * (err - 2*err_next + err_last);
	err_last = err;
	err_next = err;
	return CONSTRAIN(incrementSpeed, 0, 100);
}

int main(){
	float distance = 0.0, target = 2000.0;
	for(int i = 0; i < 500; i++){
		distance += PID_realize(target, distance);
		cout << setw(3) << i << " : "<< distance << endl;
	}
}
