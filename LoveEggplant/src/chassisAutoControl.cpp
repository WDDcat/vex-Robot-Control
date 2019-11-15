#include "vex.h"
#include "motorControl.h"
#include "GyroLib.h"
#include "chassisAutoControl.h"

void mmove(double leftvelocity, double rightvelocity) {
    LeftMotor1.spin(vex::directionType::fwd,leftvelocity,vex::voltageUnits::mV);
    LeftMotor2.spin(vex::directionType::fwd,leftvelocity,vex::voltageUnits::mV);
    RightMotor1.spin(vex::directionType::fwd,rightvelocity,vex::voltageUnits::mV);
    RightMotor2.spin(vex::directionType::fwd,rightvelocity,vex::voltageUnits::mV);
    if(leftvelocity==0){
        LeftMotor1.stop(vex::brakeType::hold);
        LeftMotor2.stop(vex::brakeType::hold);
    }
    if(rightvelocity==0){
        RightMotor1.stop(vex::brakeType::hold);
        RightMotor2.stop(vex::brakeType::hold);       
    }  
}

void autostart(double left, double right, double maxV) {//left and right must smaller than 200
    double minV=1000,left_error,right_error,olv,orv,startV=2500,K=30;
    double leftvelocity,rightvelocity,maxv=100;
    double k,k1=0.02,instant_error;
    static double left_rotation,right_rotation;
    double l=0,r=0;
    //read the initial value,set the target
    //reset the timer
    double left_target,right_target;
    left_target=LeftMotor1.rotation(vex::rotationUnits::deg)+left;
    right_target=RightMotor1.rotation(vex::rotationUnits::deg)+right;
    double t=Brain.timer(vex::timeUnits::msec);
    //speed up
    while(1){
        if(Brain.timer(vex::timeUnits::msec)-t>2000)break;
        left_error=left_target-LeftMotor1.rotation(vex::rotationUnits::deg);
        right_error=right_target-RightMotor1.rotation(vex::rotationUnits::deg);
        leftvelocity=(fabs(left-left_error)*K+startV)*left/fabs(left);
        rightvelocity=(fabs(right-right_error)*K+startV)*right/fabs(right);
        
        // if(leftvelocity>maxV)leftvelocity=maxV;
        // if(leftvelocity<-maxV)leftvelocity=-maxV;
        // if(rightvelocity>maxV)rightvelocity=maxV;
        // if(rightvelocity<-maxV)rightvelocity=-maxV;
        leftvelocity = CONSTRAIN(leftvelocity, -maxV, maxV);
        rightvelocity = CONSTRAIN(rightvelocity, -maxV, maxV);
        
        mmove(leftvelocity,rightvelocity);
        if(left>=0&&left_error<=0)l=1;
        if(left<=0&&left_error>=0)l=1;
        if(right>=0&&right_error<=0)r=1;
        if(right<=0&&right_error>=0)r=1;
        if(l&&r)break;
    }
}

void autorun(double left_target,double right_target, double maxV, double time){
    double left_error,right_error,leftvelocity,rightvelocity,instant_error,k,k1=0.07;
    double t=Brain.timer(vex::timeUnits::msec);
    while(1){
         if(Brain.timer(vex::timeUnits::msec)-t>time)break;
        left_error=left_target-LeftMotor1.rotation(vex::rotationUnits::deg);
        right_error=right_target-RightMotor1.rotation(vex::rotationUnits::deg);
        if(fabs(left_error)<=200||fabs(right_error)<=200)break;
        if(left_error>200)leftvelocity=maxV;
        if(left_error<-200)leftvelocity=-maxV;
        if(right_error>200)rightvelocity=maxV;
        if(right_error<-200)rightvelocity=-maxV;
        //instant_error=abs(LeftMotor1.velocity(vex::velocityUnits::pct))-abs(RightMotor1.velocity(vex::velocityUnits::pct));
        instant_error=fabs(left_error)-fabs(right_error);
        k=1-fabs(instant_error*k1);
        if(k<0.5)k=0.5;
        if(instant_error>0){
            Brain.Screen.drawRectangle(1,1,400,400,vex::color::green);
            rightvelocity*=k;
        }
        else {
            Brain.Screen.drawRectangle(1,1,400,400,vex::color::blue);
            leftvelocity*=k;
        }
        mmove(leftvelocity,rightvelocity);
    }
}

void autobrake(double left_target,double right_target, double maxV){
    double left_Kp=30,right_Kp=30,Ki=0.0000000,left_constantV=1000,right_constantV=1000;
    double left_integral=0,left_error;
    double right_integral=0,right_error;
    double leftvelocity,rightvelocity,instant_error,k,k1=0.1;
    double t=Brain.timer(vex::timeUnits::msec),time=Brain.timer(vex::timeUnits::msec);
    while(1){
        if(Brain.timer(vex::timeUnits::msec)-time>750)break;//2000
        Brain.Screen.drawRectangle(1,1,400,400,vex::color::yellow);        
        left_constantV=1000;
        right_constantV=1000;
        left_error=left_target-LeftMotor1.rotation(vex::rotationUnits::deg);
        right_error=right_target-RightMotor1.rotation(vex::rotationUnits::deg);
        leftvelocity=left_Kp*left_error + Ki*left_integral;
        rightvelocity=right_Kp*right_error + Ki*right_integral;
        left_integral=left_integral+left_error;
        right_integral=right_integral+right_error;
        if(fabs(left_error)<0.5)left_constantV=0;
        if(fabs(right_error)<0.5)right_constantV=0;            
        leftvelocity=left_Kp*left_error + Ki*left_integral;
        rightvelocity=right_Kp*right_error + Ki*right_integral;
        if(left_error>0)leftvelocity=leftvelocity+left_constantV;
        if(left_error<0)leftvelocity=leftvelocity-left_constantV;
        if(right_error>0)rightvelocity=rightvelocity+right_constantV;
        if(right_error<0)rightvelocity=rightvelocity-right_constantV;
        if(leftvelocity>maxV)leftvelocity=maxV;
        if(leftvelocity<-maxV)leftvelocity=-maxV;
        if(rightvelocity>maxV)rightvelocity=maxV;
        if(rightvelocity<-maxV)rightvelocity=-maxV;
        mmove(leftvelocity,rightvelocity);
        /*if(abs(left_error)<3&&abs(right_error)<3)Brain.Screen.drawRectangle(1,1,400,400,vex::color::red);//LED signal
        else Brain.Screen.drawRectangle(1,1,400,400,vex::color::green);*/
        //if(!left_constantV&&!right_constantV)break;
        if(left_constantV||right_constantV)t=Brain.timer(vex::timeUnits::msec);
        if(Brain.timer(vex::timeUnits::msec)-t>=100)break;
    }
}

void autostop(int i,int t) {
    LeftMotor1.stop(vex::brakeType::brake);
    LeftMotor2.stop(vex::brakeType::brake);
    RightMotor1.stop(vex::brakeType::brake);
    RightMotor2.stop(vex::brakeType::brake);
    if(i==0){
        LeftMotor1.resetRotation();
        LeftMotor2.resetRotation();
        RightMotor1.resetRotation();
        RightMotor2.resetRotation();
    }
    sleep(t);
}

void automove(double left, double right, double maxV, double time){
    double start_left,start_right,start_distance=200,left_target,right_target;
    start_left=left/2;
    start_right=right/2;
    if(start_left>start_distance)start_left=start_distance;
    if(start_left<-start_distance)start_left=-start_distance;
    if(start_right>start_distance)start_right=start_distance;
    if(start_right<-start_distance)start_right=-start_distance;
    maxV *= 130;
    left_target=LeftMotor1.rotation(vex::rotationUnits::deg)+left;
    right_target=RightMotor1.rotation(vex::rotationUnits::deg)+right;
    autostart(start_left,start_right, maxV);
    autorun(left_target,right_target,maxV,time);
    autobrake(left_target,right_target,maxV);
    // autostop(1,1);
    Stop(brake);
    sleep(1);
    ResetMotor();
}
//////////////////
// Turn by Gyro //
//////////////////
void Gautostart(double m, double maxV) {//left and right must smaller than 200
    double error,startV=4800,K=0.5;
    double leftvelocity,rightvelocity;
    double l=0;
    //read the initial value,set the target
    //reset the timer
    double target;
    target=GyroGetAngle() + m;
    double t=Brain.timer(vex::timeUnits::msec);
    //speed up
    while(1){
        if(Brain.timer(vex::timeUnits::msec)-t>2000)break;
        error=target-GyroGetAngle();
        leftvelocity=(fabs(m-error)*K+startV)*m/fabs(m);
        rightvelocity=(fabs(m-error)*K+startV)*m/fabs(m);
        
        // if(leftvelocity>maxV)leftvelocity=maxV;
        // if(leftvelocity<-maxV)leftvelocity=-maxV;
        // if(rightvelocity>maxV)rightvelocity=maxV;
        // if(rightvelocity<-maxV)rightvelocity=-maxV;
        leftvelocity = CONSTRAIN(leftvelocity, -maxV, maxV);
        rightvelocity = CONSTRAIN(rightvelocity, -maxV, maxV);
        
        mmove(leftvelocity,-rightvelocity);
        if(m>=0&&error<=0)l=1;
        if(m<=0&&error>=0)l=1;
        if(l)break;
    }
}

void Gautorun(double target, double maxV, double time){
    double error,leftvelocity,rightvelocity,instant_error,k,k1=0.023333;
    double t=Brain.timer(vex::timeUnits::msec);
    while(1){
         if(Brain.timer(vex::timeUnits::msec)-t>time)break;
        error=target-GyroGetAngle();
        if(fabs(error)<=200)break;
        if(error>200)leftvelocity=maxV;
        if(error<-200)leftvelocity=-maxV;
        if(error>200)rightvelocity=maxV;
        if(error<-200)rightvelocity=-maxV;
        //instant_error=abs(LeftMotor1.velocity(vex::velocityUnits::pct))-abs(RightMotor1.velocity(vex::velocityUnits::pct));
        instant_error=fabs(error)-fabs(error);
        k=1-fabs(instant_error*k1);
        if(k<0.5)k=0.5;
        if(instant_error>0){
            Brain.Screen.drawRectangle(1,1,400,400,vex::color::green);
            rightvelocity*=k;
        }
        else {
            Brain.Screen.drawRectangle(1,1,400,400,vex::color::blue);
            leftvelocity*=k;
        }
        mmove(leftvelocity,-rightvelocity);
    }
}

void Gautobrake(double target, double maxV){
    double left_Kp=10,right_Kp=10,Ki=0.0000000,left_constantV=1000,right_constantV=1000;
    double left_integral=0,left_error;
    double right_integral=0,right_error;
    double leftvelocity,rightvelocity;
    double t=Brain.timer(vex::timeUnits::msec),time=Brain.timer(vex::timeUnits::msec);
    while(1){
        if(Brain.timer(vex::timeUnits::msec)-time>750)break;//2000
        Brain.Screen.drawRectangle(1,1,400,400,vex::color::yellow);        
        left_constantV=1000;
        right_constantV=1000;
        left_error=target-GyroGetAngle();
        right_error=target-GyroGetAngle();
        leftvelocity=left_Kp*left_error + Ki*left_integral;
        rightvelocity=right_Kp*right_error + Ki*right_integral;
        left_integral=left_integral+left_error;
        right_integral=right_integral+right_error;
        if(fabs(left_error)<0.5)left_constantV=0;
        if(fabs(right_error)<0.5)right_constantV=0;            
        leftvelocity=left_Kp*left_error + Ki*left_integral;
        rightvelocity=right_Kp*right_error + Ki*right_integral;
        if(left_error>0)leftvelocity=leftvelocity+left_constantV;
        if(left_error<0)leftvelocity=leftvelocity-left_constantV;
        if(right_error>0)rightvelocity=rightvelocity+right_constantV;
        if(right_error<0)rightvelocity=rightvelocity-right_constantV;
        if(leftvelocity>maxV)leftvelocity=maxV;
        if(leftvelocity<-maxV)leftvelocity=-maxV;
        if(rightvelocity>maxV)rightvelocity=maxV;
        if(rightvelocity<-maxV)rightvelocity=-maxV;
        mmove(leftvelocity,-rightvelocity);
        /*if(abs(left_error)<3&&abs(right_error)<3)Brain.Screen.drawRectangle(1,1,400,400,vex::color::red);//LED signal
        else Brain.Screen.drawRectangle(1,1,400,400,vex::color::green);*/
        //if(!left_constantV&&!right_constantV)break;
        if(left_constantV||right_constantV)t=Brain.timer(vex::timeUnits::msec);
        if(Brain.timer(vex::timeUnits::msec)-t>=100)break;
    }
}


void Gautoturn(double m, double maxV, int time) {
    double start,start_distance=60,target;
    start=m/2;
    if(start>start_distance)start=start_distance;
    if(start<-start_distance)start=-start_distance;
    maxV *= 130;
    target=GyroGetAngle()+m;
    Gautostart(start, maxV);
    Gautorun(target,maxV,time);
    Gautobrake(target,maxV);
    // autostop(1,1);
    Stop(brake);
    sleep(1);
    ResetMotor();
}