/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\PC                                               */
/*    Created:      Mon Aug 05 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_thread.h"
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;
vex::motor LF(PORT6, ratio18_1, true);
vex::motor XX(PORT7, ratio18_1, false);
vex::motor RB(PORT9, ratio18_1, true);
vex::motor LB(PORT11, ratio18_1, false);
vex::motor TT(PORT12, ratio18_1, false);
vex::motor RF(PORT21, ratio18_1, false);
vex::motor motor_19(PORT19, ratio36_1, false);
vex::motor motor_20(PORT20, ratio36_1, false);
vex::bumper bum_a(Brain.ThreeWirePort.A);
vex::limit limit_g(Brain.ThreeWirePort.G);
vex::pot pot_h(Brain.ThreeWirePort.H);
vex::pot pot_b(Brain.ThreeWirePort.B);
vex::controller con;

    // define your global instances of motors and other devices here

    /*---------------------------------------------------------------------------*/
    /*                          Pre-Autonomous Functions */
    /*                                                                           */
    /*  You may want to perform some actions before the competition starts. */
    /*  Do them in the following function.  You must return from this function
     */
    /*  or the autonomous and usercontrol tasks will not be started.  This */
    /*  function is only called once after the cortex has been powered on and */
    /*  not every time that the robot is disabled. */
    /*---------------------------------------------------------------------------*/
void aut_punch()
{
  motor_19.spin(directionType::rev, 100, velocityUnits::pct);
  motor_20.spin(directionType::rev, 100, velocityUnits::pct);
  task::sleep(300);
  motor_19.stop(brakeType::hold);
  motor_20.stop(brakeType::hold);
}

void aut_prepunch()
{
  while ((pot_h.value(rotationUnits::deg) >= 50) &&(!limit_g.pressing())) 
    {
      motor_19.spin(directionType::rev, 100, velocityUnits::pct);
      motor_20.spin(directionType::rev, 100, velocityUnits::pct);
    }
  
      motor_19.stop(brakeType::hold);
      motor_20.stop(brakeType::hold);
  
}

void aut__xx(int timex)
{
  XX.spin(directionType::fwd, 100, velocityUnits::pct);
  task::sleep(timex);
  XX.stop(brakeType::brake);
}

void aut_finish()
{
  XX.stop(brakeType::coast);
  TT.stop(brakeType::coast);
  LF.stop(brakeType::coast);
  LB.stop(brakeType::coast);
  RF.stop(brakeType::coast);
  RB.stop(brakeType::coast);
  motor_19.stop(brakeType::coast);
  motor_20.stop(brakeType::coast);
}

void aut_tt()
{
  TT.spin(directionType::fwd, 100, velocityUnits::pct);
  task::sleep(300);
  TT.spin(directionType::rev, 100, velocityUnits::pct);
  task::sleep(300);
  TT.stop(brakeType::brake);
}

void autoDriveDegrees(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    float Ss;
    if(S < 0)
    {
        Ss = S;
        S = -S;
    }

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
        getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
        
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=7+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        if(Ss>0)
        {
            RF.spin(directionType::fwd, v, velocityUnits::rpm);
            RB.spin(directionType::fwd, v, velocityUnits::rpm);
            LF.spin(directionType::fwd, v, velocityUnits::rpm);
            LB.spin(directionType::fwd, v, velocityUnits::rpm);
        }
        else if(Ss < 0)
        {
            LF.spin(directionType::rev, v, velocityUnits::rpm);
            LB.spin(directionType::rev, v, velocityUnits::rpm);
            RF.spin(directionType::rev, v, velocityUnits::rpm);
            RB.spin(directionType::rev, v, velocityUnits::rpm);
        }
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    task::sleep(100);
}

void aut_tygo(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    float Ss;
    if(S < 0)
    {
        Ss = S;
        S = -S;
    }

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
        getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
        TT.spin(directionType::fwd, 15, velocityUnits::pct);
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=7+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        if(Ss>0)
        {
            RF.spin(directionType::fwd, v, velocityUnits::rpm);
            RB.spin(directionType::fwd, v, velocityUnits::rpm);
            LF.spin(directionType::fwd, v, velocityUnits::rpm);
            LB.spin(directionType::fwd, v, velocityUnits::rpm);
        }
        else if(Ss < 0)
        {
            LF.spin(directionType::rev, v, velocityUnits::rpm);
            LB.spin(directionType::rev, v, velocityUnits::rpm);
            RF.spin(directionType::rev, v, velocityUnits::rpm);
            RB.spin(directionType::rev, v, velocityUnits::rpm);
        }
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    task::sleep(100);
}



void aut_yygo(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    float Ss;
    int t=0;
    if(S < 0)
    {
        Ss = S;
        S = -S;
    }

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
      if(t==0)
      {
       t=1;
       motor_19.spin(directionType::rev, 100, velocityUnits::pct);
       motor_20.spin(directionType::rev, 100, velocityUnits::pct);
       task::sleep(200);
      }
      if((pot_h.value(rotationUnits::deg) >= 50) &&(!limit_g.pressing())) 
    {
      motor_19.spin(directionType::rev, 100, velocityUnits::pct);
      motor_20.spin(directionType::rev, 100, velocityUnits::pct);
    }
    else
  {
      motor_19.stop(brakeType::hold);
      motor_20.stop(brakeType::hold);
  }
        getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
        
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=7+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        if(Ss>0)
        {
            RF.spin(directionType::fwd, v, velocityUnits::rpm);
            RB.spin(directionType::fwd, v, velocityUnits::rpm);
            LF.spin(directionType::fwd, v, velocityUnits::rpm);
            LB.spin(directionType::fwd, v, velocityUnits::rpm);
        }
        else if(Ss < 0)
        {
            LF.spin(directionType::rev, v, velocityUnits::rpm);
            LB.spin(directionType::rev, v, velocityUnits::rpm);
            RF.spin(directionType::rev, v, velocityUnits::rpm);
            RB.spin(directionType::rev, v, velocityUnits::rpm);
        }
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    task::sleep(100);
}

void aut_xxgo(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    float Ss;
    if(S < 0)
    {
        Ss = S;
        S = -S;
    }

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
         getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
      if ((pot_h.value(rotationUnits::deg) >= 50) &&(!limit_g.pressing())) 
    {
      motor_19.spin(directionType::rev, 100, velocityUnits::pct);
      motor_20.spin(directionType::rev, 100, velocityUnits::pct);
    }
     else
     {
        motor_19.stop(brakeType::hold);
      motor_20.stop(brakeType::hold);
     } 
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=5+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        if(Ss>0)
        {
            RF.spin(directionType::fwd, v, velocityUnits::rpm);
            RB.spin(directionType::fwd, v, velocityUnits::rpm);
            LF.spin(directionType::fwd, v, velocityUnits::rpm);
            LB.spin(directionType::fwd, v, velocityUnits::rpm);
            XX.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        else if(Ss < 0)
        {
            LF.spin(directionType::rev, v, velocityUnits::rpm);
            LB.spin(directionType::rev, v, velocityUnits::rpm);
            RF.spin(directionType::rev, v, velocityUnits::rpm);
            RB.spin(directionType::rev, v, velocityUnits::rpm);
            XX.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    XX.stop(brakeType::brake);
    task::sleep(100);
}


void autoTurnRight(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
        getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
        
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=5+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        
            LF.spin(directionType::fwd, v, velocityUnits::rpm);
            LB.spin(directionType::fwd, v, velocityUnits::rpm);
            RF.spin(directionType::rev, v, velocityUnits::rpm);
            RB.spin(directionType::rev, v, velocityUnits::rpm);
           
        
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    task::sleep(100);
}

void autoTurnLeft(float S,float a,int time1)
{
    float getS = 0;
    float vmax = 200;
    float v = 0;
    

    RB.resetRotation();
    LB.resetRotation();
    RF.resetRotation();
    LF.resetRotation();
    Brain.resetTimer();
    while(getS < S -3 && Brain.timer(timeUnits::msec) < time1)
    {
        getS = (abs(RB.rotation(rotationUnits::deg)) + abs(LB.rotation(rotationUnits::deg)) + abs(RF.rotation(rotationUnits::deg)) + abs(LF.rotation(rotationUnits::deg))) / 4;
        
        if( getS < 0)
        {
             getS = -1 * getS;
        }
        
        //getS = fabs(getS);
        
        if((S - vmax*vmax/a) < 0)
        {
            if(getS < S/2)
            {
                v = fabs(10+sqrt(getS*2*a));
            }
            else
            {
                v = fabs(sqrt((S-getS)*2*a));
            }
        }
        else
        {
            if(getS<vmax*vmax/(2*a))
            {
                v=5+sqrt(getS*2*a);   
            }
            
            else if(getS >= (vmax*vmax/(2*a)) && getS < (S-vmax*vmax/(2*a)))
            {
                v=vmax;
            }
            else if(getS>=(S-vmax*vmax/(2*a)))
            {
                v=sqrt((S-getS)*2*a);
            }
        }
        if(v < 0)
        {
          v = -v;
        }
        
            LF.spin(directionType::rev, v, velocityUnits::rpm);
            LB.spin(directionType::rev, v, velocityUnits::rpm);
            RF.spin(directionType::fwd, v, velocityUnits::rpm);
            RB.spin(directionType::fwd, v, velocityUnits::rpm);
           
        
        task::sleep(20);        
    }
    
    LF.stop(brakeType::brake);
    LB.stop(brakeType::brake);
    RF.stop(brakeType::brake);
    RB.stop(brakeType::brake);
    task::sleep(100);
}


void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

       aut_xxgo(-1060, 30,2500);
       aut__xx(200);
       aut_xxgo(1120, 50,  2500);

       autoTurnLeft(220, 40, 1000);       
       LF.spin(directionType::fwd, 60, velocityUnits::pct);
       LB.spin(directionType::fwd, 60, velocityUnits::pct);
       RF.spin(directionType::fwd, -60, velocityUnits::pct);
       RB.spin(directionType::fwd, -60, velocityUnits::pct);
       task::sleep(30);
       LF.stop(brakeType::hold);
       LB.stop(brakeType::hold);
       RF.stop(brakeType::hold);
       RB.stop(brakeType::hold);
       aut_yygo(1250, 50, 2000);
       autoDriveDegrees(-1200, 50, 2000);


       autoTurnLeft(100, 40, 1000); 
       aut_tygo(600, 40,  1500);
       TT.resetRotation();
       while(TT.rotation(rotationUnits::deg)>-100)
       {
       TT.spin(directionType::rev, 55, velocityUnits::pct);
       LF.spin(directionType::fwd, 20, velocityUnits::pct);
       LB.spin(directionType::fwd, 20, velocityUnits::pct);
       RF.spin(directionType::fwd, 20, velocityUnits::pct);
       RB.spin(directionType::fwd, 20, velocityUnits::pct);
       }

       while(TT.rotation(rotationUnits::deg)>-390)
       {
       TT.spin(directionType::rev, 55, velocityUnits::pct);
       LF.spin(directionType::fwd, 50, velocityUnits::pct);
       LB.spin(directionType::fwd, 50, velocityUnits::pct);
       RF.spin(directionType::fwd, 50, velocityUnits::pct);
       RB.spin(directionType::fwd, 50, velocityUnits::pct);
       }
       TT.stop(brakeType::hold);
       autoDriveDegrees(610, 50,  1300);
       TT.stop(brakeType::coast);
       autoDriveDegrees(-800, 50,  1300);
       task::sleep(300);
       aut_punch();
       aut_finish();
}

void usercontrol(void) {
  // User control code here, inside the loop
  int a, b, c, d, e,f,g,h,i;
  d=0;
  e=0;
  f=1;
  g=0;
  h=0;
  i=0;
 while (1) 
  {
    if(f==0)
    {
       motor_19.spin(directionType::rev, 0, velocityUnits::pct);
       motor_20.spin(directionType::rev, 0, velocityUnits::pct);
       LF.spin(directionType::fwd, 0,velocityUnits::pct);
       LB.spin(directionType::fwd, 0,velocityUnits::pct);
       RF.spin(directionType::fwd, 0,velocityUnits::pct);
       RB.spin(directionType::fwd, 0,velocityUnits::pct);
    }
    // Place drive control code here, inside the loop
    if ((d==0)&&((con.ButtonUp.pressing())||(bum_a.pressing())))
    {
       d=1;
       aut_xxgo(-1060, 30,2500);
       aut__xx(200);
       aut_xxgo(1100, 50,  2500);

       autoTurnLeft(215, 40, 1000);       
       LF.spin(directionType::fwd, 60, velocityUnits::pct);
       LB.spin(directionType::fwd, 60, velocityUnits::pct);
       RF.spin(directionType::fwd, -60, velocityUnits::pct);
       RB.spin(directionType::fwd, -60, velocityUnits::pct);
       task::sleep(30);
       LF.stop(brakeType::hold);
       LB.stop(brakeType::hold);
       RF.stop(brakeType::hold);
       RB.stop(brakeType::hold);
       aut_yygo(1250, 50, 2000);
       autoDriveDegrees(-1200, 50, 2000);
       autoTurnLeft(98, 40, 1000); 
       aut_tygo(600, 40,  1500);
       TT.resetRotation();
       while(TT.rotation(rotationUnits::deg)>-100)
       {
       TT.spin(directionType::rev, 55, velocityUnits::pct);
       LF.spin(directionType::fwd, 20, velocityUnits::pct);
       LB.spin(directionType::fwd, 20, velocityUnits::pct);
       RF.spin(directionType::fwd, 20, velocityUnits::pct);
       RB.spin(directionType::fwd, 20, velocityUnits::pct);
       }

       while(TT.rotation(rotationUnits::deg)>-390)
       {
       TT.spin(directionType::rev, 55, velocityUnits::pct);
       LF.spin(directionType::fwd, 50, velocityUnits::pct);
       LB.spin(directionType::fwd, 50, velocityUnits::pct);
       RF.spin(directionType::fwd, 50, velocityUnits::pct);
       RB.spin(directionType::fwd, 50, velocityUnits::pct);
       }
       TT.stop(brakeType::hold);
       autoDriveDegrees(610, 50,  1300);
       TT.stop(brakeType::coast);
       autoDriveDegrees(-800, 50,  1300);
       task::sleep(300);
       aut_punch();
       aut_finish();
       f=0;
    }
    c = 1;
    // PUNCH
    if (con.ButtonX.pressing()) 
    {
      motor_19.spin(directionType::rev, 100, velocityUnits::pct);
      motor_20.spin(directionType::rev, 100, velocityUnits::pct);
      c = 1;
    }
     else if (con.ButtonY.pressing()) 
    {
      motor_19.stop(brakeType::coast);
      motor_20.stop(brakeType::coast);
      c = 0;
    }
     else if ((pot_h.value(rotationUnits::deg) >= 50) &&(!limit_g.pressing()) && (c == 1)) 
    {
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(pot_h.value(rotationUnits::deg));
      motor_19.spin(directionType::rev, 100, velocityUnits::pct);
      motor_20.spin(directionType::rev, 100, velocityUnits::pct);
    }
     else if (c == 1) 
    {
      motor_19.stop(brakeType::hold);
      motor_20.stop(brakeType::hold);
    }
     else if (c == 0) 
    {
      motor_19.spin(directionType::rev, 0, velocityUnits::pct);
      motor_20.spin(directionType::rev, 0, velocityUnits::pct);
    }

    // XX
    if ((con.ButtonR1.pressing()) &&((pot_h.value(rotationUnits::deg) <53) || (limit_g.pressing())))
      XX.spin(directionType::fwd, 100, velocityUnits::pct);
    else if (con.ButtonR2.pressing())
      XX.spin(directionType::rev, 60, velocityUnits::pct);
    else
      XX.spin(directionType::fwd, 0, velocityUnits::pct);

    // TT
    if(con.ButtonA.pressing())
    {
      e=1;
    }  
    if(e==1)
    {
      TT.spin(directionType::rev, 100, velocityUnits::pct);
      task::sleep(200);
      TT.spin(directionType::rev, 5, velocityUnits::pct);
      task::sleep(200);
      TT.spin(directionType::fwd, 100, velocityUnits::pct);
      task::sleep(200);
      h=0;
      if(h==0)
      TT.stop(brakeType::coast);
      if(h==1)
      TT.stop(brakeType::hold);

      e=0;
    }

      if(con.ButtonB.pressing())
    {
      g=1;
    }  
    if(g==1)
    {
      while((pot_b.value(rotationUnits::deg) <=80))
      {
        TT.spin(directionType::rev, 70, velocityUnits::pct);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print(pot_b.value(rotationUnits::deg));
      }
        h=1;
     if(h==0)
      TT.stop(brakeType::coast);
      if(h==1)
      TT.stop(brakeType::hold);
      g=0;
    }
      if(con.ButtonLeft.pressing())
    {
      i=1;
    }  
    if(i==1)
    {
      while((pot_b.value(rotationUnits::deg) <=220))
      {
        TT.spin(directionType::rev, 70, velocityUnits::pct);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print(pot_b.value(rotationUnits::deg));
      }
        h=1;
     if(h==0)
      TT.stop(brakeType::coast);
      if(h==1)
      TT.stop(brakeType::hold);
      i=0;
    }
       
    if (con.ButtonL1.pressing())
      {
        TT.spin(directionType::rev, 100, velocityUnits::pct);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print(pot_b.value(rotationUnits::deg));
        h=1;
      }
    else if (con.ButtonL2.pressing())
    {
      TT.spin(directionType::fwd, 100, velocityUnits::pct);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(pot_b.value(rotationUnits::deg));   
      h=0;
    }
      else
      {
      if(h==0)
      TT.stop(brakeType::coast);
      if(h==1)
      TT.stop(brakeType::hold);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print(pot_b.value(rotationUnits::deg));
      }
    // MOVE
    if (((abs(con.Axis3.position(percentUnits::pct))) >= 10) || (abs(con.Axis4.position(percentUnits::pct)) >= 10))
         { 
           f=1;
           a = con.Axis3.position(percentUnits::pct); 
           b = con.Axis4.position(percentUnits::pct);
           LF.spin(directionType::fwd, (0.9 * a + 0.7 * b),velocityUnits::pct);
           LB.spin(directionType::fwd, (0.9 * a + 0.7 * b),velocityUnits::pct);
           RF.spin(directionType::fwd, (0.9 * a - 0.7 * b),velocityUnits::pct);
           RB.spin(directionType::fwd, (0.9 * a - 0.7 * b),velocityUnits::pct);
         }
     else
         {
           LF.spin(directionType::fwd, 0,velocityUnits::pct);
           LB.spin(directionType::fwd, 0,velocityUnits::pct);
           RF.spin(directionType::fwd, 0,velocityUnits::pct);
           RB.spin(directionType::fwd, 0,velocityUnits::pct);
         }
      vex::task::sleep(20); // Sleep the task for a short amount of
                                     // time to prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (1) {
    vex::task::sleep(100); // Sleep the task for a short amount of time to
                           // prevent wasted resources.
  }
}