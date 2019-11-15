//SJTU GO STRAIGHT
void mmove(double leftvelocity, double rightvelocity);
void autostart(double left, double right, double maxV);
void autorun(double left_target, double right_target, double maxV, double time);
void autobrake(double left_target,double right_target, double maxV);
void autostop(int i,int t);
void automove(double left, double right, double maxV, double time);
//WZL TURN
void Gautostart(double m, double maxV);
void Gautorun(double target, double maxV, double time);
void Gautobrake(double target, double maxV);
void Gautoturn(double m, double maxV, int time);