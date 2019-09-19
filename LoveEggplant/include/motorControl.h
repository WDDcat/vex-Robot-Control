void Move(int lPower, int rPower);
void Stop(vex::brakeType type = vex::brake);
void Lift(int power);
void Tray(int power, vex::brakeType type = vex::brake);
void Intake(int power);

void spread();
bool goForward(int power, float target, float timeLimit);
bool Turn(int power, float target, float timeLimit);
void backToWall(float power, int dis1, int dis2, int dis3, int dis4, int time, bool left);