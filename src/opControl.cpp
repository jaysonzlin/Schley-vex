#include "main.h"

using namespace pros;

//Controller
Controller controller(E_CONTROLLER_MASTER);

//Motors
// Motor FL(20, true);
// Motor BL(10, true);
// Motor FR(11);
// Motor BR(1);

Motor FL(10);
Motor BL(1);
Motor FR(20, true);
Motor BR(11, true);

Motor I1(3);
//Motor I2(10, true);
Motor S1(8, true);
// Motor S2(8);

// ADIAnalogIn CATA (1);
// Motor T(16);

void drive(int left, int right){

    FL = left;
    BL = left;
    FR = right;
    BR = right;

}

void brake(bool coast){

    if (coast){
        FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
        FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BR.set_brake_mode(E_MOTOR_BRAKE_COAST);
    }
    else{
        FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }

    FL.brake();
    FR.brake();
    BL.brake();
    BR.brake();

}

int sign(int x){
  if (x > 0.0) return 1;
  if (x < 0.0) return -1;
  return 0;
}

void opDrive(){

    int leftJoystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

    //Linear scaling when out of deadzone
    int y;
    int x;
    int threshold = 19;
    int slope = 127/(127 - threshold);

    if (abs(leftJoystick) > threshold){
        y = slope * (leftJoystick - threshold * sign(y));
    }
    else{
        y = 0;
    }

    if (abs(rightJoystick) > threshold){
        x = slope * (rightJoystick - threshold * sign(y));
    }
    else{
        x = 0;
    }

    FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
    FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
    BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
    BR.set_brake_mode(E_MOTOR_BRAKE_COAST);

    int left = y + x * 0.5;
    int right = y - x * 0.5;
    
    drive(left, right);

}

bool toggle = false;

// void shoot(){

//     FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     BR.set_brake_mode(E_MOTOR_BRAKE_COAST);

//     if (controller.get_digital(E_CONTROLLER_DIGITAL_A)){

//         toggle = true;
        
//     }

//     if (controller.get_digital(E_CONTROLLER_DIGITAL_B)){

//         toggle = false;
//     }

//     if (toggle){

//         S1 = 127;
//         S2 = 127;

//     }
//     else{

//         S1 = 0;
//         S2 = 0;
//     }
// }

void intake(){

    if (controller.get_digital(E_CONTROLLER_DIGITAL_R1)){

        I1 = 120;
    }

    else if (controller.get_digital(E_CONTROLLER_DIGITAL_R2)){

        I1 = -120;

    }

    else{

        I1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        I1.brake();
    }
}

void launch(){

    if (controller.get_digital(E_CONTROLLER_DIGITAL_L2)){

        S1.move_velocity(100);
    }

    else{

        S1.set_brake_mode(E_MOTOR_BRAKE_COAST);
        S1.brake();
    }
}

// void cataLoad(){

//     while(1){
//         //Values for line encoder range from 0-4000, regular light in my room was 2800.
//         if (CATA.get_value() > 2000){
//             T.move_velocity(30);
//         }

//         else{
//             T.brake();
//         }
//         delay(10);

//     }



// void opDrive(){

//     int leftJoystick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
//     int rightJoystick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
//     int strafe = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

//     //Linear scaling when out of deadzone
//     int y;
//     int x;
//     int z;
//     int threshold = 19;
//     int slope = 127/(127 - threshold);

//     if (abs(leftJoystick) > threshold){
//         y = slope * (leftJoystick - threshold * sign(y));
//     }
//     else{
//         y = 0;
//     }

//     if (abs(rightJoystick) > threshold){
//         x = slope * (rightJoystick - threshold * sign(y));
//     }
//     else{
//         x = 0;
//     }

//     if (abs(strafe) > threshold){
//         z = slope * (strafe - threshold * sign(z));
//     }
//     else{
//         z = 0;
//     }

//     FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
//     BR.set_brake_mode(E_MOTOR_BRAKE_COAST);

//     int left = y + x * 0.5;
//     int right = y - x * 0.5;
    
//     FL = left + z;
//     FR = right - z;
//     BL = left - z;
//     BR = right + z;

// }