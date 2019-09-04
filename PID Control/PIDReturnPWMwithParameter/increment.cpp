#include <iostream>
#include <iomanip>
#include "cmath"

using namespace std;

#define CONSTRAIN(x,lower, upper) ( (x)<(lower)?(lower):((x)>(upper)?(upper):(x)))
#define KP 0.4
#define KI 0.04
#define KD 0.2 

float PID_realize(float target, float distance){//ÔöÁ¿ÐÍ (increment)
	float err = target - distance;
	static float err_last = 0.0;
	static float err_next = 0.0;
	float incrementSpeed = KP * (err - err_next) + KI * err + KD * (err - 2*err_next + err_last);
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
