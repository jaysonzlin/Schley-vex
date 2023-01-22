#ifndef _OPCONTROL_H_
#define _OPCONTROL_H_

extern pros::Controller controller;

extern pros::Motor FL;
extern pros::Motor FR;
extern pros::Motor BL;
extern pros::Motor BR;

extern pros::Motor I1;
extern pros::Motor I2;
extern pros::Motor S1;
extern pros::Motor S2;

extern pros::ADIAnalogIn CATA;
extern pros::Motor T;

void drive(int left, int right);
void brake(bool coast); 
int sign(int x);
void opDrive(void);

void shoot(void);
void intake(void);

void roller(void);
void cataLoad(void);
void launch(void);

#endif