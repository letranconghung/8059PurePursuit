#include "main.h"
#define kV 0.95
#define kA 0
#define kP 0
Path path;
void drive(double l, double r){
  Motor FL (FLPort);
  Motor BL (BLPort);
  Motor FR (FRPort);
  Motor BR (BRPort);
  FL.move(l);
  BL.move(l);
  FR.move(r);
  BR.move(r);
}
void basePP(std::vector<Node> wps, double p_w_data, double p_w_smooth, double p_lookAhead){
  path.setWps(wps, p_w_data, p_w_smooth, p_lookAhead);
}
void waitPP(double cutoff){
  int start = millis();
  Node target = path.getSmoWp(path.getN()-1);
  while(distance(position, target)>=LEEWAY && millis() - start < cutoff) delay(5);
}
void PPControl(void * ignore){
  int closestPointIndex = 0;
  double lastFracIndex = 0;
  Node lookAheadNode;

  // unit: in/ms
  double targV = 0, targVL = 0, targVR = 0;
  double prevTargVL = 0, prevTargVR = 0;
  // unit: in/ms^2
  double targAL = 0, targAR = 0;
  while(true){
    //FIND CLOSEST POINT
    double minDist = INF;
    for(int i = closestPointIndex;i<path.getN();++i){
      double d = distance(position, path.getSmoWp(i));
      if(d < minDist){
        minDist = d;
        closestPointIndex = i;
      }
    }
    printf("closest point: ");
    path.getSmoWp(closestPointIndex).print();

    // ===================================================================================

    // FIND LOOK AHEAD POINT
    for(int i = floor(lastFracIndex);i<=path.getN()-2;++i){ // starting from int i = 0 is technically less efficient
      // iterate every path
      Node start = path.getSmoWp(i);
      Node end = path.getSmoWp(i+1);
      std::vector<double> l = position.findLookAhead(start, end, path.getLookAhead());
      if(l[0]){
        // if there's an intersection
        // calculate fractional index
        double fracIndex = i + l[1];
        if(fracIndex >= lastFracIndex){
          lookAheadNode = start + (end - start) * l[1];
          lastFracIndex = fracIndex;
          break;
        }
      } // else keep the same lookaheadnode
    }
    printf("look ahead point:");
    lookAheadNode.print();

    // ===================================================================================

    // calculate moveCurvature
    // under "Curvature of Arc" header
    // calculate angle from x-axis, counter clockwise as positive
    double a = -tan(angle);
    double b = 1;
    double c = tan(angle)*position.getX() - position.getY();
    double xabs = fabs(a * lookAheadNode.getX() + b * lookAheadNode.getY() + c)/sqrt(a*a + b*b);
    double crossProduct = sin(angle)*(lookAheadNode.getX() - position.getX()) - cos(angle)*(lookAheadNode.getY() - position.getY());
    double sign = crossProduct >= 0 ? 1 : -1;
    double moveCurvature = sign*2*xabs/(path.getLookAhead()*path.getLookAhead());

    // ===================================================================================

    // find target velocities
    /**
     * point (2): To get the target velocity take the target velocity associated with the closest point, and
     * constantly feed this value through the rate limiter to get the acceleration-limited target velocity.
     */
    double targVClosest = path.getTargV(closestPointIndex);
    // rate limiter
    targV = targV + abscap(targVClosest, MAXA); //might use v + abscap instead of targV + abscap?

    targVL = targV*(2 + moveCurvature*baseWidth)/2;
    targVR = targV*(2 - moveCurvature*baseWidth)/2;

    // ===================================================================================

    // motor controller
    targAL = (targVL - prevTargVL)/dT;
    targAR = (targVR - prevTargVR)/dT;
    // feedforward terms
    double ffL = kV * targVL + kA * targAL;
    double ffR = kV * targVR + kA * targAR;
    // feedback terms
    double fbL = kP * (targVL - measuredVL);
    double fbR = kP * (targVR - measuredVR);
    // set power
    drive((ffL + fbL)/powerToInPerMs, (ffR + fbR)/powerToInPerMs);
    // handling prev
    prevTargVL = targVL;
    prevTargVR = targVR;
    // debugging
    printf("%4.2f %4.2f\n", targV, measuredV);
    delay(dT);
  }
}
