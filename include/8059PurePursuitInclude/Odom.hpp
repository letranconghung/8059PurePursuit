#ifndef _8059_PP_ODOM_HPP_
#define _8059_PP_ODOM_HPP_
#include <algorithm>
#include "Node.hpp"
/** Essential variables for odometry task and functions */
/** Tuning: turn at least 2 rotations and compare results in program & real life */
#define baseWidth 16.18003749869522
/** Tuning: go straight and compare results in program & real life */
#define inPerDeg 0.0372817639078584
/** makes position a universally accessible object */
extern double encdL, encdR, bearing, angle;
extern Node position;
/** refer to baseOdometry.cpp for function documentation */
void Sensors(void * ignore);
void Odometry(void * ignore);

#endif
