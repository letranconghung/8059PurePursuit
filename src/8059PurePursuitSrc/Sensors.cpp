#include "main.h"
/** global variables */
Node position;
double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;
double measuredV = 0, measuredVL = 0, measuredVR = 0;
// angle = mathematical angle, taken from x-axis, counter clockwise as positive
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
    measuredVL = (FL.get_voltage() + BL.get_voltage())/2*voltageToPower*powerToInPerMs;
    measuredVR = (FR.get_voltage() + BR.get_voltage())/2*voltageToPower*powerToInPerMs;
    measuredV = (measuredVL + measuredVR)/2;
    delay(dT);
  }
}
