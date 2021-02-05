#include "main.h"
#define inPerDeg 0.0372817639078584 //use baseOdom to tune?
#define powerToDegsPerMs 0.0104 //empirical use excel
#define powerToInPerMs (powerToDegsPerMs * inPerDeg)
#define voltageToPower 127/12000
#define MAXPOWV 100.0 //power
#define MAXPOWA .5 //.5 power every ms
#define MAXV MAXPOW*powerToInPerMs
#define MAXA MAXPOWA*powerToInPerMs
//INJECT
#define SPACING .5
//SMOOTH
#define TOLERANCE 0.0001
//MAXV
#define K 20
Path::Path(): wps{}
{}
Path::Path(std::vector<Node> p_wps): wps{p_wps}
{}
double Path::getMaxV(int i){
  return maxV[i];
}
Node Path::getSmoWp(int i){
  return smoWps[i];
}
int Path::getN(){
  return n;
}
void Path::inject(){
  injWps.clear();
  for(int i = 0;i<=wps.size()-2;++i){
    Node start = wps[i];
    Node end = wps[i+1];
    Node diff = end - start;
    Node step = diff.norm()*SPACING;
    int nFit = ceil(diff.mag()/SPACING);
    for(int j = 0;j<nFit;++j){
      injWps.push_back(start + step*j);
    }
  }
  injWps.push_back(wps[wps.size()-1]);
  n = injWps.size();
}
void Path::smooth(){
  smoWps = injWps;
  double change = TOLERANCE;
  while(change >= TOLERANCE){
    change = 0;
    for(int i = 1;i<n-1;++i){
      Node aux = smoWps[i];
      smoWps[i] = aux + (injWps[i] - smoWps[i])*w_data + (smoWps[i-1] + smoWps[i+1] - smoWps[i]*2)*w_smooth;

      Node diff = smoWps[i] - aux;
      change += (fabs(diff.getX()) + fabs(diff.getY()));
    }
    printf("change = %.5f\n", change);
  }
}
void Path::calcDist(){
  Node prevWp = smoWps[0];
  double prevDist = 0;
  for(auto smoWp : smoWps){
    double deltaDist = distance(smoWp, prevWp);
    double newDist = prevDist + deltaDist;
    dist.push_back(newDist);
    prevDist = newDist;
    prevWp = smoWp;
  }
  // printVector(dist);
}
void Path::calcCurvature(){
  curv.push_back(INFsmall); //starting point
  for (int i = 1;i<=n-2;++i){
    double r = circumRad(smoWps[i-1], smoWps[i], smoWps[i+1]);
    curv.push_back(1/r);
  }
  printVector(curv);
  curv.push_back(INFsmall); //final point
}
void Path::calcMaxV(){
  for(int i = 0;i<n;++i){
    maxV.push_back(std::min(MAXPOWV, K/curv[i])*powerToInPerMs);
  }
  // printVector(maxV);
}
void Path::calcTargV(){
  targV.clear();
  targV.resize(n, 0);
  targV[n-1] = 0;
  for(int i = n-2;i>=0;--i){
    double d = distance(smoWps[i+1], smoWps[i]);
    targV[i] = std::min(maxV[i], sqrt(targV[i+1]*targV[i+1] + 2 * MAXA * d));
  }
}
void Path::setWps(std::vector<Node> p_wps, double p_w_data, double p_w_smooth){
  //perform injection and smooth
  wps = p_wps;
  w_data = p_w_data;
  w_smooth = p_w_smooth;
  this->inject();
  this->smooth();
  this->calcDist();
  this->calcCurvature();
  this->calcMaxV();
  this->calcTargV();
}
