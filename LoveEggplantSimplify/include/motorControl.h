#include <vex.h>

void gyroInit();  //初始化陀螺仪各项参数，pre_auton中调用
void ResetMotor();//重置电机相关设置
void Move(float lPower, float rPower);                        //电压控制底盘
void sMove(float lPower, float rPower);                       //rpm控制底盘  rotation per minute
void Stop(vex::brakeType type = vex::brake);                  //底盘停车，默认刹车方式为brake
void LowRoll(float power, vex::brakeType type = vex::coast);  //下滚轮旋转，power为0时停转，默认刹车方式为coast
void UpRoll(float power, vex::brakeType type = vex::coast);   //上滚轮旋转，power为0时停转，默认刹车方式为coast
void Roll(float power, vex::brakeType type = vex::coast);     //上下滚轮同时旋转，power为0时停转，默认刹车方式为coast
void Intake(float power, vex::brakeType type = vex::brake);   //吸球吐球，power为0时停转，默认刹车方式为brake

//使用PID方式，以最大功率为power的速度前进(0<power<100)，前进距离为target，超时时间为timeLimit
//默认PID为vex.h中的PID参数，也可在调用函数时通过传参规定其PID参数的值
bool goForward(int power, float target, float timeLimit, float P = KP, float I = KI, float D = KD); //前进时power > 0, target > 0
bool goBackward(int power, float target, float timeLimit, float P = KP, float I = KI, float D = KD);//后退时power > 0, target < 0

//不使用PID方式进行前进后退，即当行驶距离小于target时，均以power速度前进
//由于在起步时会出现仰头情况，故添加acc参数以缓加速启动，默认为false
bool rushForward(int power, float target, float timeLimit, bool acc = false);
bool rushBackward(int power, float target, float timeLimit, bool acc = false);

//使用PID方式，以最大功率为power的速度向左/右转(0<power<100)，target为陀螺仪的目标（绝对，非相对）值，超时时间为timeLimit
//默认PID为vex.h中的PID_TURN参数，也可在调用时通过传参规定其PID参数的值
bool turnLeftWithGyro(int power, float target, float timeLimit, bool fullTime = false, float P = KP_TURN, float I = KI_TURN, float D = KD_TURN);  //左转时power > 0
bool turnRightWithGyro(int power, float target, float timeLimit, bool fullTime, float P = KP_TURN, float I = KI_TURN, float D = KD_TURN); //右转时power > 0

//不使用PID方式进行向左/右转，即当陀螺仪的值未到达target时，均以power速度转向
bool rushLeftWithGyro(int power, float target, float timeLimit);
bool rushRightWithGyro(int power, float target, float timeLimit);