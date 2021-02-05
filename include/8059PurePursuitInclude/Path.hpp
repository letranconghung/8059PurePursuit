#ifndef _8059_PP_PATH_HPP_
#define _8059_PP_PATH_HPP_
#include "Node.hpp"
#include <vector>
class Path{
private:
  std::vector<Node> wps;
  std::vector<Node> injWps;

  std::vector<Node> smoWps;
  double w_data, w_smooth;
  int n;

  std::vector<double> dist;
  std::vector<double> curv;
  std::vector<double> maxV;
  std::vector<double> targV;

public:
  Path();
  Path(std::vector<Node> p_wps);
  double getMaxV(int i);
  Node getSmoWp(int i);
  int getN();
  void inject();
  void smooth();
  void calcDist();
  void calcCurvature();
  void calcMaxV();
  void calcTargV();
  void setWps(std::vector<Node> p_wps, double p_w_data, double p_w_smooth);
};
#endif
