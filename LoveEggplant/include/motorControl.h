void gyroInit();
void Move(float lPower, float rPower);
void Stop(vex::brakeType type = vex::brake);
void Lift(int power);
void Tray(int power, vex::brakeType type = vex::brake);
void Intake(int power);

void spread();
bool goForward(int power, float target, float timeLimit);
bool goBackward(int power, float target, float timeLimit);
bool turnLeft(int power, float target, float timeLimit);
bool turnRight(int power, float target, float timeLimit);
void backToWall(float power, int dis1, int dis2, int dis3, int dis4, int time, bool left);
bool turnLeftWithGyro(int power, float target, float timeLimit);
bool turnRightWithGyro(int power, float target, float timeLimit);