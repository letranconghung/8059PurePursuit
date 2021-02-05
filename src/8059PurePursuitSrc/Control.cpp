#include "main.h"
#define LEEWAY 3

Path path;
// void basePP(std::vector<Node> wps){
//   path.setWps
// }
void waitPP(){
  Node target = path.getSmoWp(path.getN()-1);
  while(distance(position, target)>=LEEWAY) delay(5);
}
void PPControl(void * ignore){
  while(true){
    delay(5);
  }
}
