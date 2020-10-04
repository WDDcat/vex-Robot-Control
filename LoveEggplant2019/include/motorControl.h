void gyroInit();
void ResetMotor();
void Move(float lPower, float rPower);
void sMove(float lPower, float rPower);
void Stop(vex::brakeType type = vex::brake);
void Lift(int power, vex::brakeType type = vex::hold);
void Tray(float power, vex::brakeType type = vex::brake, float rotation = 0.0);
void Intake(float power, vex::brakeType type = vex::brake);

void spread(bool preload);
int locateCube();
bool goForward(int power, float target, float timeLimit, float P = 0.6, float I = 0.007, float D = 4.0);
bool goBackward(int power, float target, float timeLimit, float P = 0.6, float I = 0.007, float D = 4.0);
bool rushForward(int power, float target, float timeLimit, bool acc = false);
bool rushBackward(int power, float target, float timeLimit, bool acc = false);
void backToWall(float power, int dis1, int dis2, int dis3, int dis4, int time, bool left);
bool turnLeft(int power, float target, float timeLimit, float P = 0.6, float I = 0.007, float D = 4.0);
bool turnRight(int power, float target, float timeLimit, float P = 0.6, float I = 0.007, float D = 4.0);
bool rushLeft(int power, float target, float timeLimit);
bool rushRight(int power, float target, float timeLimit);
bool turnLeftWithGyro(int power, float target, float timeLimit, bool fullTime, float P = 0.33, float I = 0.0001, float D = 1.25);
bool turnRightWithGyro(int power, float target, float timeLimit, bool fullTime, float P = 0.33, float I = 0.0001, float D = 1.25);
bool turnRightWithGyroL(int power, float target, float timeLimit, bool fullTime, float P = 0.33, float I = 0.0001, float D = 1.25);
bool turnLeftWithGyroR(int power, float target, float timeLimit, bool fullTime, float P = 0.33, float I = 0.0001, float D = 1.25);
bool rushLeftWithGyro(int power, float target, float timeLimit);
bool rushRightWithGyro(int power, float target, float timeLimit);
void autoTurnRight(float S,float a,int time1);
void autoTurnLeft(float S,float a,int time1);
void autoGoForward(float target,float a,int time1);