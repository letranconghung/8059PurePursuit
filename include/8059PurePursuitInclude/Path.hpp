#ifndef _8059_PP_PATH_HPP_
#define _8059_PP_PATH_HPP_
#include "Node.hpp"
#include <vector>
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
class Path{
private:
  std::vector<Node> wps;
  std::vector<Node> injWps;

  std::vector<Node> smoWps;
  double w_data, w_smooth, lookAhead;
  int n;

  std::vector<double> dist;
  std::vector<double> curv;
  std::vector<double> maxV;
  std::vector<double> targV;

public:
  Path();
  Path(std::vector<Node> p_wps);
  Node getSmoWp(int i);
  double getMaxV(int i);
  double getTargV(int i);
  int getN();
  double getLookAhead();
  void inject();
  void smooth();
  void calcDist();
  void calcCurvature();
  void calcMaxV();
  void calcTargV();
  void setWps(std::vector<Node> p_wps, double p_w_data, double p_w_smooth, double p_lookAhead);
};
#endif
