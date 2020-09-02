#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision__BLUE_BALL = signature (1, -3699, -2435, -3066, 9191, 14799, 11994, 2.5, 0);
signature Vision__RED_BALL = signature (2, -1, 6049, 3024, -495, 567, 36, 0.9, 0);
vision Vision = vision (PORT8, 50, Vision__BLUE_BALL, Vision__RED_BALL);
/*vex-vision-config:end*/
motor RightMotor = motor(PORT13, ratio18_1, true);
motor LeftMotor = motor(PORT18, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}