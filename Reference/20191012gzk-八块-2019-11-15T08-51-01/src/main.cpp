

#include "vex.h"

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
int liftrot,xirot1,xirot2,openrot;
int kexiezidongshijian;
int zidong=1;
int a=0;
int aa;
int d=0;
int j2=0;
int direction=-1;
int timersb=0;
int timersb1=0;
int timersb2=0;
int timersb3=0;
int timersb4=0;
int autontanstate=0;
int out=0;
double tanbianmaduzhii;
double shutuoluoduzhii;
double lduzhii1;
double lduzhii2;
double rduzhii1;
double rduzhii2;
double fanbianmaduzhii;
const float HSpdTicks = 392; //IME counts per revolution
const float HTorqTicks = 627.2;
const float TurboTicks =360;
int launchready = 1;
int PIDerror = 0; //PID DIagnostics Var
float PIDtimer = 0.0;
volatile bool brakeActive = false;
//--Tunable Variables--//
float dkP = 1.0;
float dkI = 1.0;
float dkD = 1.0;
float dkL = 50.0;
float gkP = 1.0;
float gkI = 1.0;
float gkD = 1.0;
float gkL = 50.0;
double frot = 10;
int gaitiaopanzi=0;
int sbsb;
int flagta=0;

int taihuatiflag=0;
void TTimertask()
{
  
    while(1)
    {
       
        vex::task::sleep(50);
        timersb+=50;
        timersb1+=50;
        timersb2+=50;
        timersb3+=50;
        timersb4+=50;
        Brain.Screen.printAt(100,100,"Timersb1= %d%%",timersb1);
        Brain.Screen.printAt(100,120,"Tanbianma= %lf%%",1.0*Tanbianma.rotation(rotationUnits::deg));
        
         if(Controller1.ButtonX.pressing()==1)
         {
         
         
           while(Controller1.ButtonX.pressing()==1);
           flagta=1-flagta;
          
          }


        if(taihuatiflag==1)
        {
          Lift1.spin(vex::directionType::fwd,1.0*0.2*(-2600-Lift1.rotation(rotationUnits::deg)), vex::velocityUnits::pct);
          /*if(timersb4 % 400 <= 200)
      {
          Xis1.spin_s( directionType::fwd, 0 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, 0 , voltageUnits::volt );
      }
      else
      {
          Xis1.spin_s( directionType::fwd, -100 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, -100 , voltageUnits::volt );
      }*/
        }
    }
}

/*
void DriveInitPID1(float sKp, float sKi, float sKd, float sKl, float rKp, float rKi, float rKd, float rKl)
{
	dkP = sKp;//laihuihuang shuzhi de yiban
	dkI = sKi;//yiban wei 0,zuli yong
	dkD = sKd;//
	dkL = sKl;//10
	gkP = rKp;//0
	gkI = rKi;//0
	gkD = rKd;//0
	gkL = rKl;//0
}
*/
void drivesb(float mtarget,int timemax,int powermax)
{
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation();
    int result=0;
    powermax=powermax*1.0*12/100;
    double l1, l2, r1, r2;
    float mrotation;
    timersb1=0;
    mtarget=mtarget*1.0*300/40;
    while(timersb1<=200)
    {
       if (mtarget>0)
       {
        LeftRun1.spin_s( directionType::fwd,8, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, 8, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, -8, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, -8, voltageUnits::volt );
       }
        else 
        {
        LeftRun1.spin_s( directionType::fwd,-8, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, -8, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, 8, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, 8, voltageUnits::volt );
        }
    }
    while(timersb1<=timemax)
    {
        mrotation=1.0*(Left1.rotation(rotationUnits::deg)+Left2.rotation(rotationUnits::deg)+Right1.rotation(rotationUnits::deg)+Right2.rotation(rotationUnits::deg))/4.0;
        l1 = 1.0*1.0*(mtarget-Left1.rotation(rotationUnits::deg))*12.0/144;
        l2 = 1.0*1.0*(mtarget-Left2.rotation(rotationUnits::deg))*12.0/144;
        r1 = -1.0*1.0*(mtarget+Right1.rotation(rotationUnits::deg))*12.0/144;
        r2 = -1.0*1.0*(mtarget+Right2.rotation(rotationUnits::deg))*12.0/144;
        Brain.Screen.printAt(100,120,"l1=%lf",l1);
        Brain.Screen.printAt(100,140,"l2=%lf",l2);
        Brain.Screen.printAt(100,160,"r1=%lf",r1);
        Brain.Screen.printAt(100,180,"r2=%lf",r2);
        if(l1 > powermax)    l1 = powermax;
        if(l1 < -powermax)    l1 = -powermax;
        if(l2 > powermax)    l2 = powermax;
        if(l2 < -powermax)    l2 = -powermax;
        if(r1 > powermax)    r1 = powermax;
        if(r1 < -powermax)    r1 = -powermax;
        if(r2 > powermax)    r2 = powermax;
        if(r2 < -powermax)    r2 = -powermax;
        LeftRun1.spin_s( directionType::fwd, l1, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, l2, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, r1, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, r2, voltageUnits::volt ); 
        /*LeftRun1.spin_s( directionType::fwd, 0.448*(mtarget-Left1.rotation(rotationUnits::deg))*12.0/144, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, 0.448*(mtarget-Left2.rotation(rotationUnits::deg))*12.0/144, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, 0.448*(-mtarget-Right1.rotation(rotationUnits::deg))*12.0/144, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, 0.448*(-mtarget-Right2.rotation(rotationUnits::deg))*12.0/144, voltageUnits::volt ); 
        */
    }
    
    
    Left1.stop();
    Left2.stop();
    Right1.stop();
    Right2.stop();
    
}


void turn(float mtarget,int timemax,int powermax)
{
    //powermax=powermax*1.0/100*12;
    powermax=powermax*1.0/100.0*12.0;
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation();
    int result=0;
    int l1, l2, r1, r2;
    timersb1=0;
    float mrotation;
    if(abs(mtarget)>30)
    {
	mtarget =  (25.0*mtarget/(3.1415926*4));
    while(timersb1<=timemax)
    {
        mrotation=1.0*(Left1.rotation(rotationUnits::deg)+Left2.rotation(rotationUnits::deg)+Right1.rotation(rotationUnits::deg)+Right2.rotation(rotationUnits::deg))/4.0;
        l1 = 1.0*1.15*(mtarget-Left1.rotation(rotationUnits::deg))*12.0/144;
        l2 = 1.0*1.15*(mtarget-Left2.rotation(rotationUnits::deg))*12.0/144;
        r1 = 1.0*1.15*(mtarget-Right1.rotation(rotationUnits::deg))*12.0/144;
        r2 = 1.0*1.15*(mtarget-Right2.rotation(rotationUnits::deg))*12.0/144;
        if(l1 > powermax)    l1 = powermax;
        if(l1 < -powermax)    l1 = -powermax;
        if(l2 > powermax)    l2 = powermax;
        if(l2 < -powermax)    l2 = -powermax;
        if(r1 > powermax)    r1 = powermax;
        if(r1 < -powermax)    r1 = -powermax;
        if(r2 > powermax)    r2 = powermax;
        if(r2 < -powermax)    r2 = -powermax;
        LeftRun1.spin_s( directionType::fwd, l1, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, l2, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, r1, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, r2, voltageUnits::volt ); 
        
        /*
        LeftRun1.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt ); 
        */
    }
    }
    else
    {
     mtarget =  (25.0*mtarget/(3.1415926*4));
    while(timersb1<=timemax)
    {
        mrotation=1.0*(Left1.rotation(rotationUnits::deg)+Left2.rotation(rotationUnits::deg)+Right1.rotation(rotationUnits::deg)+Right2.rotation(rotationUnits::deg))/4.0;
        l1 = 1.0*2.3*(mtarget-Left1.rotation(rotationUnits::deg))*12.0/144;
        l2 = 1.0*2.3*(mtarget-Left2.rotation(rotationUnits::deg))*12.0/144;
        r1 = 1.0*2.3*(mtarget-Right1.rotation(rotationUnits::deg))*12.0/144;
        r2 = 1.0*2.3*(mtarget-Right2.rotation(rotationUnits::deg))*12.0/144;
        if(l1 > powermax)    l1 = powermax;
        if(l1 < -powermax)    l1 = -powermax;
        if(l2 > powermax)    l2 = powermax;
        if(l2 < -powermax)    l2 = -powermax;
        if(r1 > powermax)    r1 = powermax;
        if(r1 < -powermax)    r1 = -powermax;
        if(r2 > powermax)    r2 = powermax;
        if(r2 < -powermax)    r2 = -powermax;
        LeftRun1.spin_s( directionType::fwd, l1, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, l2, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, r1, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, r2, voltageUnits::volt ); 
        /*
        LeftRun1.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, 1.15*(mtarget-mrotation)*12.0/144, voltageUnits::volt ); 
        */
    }   
    }
    Left1.stop();
    Left2.stop();
    Right1.stop();
    Right2.stop();
    
}
/*
void drive(float mtarget, int timemax, int powermax)
{
    int lerror = 0;
    int rerror = 0;
	int lpError = 0;
    int rpError = 0;
	int lp = 0;
	int li = 0;
	int ld = 0;
    int rp = 0;
	int ri = 0;
	int rd = 0;
	int GpError = 0;
	int Gp = 0;
	int Gi = 0;
	int Gd = 0;
	int lpower=0;
    int rpower=0;
	int driveLeft=0;
	int driveRight=0;
	int turning = 0;
    int ab = 0;
    int lattarget=0;
    int rattarget=0;
	//long atTargetTime = nPgmTime;
	//bool atTarget = false;
	//int ramp;
    //vex::task::sleep(500);
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation();
	
	timersb1 = 0;

	mtarget =  (100.0*mtarget/(3.1415926*4));
	while(timersb1 < timemax)
	{
        //Brain.Screen.printAt(50,100,"tgt= %f%%",mtarget);
        //Brain.Screen.printAt(50,120,"error= %d%%",error);
        //Brain.Screen.printAt(50,120,"timersb1= %d%%",timersb1);
        Brain.Screen.printAt(50,140,"left= %lf%%",Left1.rotation(vex::rotationUnits::deg));
        Brain.Screen.printAt(50,160,"right= %lf%%",-Right1.rotation(vex::rotationUnits::deg));
        
        //Brain.Screen.printAt(50,160,"power= %d%%",power);
		lerror = mtarget - ((Left1.rotation(vex::rotationUnits::deg)+Left2.rotation(vex::rotationUnits::deg)))/2;//fang xiang kongzhi
		rerror = mtarget + ((Right1.rotation(vex::rotationUnits::deg)+Right2.rotation(vex::rotationUnits::deg)))/2;//fang xiang kongzhi
		
        //PIDerror = error;
		//error1 = error;
		//drive
		lp = lerror;
		li = abs(li + lerror) < dkL ? li+ lerror : abs(li + lerror)/(li + lerror)*dkL;
		ld = lerror - lpError;
        
        rp = rerror;
		ri = abs(ri + rerror) < dkL ? ri+ rerror : abs(ri + rerror)/(ri + rerror)*dkL;
		rd = rerror - rpError;
		//straighten
		//Gp = SensorValue[gyro1];
		//Gi = abs(i + SensorValue[gyro1]) < gkL ? i+ SensorValue[gyro1] : sgn(i + SensorValue[gyro1])*gkL;
		//Gd = error - pError;

		lpError = lerror;
        rpError = rerror;
		//GpError = SensorValue[gyro1];

		//ramp = (nPgmTime - atTargetTime) * 2.7;

		if(mtarget>=70||mtarget<=-70)
        {
            lpower = lp*dkP + li*dkI + ld*dkD + 5;
            rpower = rp*dkP + ri*dkI + rd*dkD;
        }
        else 
        {
            lpower = lp*dkP + li*dkI + ld*dkD + 0.5;
            rpower = rp*dkP + ri*dkI + rd*dkD;
        }
		//turning = Gp*gkP + Gi*gkI + Gd*gkD;


		if(abs(lpower) < 30)
	        lattarget=1;
        if(abs(rpower) < 30)
            rattarget=1;
        
            //break;

		

		//if(!lattarget)
            driveLeft =  -(lpower);
        //else
         //  driveLeft =0;
        
       // if(!rattarget)
        driveRight =  -(rpower);
        //else
          //  driveRight = 0;

		driveLeft = abs(driveLeft) < powermax ? driveLeft : abs(driveLeft)/(driveLeft)*powermax;
        driveRight = abs(driveRight) < powermax ? driveRight : abs(driveRight)/(driveRight)*powermax;

		//motor[wave1] = -driveLeft;//kan lun zi gai + -
        if(!lattarget)
        {
            Left1.spin(vex::directionType::fwd,-driveLeft,vex::velocityUnits::pct);
            Left2.spin(vex::directionType::fwd,-driveLeft,vex::velocityUnits::pct);
        }
        else
        {
            Left1.stop();
            Left2.stop();
        
        }
        if(!rattarget)
        {
        Right1.spin(vex::directionType::fwd,driveRight,vex::velocityUnits::pct);
        Right2.spin(vex::directionType::fwd,driveRight,vex::velocityUnits::pct);
       }
        else
        {
        Right1.stop();
        Right2.stop();
        
        }
	}
        Left1.stop();
        Left2.stop();
        Right1.stop();
        Right2.stop();
    
	

}


void turnsb(float mtarget, int timemax, int powermax)
{
    int lerror = 0;
    int rerror = 0;
	int lpError = 0;
    int rpError = 0;
	int lp = 0;
	int li = 0;
	int ld = 0;
    int rp = 0;
	int ri = 0;
	int rd = 0;
	int GpError = 0;
	int Gp = 0;
	int Gi = 0;
	int Gd = 0;
	int lpower=0;
    int rpower=0;
	int driveLeft=0;
	int driveRight=0;
    int lattarget=0,rattarget=0;
	int turning = 0;
    int ab = 0;
	//long atTargetTime = nPgmTime;
	//bool atTarget = false;
	int ramp;
    //vex::task::sleep(500);
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation();
	
	timersb1 = 0;

	mtarget =  (25.0*mtarget/(3.1415926*4));
	while(timersb1 < timemax)
	{
        //Brain.Screen.printAt(50,100,"tgt= %f%%",mtarget);
        Brain.Screen.printAt(50,120,"timersb1= %d%%",timersb1);
        Brain.Screen.printAt(50,140,"left= %lf%%",Left1.rotation(vex::rotationUnits::deg));
        Brain.Screen.printAt(50,160,"right= %lf%%",Right1.rotation(vex::rotationUnits::deg));
        
        //Brain.Screen.printAt(50,160,"power= %d%%",power);
		lerror = mtarget - (Left1.rotation(vex::rotationUnits::deg));//fang xiang kongzhi
		rerror = mtarget - (Right1.rotation(vex::rotationUnits::deg));//fang xiang kongzhi
		
        //PIDerror = error;
		//error1 = error;
		//drive
		lp = lerror;
		li = abs(li + lerror) < dkL ? li+ lerror : abs(li + lerror)/(li + lerror)*dkL;
		ld = lerror - lpError;
        
        rp = rerror;
		ri = abs(ri + rerror) < dkL ? ri+ rerror : abs(ri + rerror)/(ri + rerror)*dkL;
		rd = rerror - rpError;
		//straighten
		//Gp = SensorValue[gyro1];
		//Gi = abs(i + SensorValue[gyro1]) < gkL ? i+ SensorValue[gyro1] : sgn(i + SensorValue[gyro1])*gkL;
		//Gd = error - pError;

		lpError = lerror;
        rpError = rerror;
		//GpError = SensorValue[gyro1];

		//ramp = (nPgmTime - atTargetTime) * 2.7;

		lpower = 1.4*lp*dkP + li*dkI + ld*dkD;
        rpower = 1.4*rp*dkP + ri*dkI + rd*dkD;
		//turning = Gp*gkP + Gi*gkI + Gd*gkD;

		if(abs(lpower) < 20)
	        lattarget=1;
        if(abs(rpower) < 20)
            rattarget=1;
        
            //break;
        driveLeft = -lpower;
        driveRight = -rpower;
		driveLeft = abs(driveLeft) < powermax ? driveLeft : abs(driveLeft)/(driveLeft)*powermax;
        driveRight = abs(driveRight) < powermax ? driveRight : abs(driveRight)/(driveRight)*powermax;


		

		
            Left1.spin(vex::directionType::fwd,-driveLeft,vex::velocityUnits::pct);
            Left2.spin(vex::directionType::fwd,-driveLeft,vex::velocityUnits::pct);
       
            Right1.spin(vex::directionType::fwd,-driveRight,vex::velocityUnits::pct);
            Right2.spin(vex::directionType::fwd,-driveRight,vex::velocityUnits::pct);
        

	}
        Left1.stop();
        Left2.stop();
        Right1.stop();
        Right2.stop(); 


}
*/
void simplemove(int power)
{
   
        LeftRun1.spin_s( directionType::fwd, power*12.0/100, voltageUnits::volt );
        LeftRun2.spin_s( directionType::fwd, power*12.0/100, voltageUnits::volt );
        RightRun1.spin_s( directionType::fwd, -power*12.0/100, voltageUnits::volt );
        RightRun2.spin_s( directionType::fwd, -power*12.0/100, voltageUnits::volt );
         
}

void simpleturn(int power)
{
  Left1.spin( directionType::fwd, power*12.0/100, voltageUnits::volt );
  Left2.spin( directionType::fwd, power*12.0/100, voltageUnits::volt );
  Right1.spin( directionType::fwd, power*12.0/100, voltageUnits::volt );
  Right2.spin( directionType::fwd, power*12.0/100, voltageUnits::volt );
}


double tuoluo;
void dutuoluotask()
{
    while(1)
    {
        tuoluo = mGyro.value(vex::rotationUnits::deg);
        Brain.Screen.printAt(1,40,"tuoluo=%lf%%",tuoluo);
    }
}

bool RTE=0;

void v5cyka()
{
//drivesb(42,5000,100);//1 ge qianjin 0kuai
//drivesb(42*2,5000,100);//2 ge qianjin 0kuai
//drivesb(-42,5000,100);//1 ge houtui 0kuai
//drivesb(42,5000,100);//1 ge qianjin 8kuai
//turn(70,5000,100);//90 du shunshizhen 0kuai
//turn(-66.5,5000,100);//90 du nishizhen 0kuai
//turn(35,5000,100);//45 du shunshizhen 0kuai
//turn(-35,5000,100);//45 du nishizhen 0kuai
//turn(63.5,5000,80);//90 du shunshizhen 4kuai
//turn(-61,5000,80);//90 du nishizhen 4kuai
//turn(35,5000,100);//45 du shunshizhen 4kuai
//turn(-38,5000,100);//45 du nishizhen 4kuai
//turn(62,5000,80);//90 du shunshizhen 8kuai
//turn(-60,5000,80);//90 du nishizhen 8kuai
//turn(35,5000,100);//45 du shunshizhen 8kuai
//turn(-36,5000,100);//45 du nishizhen 8kuai
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) 
{
    vex::thread tTTimer(TTimertask);
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation(); 
    Lift1.resetRotation();
    Xi1.resetRotation();
    Xi2.resetRotation();
    Open2.resetRotation();
    Tanbianma.resetRotation();
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

void Xis(int power)
{
  Xis1.spin_s( directionType::fwd, power , voltageUnits::volt );
  Xis2.spin_s( directionType::fwd, power , voltageUnits::volt );
          
}

void xi(int power)
{
  Xi1.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
  Xi2.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
 
}
void xistop()
{
  Xi1.stop(brakeType::hold);
  Xi2.stop(brakeType::hold);
 
}
void xistopopen()
{
  Xi1.stop();
  Xi2.stop();
 
}
void armlift(int power)
{
  Lift1.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
 // while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
  //Lift1.spin(vex::directionType::fwd, power/3, vex::velocityUnits::pct);
  while(Tanbianma.rotation(vex::rotationUnits::deg)<=70.0);
  Lift1.stop(brakeType::hold);
}

void one()
{
  drivesb(21,800,100);
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  task::sleep(2000);
  xi(-100);
  //xistop();
  //simplemove(0);
}
void two()
{
 
}

void three()
{
 drivesb(-42,5000,100);
 turn(-60-36,5000,80);
 Lift1.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
 drivesb(21,1000,100);
 armlift(100);
}

void auton1(int direction)//zheng chang qian chang jia shang tai//21.5s
{
    //drivesb(42,5000,100);//1 ge qianjin 0kuai
    //drivesb(42*2,5000,100);//2 ge qianjin 0kuai
    //drivesb(-42,5000,100);//1 ge houtui 0kuai
    //drivesb(42,5000,100);//1 ge qianjin 8kuai
    //turn(70,5000,100);//90 du shunshizhen 0kuai
    //turn(-66.5,5000,100);//90 du nishizhen 0kuai
    //turn(35,5000,100);//45 du shunshizhen 0kuai
    //turn(-35,5000,100);//45 du nishizhen 0kuai
    //turn(63.5,5000,80);//90 du shunshizhen 4kuai
    //turn(-61,5000,80);//90 du nishizhen 4kuai
    //turn(35,5000,100);//45 du shunshizhen 4kuai
    //turn(-38,5000,100);//45 du nishizhen 4kuai
    //turn(62,5000,80);//90 du shunshizhen 8kuai
    //turn(-60,5000,80);//90 du nishizhen 8kuai
    //turn(35,5000,100);//45 du shunshizhen 8kuai
    //turn(-36,5000,100);//45 du nishizhen 8kuai
    
    //Xis(-100);
    //taihuatiflag=1;
    //while(1);
    
    
    //one();

     //drivesb(21,800,100);

  
  
 // simplemove(80);
  
//  task::sleep(400);
  
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=1100)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(42+32,2500,40);
    if(direction == 1)
 	    turn(-22,800,80); 
 	  else if(direction == -1)
      turn(22.5,810,80); 

Lift1.resetRotation();

    simplemove(-100);
    task::sleep(1600);
     simplemove(0);
    /*Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    while(Tanbianma.rotation(vex::rotationUnits::deg)<20.0);
    Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    task::sleep(200);
    Lift1.stop();*/
    drivesb(42+26,2700,40);
    /*xi(100);
    task::sleep(150);
    xi(0);*/
    if(direction == 1)
      { 
 	     turn(60+40,1900,80); 
      }
 	  else if(direction == -1)
     { 
 	     turn(-60-40,1900,80); 
     }
     taihuatiflag=1;
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xistopopen();
     if(direction == 1)
      { 
 	     drivesb(42+57,1700,40);
      }
 	  else if(direction == -1)
     {
    drivesb(42+57,1700,40);
     }
    taihuatiflag=0;
    xi(100);
    task::sleep(150);
    xi(0);
    timersb3=0;
    //simplemove(-60);
    /*while(timersb3<=1500)
    {
      Lift1.spin(vex::directionType::fwd,-80, vex::velocityUnits::pct);

    }*/
    while(timersb3<=1100)
    {
      Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
      if(timersb3 % 800 <= 200)
      {
          Xis1.spin_s( directionType::fwd, 0 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, 0 , voltageUnits::volt );
      }
      else
      {
          Xis1.spin_s( directionType::fwd, -100 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, -100 , voltageUnits::volt );
      }
    }
    xi(0);
    Lift1.stop();
   //task::sleep(200);
   simplemove(-40);
   task::sleep(1000);
   simplemove(0);

   //armlift(-60);
    //
    //task::sleep(500);
    //

   
}
void auton111(int direction)
{
  turn(22,2000,80);
 
  //simplemove(80);
  
  /*task::sleep(300);
  
  simplemove(-80);
  xi(100);
  task::sleep(800);
  simplemove(0);
  Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(35,600,100);
    drivesb(50,1800,40);
    if(direction == 1)
 	    turn(-22.75,820,80); 
 	  else if(direction == -1)
      turn(22,900,80); 

Lift1.resetRotation();

    simplemove(-100);
    task::sleep(1700);
     simplemove(0);*/
     
}
void auton11(int direction)
{
 
  simplemove(80);
  
  task::sleep(300);
  
  simplemove(-80);
  xi(100);
  task::sleep(800);
  simplemove(0);
  
  ////////////task::sleep(2000);
 /* timersb2=0;

while(timersb2<=1100)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();*/
//simplemove(-100);
  
  
  
  //xi(-100);
    
    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
   drivesb(35,600,100);
    drivesb(50,1600,40);
   // drivesb(42+32,2500,40);
  /*  if(direction == 1)
 	    turn(-20,1650,80); 
 	  else if(direction == -1)
      turn(20,1500,80);*/
    task::sleep(200);
    if(direction == 1)
    {
      simpleturn(-40);
    task::sleep(315);
     simplemove(0);
     }
    else if(direction == -1)
    {
      simpleturn(40);
    task::sleep(325);
     simplemove(0);
     }
     task::sleep(200);
Lift1.resetRotation();

    simplemove(-100);
    task::sleep(2100);
     simplemove(0);
    /*Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    while(Tanbianma.rotation(vex::rotationUnits::deg)<20.0);
    Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    task::sleep(200);
    Lift1.stop();*/
    drivesb(35,600,100);
    drivesb(50,1600,40);
    //drivesb(42+30,2700,45);
    /*xi(100);
    task::sleep(150);
    xi(0);*/
    if(direction == 1)
      { 
 	     turn(60+41,1900,80); 
      }
 	  else if(direction == -1)
     { 
 	     turn(-60-41,1900,80); 
     }
     taihuatiflag=1;
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xistopopen();
     if(direction == 1)
      { 
 	     drivesb(42+63,1670,45);
      }
 	  else if(direction == -1)
     {
    drivesb(42+63,1670,45);
     }
    taihuatiflag=0;
   xi(100);
    task::sleep(120);
    xi(0);
    timersb3=0;
    simplemove(30);
    while(timersb3<=1700)
    {
      Lift1.spin(vex::directionType::fwd,-85, vex::velocityUnits::pct);

    }
    simplemove(0);
   /* while(timersb3<=1100)
    {
      Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
      if(timersb3 % 800 <= 200)
      {
          Xis1.spin_s( directionType::fwd, 0 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, 0 , voltageUnits::volt );
      }
      else
      {
          Xis1.spin_s( directionType::fwd, -100 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, -100 , voltageUnits::volt );
      }
    }*/
    xi(0);
    Lift1.stop();
    task::sleep(300);
   simplemove(-100);
   task::sleep(1000);
   simplemove(0);
}
void auton2(int direction)
{
  simplemove(100);
  
  task::sleep(500);
  
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=2000)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=1500)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>1500&&timersb2<=1800)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>1800)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  
  }
}
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(50,2000,50);
    if(direction == 1)
 	    turn(-66,1200,100); 
 	  else if(direction == -1)
      turn(66,1200,100); 
    drivesb(42,2000,80);
  taihuatiflag=1;
    if(direction == 1)
 	    turn(-40,1000,100); 
 	  else if(direction == -1)
      turn(40,1000,100); 
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xi(80);
    task::sleep(230);
    xi(0);
    xistopopen();
    drivesb(19,1000,100);
    taihuatiflag=0;
    timersb3=0;
    //simplemove(-60);
    while(timersb3<=1100)
    {
      Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);

    }
    Lift1.stop();
    xi(0);
    //armlift(-100);
    drivesb(-25,1500,80);
     
    Lift1.stop();
    /* Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
     if(direction == 1)
 	    turn(110,1200,80); 
 	  else if(direction == -1)
      turn(-110,1200,80);
    Lift1.stop();*/
    // Xis(-100);
   /* drivesb(42+15,1000,100);
    xistop();
   timersb2=0;
   while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0)
   {
   if (timersb2%1600<=800)
   {
     xi(100);
   }
    else
   {
    xi(0);
    }
  }
  Lift1.spin(vex::directionType::fwd, 100/3, vex::velocityUnits::pct);
  while(Tanbianma.rotation(vex::rotationUnits::deg)<=70.0)
  {
   if (timersb2%1600<=800)
   {
     xi(100);
   }
    else
   {
    xi(0);
    }
  }
  Lift1.stop(brakeType::hold);
  xi(0);
  simplemove(60);
   task::sleep(100);*/
}
    
void auton3(int direction)
{
  simplemove(80);
  
  task::sleep(450);
  
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=1800)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -6, vex::velocityUnits::pct);
    drivesb(42+32,2500,40);
    if(direction == 1)
 	    turn(-22,800,80); 
 	  else if(direction == -1)
      turn(22,800,80); 

//Lift1.resetRotation();

    simplemove(-100);
    task::sleep(1800);
     simplemove(0);
    /*Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    while(Tanbianma.rotation(vex::rotationUnits::deg)<20.0);
    Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    task::sleep(200);
    Lift1.stop();*/
    drivesb(42+29,2700,40);
    if(direction == 1)
 	    turn(-20,1000,80); 
 	  else if(direction == -1)
      turn(18,800,80); 
    drivesb(30,1000,40);
    drivesb(-7,800,40);
    if(direction == 1)
 	    turn(-14,900,80); 
 	  else if(direction == -1)
      turn(13,800,80); 
    drivesb(30,2000,50);
    /*xi(100);
    task::sleep(150);
    xi(0);
    taihuatiflag=1;
    if(direction == 1)
      { 
 	     turn(60+35.25,2000,80); 
      }
 	  else if(direction == -1)
     { 
 	     turn(-60-34,2000,80); 
     }
     
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xistopopen();
    drivesb(42+50,2000,40);
    taihuatiflag=0;
    timersb3=0;
    //simplemove(-60);
    while(timersb3<=1050)
    {
      Lift1.spin(vex::directionType::fwd,-60, vex::velocityUnits::pct);

    }*/
    xi(0);
    /*Lift1.stop();
   //task::sleep(200);
   simplemove(-40);
   task::sleep(1000);
   simplemove(0);*/

}

void auton4(int direction)
{
    simplemove(80);
  
  task::sleep(300);
  
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=1800)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(42+20,2500,40);
    if(direction == 1)
 	    turn(-26.5,800,80); 
 	  else if(direction == -1)
      turn(25,800,80); 

Lift1.resetRotation();

    simplemove(-100);
    task::sleep(1800);
     simplemove(0);
    /*Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    while(Tanbianma.rotation(vex::rotationUnits::deg)<20.0);
    Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    task::sleep(200);
    Lift1.stop();*/
    drivesb(42+15,2700,40);
    xi(100);
    task::sleep(150);
    xi(0);
    taihuatiflag=1;
    if(direction == 1)
      { 
 	     turn(60+38.25,2000,80); 
      }
 	  else if(direction == -1)
     { 
 	     turn(-60-38,2000,80); 
     }
     
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xistopopen();
    drivesb(42+50,2000,40);
    taihuatiflag=0;
    timersb3=0;
    //simplemove(-60);
    while(timersb3<=1050)
    {
      Lift1.spin(vex::directionType::fwd,-60, vex::velocityUnits::pct);

    }
    xi(0);
    Lift1.stop();
   //task::sleep(200);
   simplemove(-40);
   task::sleep(1000);
   simplemove(0);

}

void auton55(int direction)
{
 /* timersb4=0;
   simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=1100)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();
simplemove(-100);
  
  
  
  //xi(-100);*/
  /*simplemove(80);
  
  task::sleep(300);*/
  
  simplemove(-80);
  xi(100);
  task::sleep(800);
  simplemove(0);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(45,1100,80);
    if(direction == 1)
 	    turn(-22.5,800,100);
 	  else if(direction == -1)
      turn(22.5,800,100);
    drivesb(45,2000,45);
    /*if(direction == 1)
 	    turn(-10,1200,100);
 	  else if(direction == -1)
      turn(10,1000,100);
    drivesb(18,2000,40);*/
    /*if(direction == 1)
 	    turn(10,1000,100);
 	  else if(direction == -1)
      turn(-10,1000,100);
    drivesb(21,2500,40);
    while(timersb3<=1500)
    {
      Lift1.spin(vex::directionType::fwd,-80, vex::velocityUnits::pct);
    }
     Lift1.stop(brakeType::hold);
    if(direction == 1)
 	    turn(-25,5000,100);
 	  else if(direction == -1)
      turn(25,5000,100);
     while(timersb3>=300)
    {
      Lift1.spin(vex::directionType::fwd,80, vex::velocityUnits::pct);
    }
    Lift1.stop(brakeType::hold);
    drivesb(30,2500,40);*/
    if(direction == 1)
 	    turn(-106,1750,80);
 	  else if(direction == -1)
      turn(106,1750,80);
      drivesb(37,970,70);/////////////////////////////////////////////
   /*drivesb(75,1300,80);
    drivesb(-10,900,80);
     if(direction == 1)
 	    turn(76.5,1500,100);
 	  else if(direction == -1)
      turn(-67,1400,100);*/
    if(direction == 1)
 	    turn(60,1500,100);
 	  else if(direction == -1)
      turn(-60,1500,100);
    drivesb(40,1300,80);///////////////////////////////////////////////////////////////////////
    Xis(100);
    task::sleep(48);
    Xis(0);
     taihuatiflag=1;
    if(direction == 1)
 	    turn(-24,1200,100);
 	  else if(direction == -1)
      turn(24,1200,100);
    taihuatiflag=1;
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xistopopen();
    drivesb(20,1300,20);
    //drivesb(-3,2500,40);
    //drivesb(18,1000,100);
    taihuatiflag=0;
    Xis(0);
    timersb3=0;
    //simplemove(-60);
    while(timersb3<=1200)
    {
      Lift1.spin(vex::directionType::fwd,-80, vex::velocityUnits::pct);

    }
   /* while(timersb3<=1100)
    {
      Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
      if(timersb3 % 800 <= 200)
      {
          Xis1.spin_s( directionType::fwd, 0 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, 0 , voltageUnits::volt );
      }
      else
      {
          Xis1.spin_s( directionType::fwd, -100 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, -100 , voltageUnits::volt );
      }
    }*/
    xi(0);
    Lift1.stop();
     simplemove(-70);
   task::sleep(1000);
   simplemove(0);

     
    Lift1.stop();
     Brain.Screen.printAt(10,160,"qqqq %lf%%",timersb4*1.0);
}

void auton555(int direction)
{
  timersb4=0;
   simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=1100)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=900)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>900&&timersb2<=950)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>950)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
Lift1.stop();
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(43,1400,80);
    if(direction == 1)
 	    turn(-22,1000,100);
 	  else if(direction == -1)
      turn(22,1000,100);
    drivesb(43,1900,40);
    /*if(direction == 1)
 	    turn(-10,1200,100);
 	  else if(direction == -1)
      turn(10,1000,100);
    drivesb(18,2000,40);*/
    /*if(direction == 1)
 	    turn(10,1000,100);
 	  else if(direction == -1)
      turn(-10,1000,100);
    drivesb(21,2500,40);
    while(timersb3<=1500)
    {
      Lift1.spin(vex::directionType::fwd,-80, vex::velocityUnits::pct);
    }
     Lift1.stop(brakeType::hold);
    if(direction == 1)
 	    turn(-25,5000,100);
 	  else if(direction == -1)
      turn(25,5000,100);
     while(timersb3>=300)
    {
      Lift1.spin(vex::directionType::fwd,80, vex::velocityUnits::pct);
    }
    Lift1.stop(brakeType::hold);
    drivesb(30,2500,40);*/
    if(direction == 1)
 	    turn(-104.5,3000,80);
 	  else if(direction == -1)
      turn(104.5,2100,100);
    drivesb(75,1500,80);
    drivesb(-15,1000,80);
     if(direction == 1)
 	    turn(76.5,1500,100);
 	  else if(direction == -1)
      turn(-82,2000,100);
    drivesb(38,2000,80);
    Xis(100);
    task::sleep(48);
    Xis(0);
     taihuatiflag=1;
    if(direction == 1)
 	    turn(-35,1200,100);
 	  else if(direction == -1)
      turn(34,1100,100);
    /*drivesb(18,1500,40);
    //drivesb(-3,2500,40);
    xistopopen();
    //drivesb(18,1000,100);
    taihuatiflag=0;
    Xis(0);
    timersb3=0;
    //simplemove(-60);
    while(timersb3<=1100)
    {
      Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
      if(timersb3 % 800 <= 200)
      {
          Xis1.spin_s( directionType::fwd, 0 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, 0 , voltageUnits::volt );
      }
      else
      {
          Xis1.spin_s( directionType::fwd, -100 , voltageUnits::volt );
          Xis2.spin_s( directionType::fwd, -100 , voltageUnits::volt );
      }
    }
    Lift1.stop();
    xi(0);
    //armlift(-100);
    task::sleep(600);
    drivesb(-23,1500,60);
     
    Lift1.stop();
     Brain.Screen.printAt(10,160,"qqqq %lf%%",timersb4*1.0);*/
}
void auton999(int direction)
{
   simplemove(100);
   task::sleep(300);
   simplemove(0);

   simpleturn(100);
   task::sleep(100);

   simplemove(100);
   task::sleep(100);

   simpleturn(100);
   task::sleep(100);

   simplemove(100);
   task::sleep(300);
   simplemove(0);
}
void auton99(int direction)
{
   simplemove(100);
   task::sleep(300);
   simplemove(0);

   xi(3);
   task::sleep(300);
   xistop();
   timersb2=0;
   while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0)
   {
   if (timersb2%1600<=800)
   {
     xi(100);
   }
    else
   {
    xi(0);
    }
  }
  Lift1.spin(vex::directionType::fwd, 100/3, vex::velocityUnits::pct);
  while(Tanbianma.rotation(vex::rotationUnits::deg)<=70.0)
  {
   if (timersb2%1600<=800)
   {
     xi(100);
   }
    else
   {
    xi(0);
    }
  }
  Lift1.stop(brakeType::hold);
  xi(0);
  simplemove(60);
   task::sleep(100);
}
void auton9(int direction)
{
simplemove(100);
  
  task::sleep(300);
  
  simplemove(-100);
  xi(100);
  //task::sleep(500);
  
  ////////////task::sleep(2000);
  timersb2=0;

while(timersb2<=2000)
{
  Brain.Screen.printAt(10,80,"timersb2=%lf%%",timersb2*1.0);
     

  if(timersb2>=200&&timersb2<=1500)
  {
  Lift1.spin(vex::directionType::fwd,-100, vex::velocityUnits::pct);
  }
  if(timersb2>1500&&timersb2<=1800)
  {
  Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  //Lift1.stop();
  }
  if(timersb2>1800)//&&timersb2<=1800)
  {
  //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
  Lift1.stop();
  }
}
simplemove(-100);
  
  
  
  //xi(-100);

    Xis(-100);
    Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
    drivesb(42*2+15,2000,70);
    if(direction == 1)
 	    turn(-18,1000,80); 
 	  else if(direction == -1)
      turn(19,1000,80); 

Lift1.resetRotation();

    simplemove(-100);
    task::sleep(2300);
     simplemove(0);
    /*Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    while(Tanbianma.rotation(vex::rotationUnits::deg)<20.0);
    Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    task::sleep(200);
    Lift1.stop();*/
    drivesb(42*2+20,2000,65);
    taihuatiflag=1;
    if(direction == 1)
      { 
 	     turn(60+46,1800,80); 
      }
 	  else if(direction == -1)
     { 
 	     turn(-60-46,1800,80); 
     }
     
    //Lift1.spin(vex::directionType::fwd,100, vex::velocityUnits::pct);
    //while(Tanbianma.rotation(vex::rotationUnits::deg)<=35.0);
    //Lift1.stop(brakeType::hold);
    xi(100);
    task::sleep(150);
    xi(0);
    xistopopen();
    drivesb(42+36,1800,70);
    taihuatiflag=0;
    timersb3=0;
    simplemove(-20);
    while(timersb3<=1000)
    {
      Lift1.spin(vex::directionType::fwd,1.0*0.5*(-4000-Lift1.rotation(rotationUnits::deg)), vex::velocityUnits::pct);
  
    }
    Lift1.stop();
   simplemove(0);
   // armlift(-60);
    //
    //task::sleep(500);
    //

   
}
void autonomous( void ) 
{
    zidong=1;
  //  auton1(1);
  //   auton11(1);
   // auton2(1);	
	//	auton2(-1);
 auton55(1);
  //auton3(-1);
    //v5cyka();
     /*if ((jumper1.pressing() == 0) && (jumper2.pressing() == 0))
			{
				auton2(1);
			}
			else if((jumper1.pressing() == 0) && (jumper2.pressing() == 1))
			{
				auton1(1);
       }
			else if((jumper1.pressing() == 1) && (jumper2.pressing() == 0))
			{
			   auton2(1);	
			}
			else if((jumper1.pressing() == 1) && (jumper2.pressing() == 1))
			{
			  auton2(-1);	
			}
		*/
      zidong=0;
		    
	  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
 int yinggaizaitipanzi,yinggaixiajiangle;
 int liftlockflag=0;
void usercontrol( void ) 
{
  double sss=0;

  flagta=0;
  
        
  Brain.Screen.printAt(10,10,"marker1");
      
  // User control code here, inside the loop
    Left1.resetRotation();
    Left2.resetRotation();
    Right1.resetRotation();
    Right2.resetRotation(); 
    Xi1.resetRotation();
    Xi2.resetRotation();
    Open2.resetRotation();
    Tanbianma.resetRotation();
  Brain.Screen.printAt(10,10,"marker2");
    liftlockflag=0;
    int count=1;
    zidong=0;


    //vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    
    //double sbsbsbsb=0;
    //double saddd;
   while(1)
   { 
     if(Controller1.ButtonY.pressing()==1)
     {
       Lift1.resetRotation();
        liftrot = Lift1.rotation(vex::rotationUnits::deg);
     }  

     if(Controller1.ButtonRight.pressing()==1)
     {
       liftlockflag=1;
     }

     tanbianmaduzhii =1.0* Left1.rotation(rotationUnits::deg);
     Brain.Screen.printAt(10,80,"liftbiana %lf%%",tanbianmaduzhii);
     //sss=1.0*Open2.rotation(vex::rotationUnits::deg);
     //Brain.Screen.printAt(10,10,"Tanbiana %lf%%",sss);
      
      ////di pan/////
       double move = (double)Controller1.Axis3.value() * 12.0 / 100;//144
       double turnsk = (double)Controller1.Axis1.value() * 12.0 / 100;//149
       //double drift = 0;//-(double)Controller1.Axis4.value() * 12.0 / 100;
      //////////////////xi///////////////////
        if(Controller1.ButtonR1.pressing()==1 && Controller1.ButtonR2.pressing()==1)
        {
            Xi1.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
            Xi2.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
            
             xirot1 = Xi1.rotation(vex::rotationUnits::deg);
             xirot2 = Xi2.rotation(vex::rotationUnits::deg);
         }
        
        if(Controller1.ButtonR1.pressing()==0 && Controller1.ButtonR2.pressing()==1)
        {
            Xi1.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
            Xi2.spin(vex::directionType::fwd, 80, vex::velocityUnits::pct);
            
             xirot1 = Xi1.rotation(vex::rotationUnits::deg);
             xirot2 = Xi2.rotation(vex::rotationUnits::deg);
         }
            
        
        if(Controller1.ButtonR1.pressing()==1 && Controller1.ButtonR2.pressing()==0)
        {
            Xi1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
            Xi2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
            xirot1 = Xi1.rotation(vex::rotationUnits::deg);
            xirot2 = Xi2.rotation(vex::rotationUnits::deg);
        }
      if(Controller1.ButtonR1.pressing()==0 && Controller1.ButtonR2.pressing()==0)
      {
         //Xi1.stop();
         //Xi2.stop();
        if(Controller1.ButtonL1.pressing()==0)
         {
          Xi1.spin(vex::directionType::fwd,0.08*(xirot1-Xi1.rotation(vex::rotationUnits::deg)),vex::velocityUnits::pct);
          Xi2.spin(vex::directionType::fwd,0.08*(xirot2-Xi2.rotation(vex::rotationUnits::deg)),vex::velocityUnits::pct);
         }
        else
         {
          Xi1.stop();
          Xi2.stop(); 
          xirot1 = Xi1.rotation(vex::rotationUnits::deg);
          xirot2 = Xi2.rotation(vex::rotationUnits::deg);
          }
        }
      /////////////////lift//////////////////
        if(Controller1.ButtonL1.pressing()==0 && Controller1.ButtonL2.pressing()==1)
        {
            Lift1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
                
            liftrot = Lift1.rotation(vex::rotationUnits::deg);
        }
        if(Controller1.ButtonL1.pressing()==1 && Controller1.ButtonL2.pressing()==0)
        {
            if(Controller1.ButtonA.pressing()==1)
                Lift1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
            else
                Lift1.spin(vex::directionType::fwd, -30, vex::velocityUnits::pct);
            
            liftrot = Lift1.rotation(vex::rotationUnits::deg);
        }
      if(Controller1.ButtonL1.pressing()==0 && Controller1.ButtonL2.pressing()==0&& flagta==0)
      {
          if(liftlockflag==0)
          {
            Lift1.stop();
            liftrot = Lift1.rotation(vex::rotationUnits::deg);
          }
          else
          {
            Lift1.spin(vex::directionType::fwd,0.08*(liftrot-Lift1.rotation(vex::rotationUnits::deg)),vex::velocityUnits::pct);
          }
      }
      ////////////////open//////////////////
        if(Controller1.ButtonUp.pressing()==1 && Controller1.ButtonDown.pressing()==0)
        {
            Open2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
            openrot = Open2.rotation(vex::rotationUnits::deg);
            //saddd=openrot;
        }
        if(Controller1.ButtonUp.pressing()==0 && Controller1.ButtonDown.pressing()==1)
        {
            Open2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
            openrot = Open2.rotation(vex::rotationUnits::deg);
            //saddd=openrot;
        }
      if(Controller1.ButtonUp.pressing()==0 && Controller1.ButtonDown.pressing()==0 && flagta==0)
      {
          //Open1.stop();
          if(Controller1.ButtonR1.pressing()==1&&Controller1.ButtonR2.pressing()==0)//openrot>=540)
          {
           //Open2.spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);
            Opens2.spin_s( directionType::fwd, -3 , voltageUnits::volt );
            openrot = Open2.rotation(vex::rotationUnits::deg);
          }
          else
          {
            if(Open2.rotation(vex::rotationUnits::deg)<=550)
            {
            Open2.stop();//spin(vex::directionType::fwd, -3, vex::velocityUnits::pct);   
            openrot = Open2.rotation(vex::rotationUnits::deg);
            }
            else
            {
              Open2.spin(vex::directionType::fwd,0.08*(openrot-Open2.rotation(vex::rotationUnits::deg)),vex::velocityUnits::pct);
            }
          
          }
      } 

      //////////////yijianfangta////////////
    // if(Controller1.ButtonX.pressing()==1)
   
    
      ////////run////////
      if ((Controller1.Axis4.value()>= 2 || Controller1.Axis4.value() <=-2) ||(Controller1.Axis3.value()>= 2 || Controller1.Axis3.value() <=-2) || (Controller1.Axis1.value()>= 2 || Controller1.Axis1.value()<=-2))
      {
          LeftRun1.spin_s( directionType::fwd, move + turnsk , voltageUnits::volt );
          LeftRun2.spin_s( directionType::fwd, move + turnsk , voltageUnits::volt );
          RightRun1.spin_s( directionType::fwd,- move + turnsk , voltageUnits::volt );
          RightRun2.spin_s( directionType::fwd,- move + turnsk , voltageUnits::volt );
          Brain.Screen.printAt(10,10,"marker11");
      }
      else
      {
          LeftRun1.stop();
          LeftRun2.stop();
          RightRun1.stop();
          RightRun2.stop();
          Brain.Screen.printAt(10,10,"marker12");
      }
      
      
      if(flagta==1)
    {
               Lift1.spin(vex::directionType::fwd,1.0*0.2*(-2000-Lift1.rotation(rotationUnits::deg)),vex::velocityUnits::pct);

          
          openrot = Open2.rotation(vex::rotationUnits::deg);
          liftrot = Lift1.rotation(vex::rotationUnits::deg);
          if(Lift1.rotation(rotationUnits::deg)<-700)
          {
            Open2.spin(vex::directionType::fwd,1.0*0.2*(1100-Open2.rotation(rotationUnits::deg)),vex::velocityUnits::pct);
          
          openrot = Open2.rotation(vex::rotationUnits::deg);
          liftrot = Lift1.rotation(vex::rotationUnits::deg);
          }

          if(Open2.rotation(rotationUnits::deg)>1050)
          {
            flagta=0;
            Lift1.stop();
            Open2.stop();
          }
          openrot = Open2.rotation(vex::rotationUnits::deg);
          liftrot = Lift1.rotation(vex::rotationUnits::deg);

   }

    
  }
  Brain.Screen.printAt(10,10,"marker3");
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(0);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}