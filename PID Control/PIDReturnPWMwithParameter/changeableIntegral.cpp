#include <iostream>
#include <iomanip>
#include "cmath"

using namespace std;

#define CONSTRAIN(x,lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))
#define KP 0.4
#define KI 0.04
#define KD 0.2
#define KI_START_PERCENT 0.2
#define KI_INDEX_PAR (1 - KI_START_PERCENT)

float PID_realize(float target, float current){//变积分型 (changeable integral)
	static float err_last = 0.0;
	static float voltage = 0.0;
	static float integral = 0.0;		
	float err = target - current;
	float voltage_last = voltage;
	
	float index = 0;
	if(abs(err) > target){
		index = 0;
	}
	else if(abs(err) < target * KI_START_PERCENT){
		index = 1;
		integral += err / 2;
	}
	else{
		index = (target - abs(err)) / KI_INDEX_PAR;
		integral += err / 2;
	}
	voltage = KP * err + index * KI * integral + KD * (err - err_last);
	integral += err / 2;
	err_last = err;
	
	return CONSTRAIN(voltage - voltage_last, 0, 100);
}

int main(){
	float current = 0.0, target = 2000.0;
	for(int i = 0; i < 500; i++){
		current += PID_realize(target, current);
		cout << setw(3) << i << " : "<< current << endl;
	}
}
