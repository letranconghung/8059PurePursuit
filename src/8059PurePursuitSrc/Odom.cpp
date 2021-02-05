#include "main.h"
/** to test odometry in opcontrol() when not in competition */
#define COMPETITION_MODE false
/** global variables */
Node position;
double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;
// angle = mathematical angle, taken from x-axis, counter clockwise as positive
void printTerminal(){
  printf("X: %.2f Y: %.2f bearing: %.2f\n", position.getX(), position.getY(), bearing);
}
void printMaster(){
  Controller master(E_CONTROLLER_MASTER);
  master.print(2, 0, "%.2f %.2f %.2f", position.getX(), position.getY(), bearing);
}
void Sensors(void * ignore){
  // port data from all sensors
  Motor FL (FLPort);
  Motor BL (BLPort);
  Motor FR (FRPort);
  Motor BR (BRPort);
  Imu imu(imuPort);
  bool calibrated = false;
  int start = millis();
  while(true){
    encdL = BL.get_position();
    encdR = BR.get_position();
    bearing = imu.is_calibrating()? 0 : imu.get_rotation();
    angle = boundRad(halfPI - bearing);
    delay(5);
  }
}
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
    if(!COMPETITION_MODE) printMaster();
    if((DEBUG_MODE == 1) && (count++ % 100 == 0)){
      printTerminal();
    }
    if(DEBUG_MODE == 4) printf("Encoder values %4.0f \t %4.0f\n",encdL, encdR);
    /** refresh rate of Task */
    Task::delay(5);
  }
}
