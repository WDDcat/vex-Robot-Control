void gyroInit();
void ResetMotor();
void Move(float lPower, float rPower);
void sMove(float lPower, float rPower);
void Stop(vex::brakeType type = vex::brake);
void Lift(int power);
void Tray(float power, vex::brakeType type = vex::brake, float rotation = 0.0);
void Intake(float power);

void spread(int target, int timeLimit);
bool goForward(int power, float target, float timeLimit);
bool goBackward(int power, float target, float timeLimit);
bool rushForward(int power, float target, float timeLimit);
bool rushBackward(int power, float target, float timeLimit);
bool turnLeft(int power, float target, float timeLimit);
bool turnRight(int power, float target, float timeLimit);
void backToWall(float power, int dis1, int dis2, int dis3, int dis4, int time, bool left);
bool turnLeftWithGyro(int power, float target, float timeLimit, bool fullTime);
bool turnRightWithGyro(int power, float target, float timeLimit, bool fullTime);
