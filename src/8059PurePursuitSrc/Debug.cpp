#include "main.h"
void printVector(std::vector<double> vd){
  for(auto m : vd){
    printf("%.2f ", m);
  }
  printf("\n");
}
void posPrintTerminal(){
  printf("X: %.2f Y: %.2f bearing: %.2f\n", position.getX(), position.getY(), bearing);
}
void posPrintMaster(){
  Controller master(E_CONTROLLER_MASTER);
  master.print(2, 0, "%.2f %.2f %.2f", position.getX(), position.getY(), bearing);
}
void encdPrintTerminal(){
  printf("EncdL: %4.1f \t EncdR: %4.1f\n", encdL, encdR);
}
