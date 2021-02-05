/** Robot's setup variables: Motor and sensor ports */
#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_
/** base motor ports */
#define FLPort 12
#define FRPort 19
#define BLPort 11
#define BRPort 20
/** other mechanical motor ports */
#define lRollerPort 13
#define rRollerPort 18
#define shooterPort 15
#define indexerPort 16
/** sensor ports */
#define encdL_port 1
#define encdR_port 4
#define intakeColorPort 6
#define shootColorPort 7
#define imuPort 14
#define visBallport 2
#define visFlagport 3
extern bool useVision;
#endif
