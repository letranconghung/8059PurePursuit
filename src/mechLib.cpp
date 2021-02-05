/** Other mechanical functions. */
#include "main.h"
/** declare motors and sensors */
/** thresholds */
int iMax = 127;
int rMax = 127;
int intakeColorValue = 0, shootColorValue = 0;
int intakeColorThreshold = 2800;
int shootColorThreshold = 2400;
void setMech(int l, int r, int i, int s){
  Motor lRoller (lRollerPort);
  Motor rRoller (rRollerPort);
  Motor shooter (shooterPort);
  Motor indexer (indexerPort);
  lRoller.move(l);
  rRoller.move(r);
  indexer.move(i);
  shooter.move(s);
}
void resetMech(){
  setMech(0, 0, 0, 0);
}
void setMech(int l, int r, int i, int s, int t){
  setMech(l, r, i, s);
  delay(t);
  resetMech();
}
void waitIntakeColor(){
  printf("wait intake color \t value: %d\n", shootColorValue);
  while(intakeColorValue>intakeColorThreshold) delay(5);
}
void waitShootColor(){
  printf("wait Shoot color \t value: %d\n", shootColorValue);
  while(shootColorValue>shootColorThreshold){
    delay(5);
  }
}
void autoFrontIntake(){
  setMech(rMax, rMax, iMax, 0);
  waitIntakeColor();
  resetMech();
}
void autoBackIntake(){
  setMech(0, 0, iMax, 0);
  waitIntakeColor();
  resetMech();
}
/** can be used for backIntakeLoad */
void autoLoad(){
  printf("auto load\n");
  setMech(0, 0, iMax, 0);
  waitShootColor();
  resetMech();
}
/** not recommended as it will accidentally intake other balls while loading (?) */
void autoFrontIntakeLoad(){
  setMech(rMax, rMax, iMax, 0);
  waitShootColor();
  resetMech();
}
void shoot(int s, int t){
  setMech(0, 0, iMax, s);
  delay(t);
  resetMech();
}
void shoot(int s){
  setMech(0, 0, iMax, s);
}

void mechControl(void * ignore){
  Motor lRoller (lRollerPort);
  Motor rRoller (rRollerPort);
  Motor shooter (shooterPort);
  Motor indexer (indexerPort);
  ADIAnalogIn intakeColor(intakeColorPort);
  ADIAnalogIn shootColor(shootColorPort);
  while(true){
    intakeColorValue = intakeColor.get_value();
    shootColorValue = shootColor.get_value();
    delay(5);
  }
}
