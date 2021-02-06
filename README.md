# 8059 Base Control Library with Pure Pursuit

*credits*: https://www.chiefdelphi.com/uploads/default/original/3X/b/e/be0e06de00e07db66f97686505c3f4dde2e332dc.pdf

## File structure:
Library files:
- ```/include/8059PurePursuitInclude```
- ```/src/8059PurePursuitSrc```

Supporting files:
- `autonSets.cpp` & `autonSets.hpp`
- `mechLib.cpp` & `mechLib.hpp`
- `globals.hpp`

## Library files:
#### Handle input:
- **Sensors**: handle input data from encoders, inertial and motor voltage
  - **Encoders** --> `encdL, encdR`
  - **Inertial** --> `bearing` --> `angle`
  - **Motor Voltage** --> `measuredVL, measuredVR`


#### Odometry:
- **Odom**: uses trigonometry to track the robot's absolute `position` (relative to field) over time

#### Pure Pursuit:
- **Node**: basic `Node` class of a 2D point
- **Path**: `Path` class:
  1. Point **injection**
  2. Path **smoothing**
  3. Calculate **distance** between smoothed pathpoints
  4. Calculate **curvature** of every smoothed pathpoint
  5. Calculate theoretical **maximum velocity** of every smoothed pathpoint
  6. Calculate **target velocity** of every smoothed pathpoint, with capped deceleration (*backward capping*) (i.e. capped acceleration from the last point)
    - Still *subjected to forward capping* to be implemented during motor control
    - Forms the *later half of trapezoidal velocity control*
- **Control**: use information from `path` to control base motors, using both feedforward and feedback

#### Support:
- **Math**: handle mathematical calculations
- **Debug**: print functions for debugging
- **api**: api file
