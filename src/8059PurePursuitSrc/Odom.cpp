#include "main.h"
/** to test odometry in opcontrol() when not in competition */
#define COMPETITION_MODE false
/** Update the robot's position using side encoders values. */
void Odometry(void * ignore){
  /** D loop variables */
  double prevEncdL = 0, prevEncdR = 0;
  int count = 0;
  while(!COMPETITION_MODE || competition::is_autonomous()){
    double encdChangeL = encdL-prevEncdL;
    double encdChangeR = encdR-prevEncdR;
    double distance = (encdChangeL + encdChangeR)/2*inPerDeg;
    position = position + Node(distance * cos(angle), distance * sin(angle));
    /** update prev variables */
		prevEncdL = encdL;
		prevEncdR = encdR;
    /** debugging */
    if(!COMPETITION_MODE) posPrintMaster();
    if((DEBUG_MODE == 1) && (count++ % 100 == 0)) posPrintTerminal();
    if(DEBUG_MODE == 4) encdPrintTerminal();
    /** refresh rate of Task */
    Task::delay(5);
  }
}
