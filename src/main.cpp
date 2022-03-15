#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Motor LEFT (10);
pros::Motor RIGHT (1, true);
pros::Motor CLAW (20, true);
pros::Motor ARM (5, true);

void initialize() {
	LEFT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	RIGHT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	CLAW.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ARM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
while(true){



	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
	int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

	int left = power + turn;
	int right = power - turn;

	LEFT.move(left);
	RIGHT.move(right);

	int armInput = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	ARM.move(0.5*armInput);

	bool clawOpen = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	bool clawClose = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	if(clawOpen) CLAW.move_velocity(50);
	else if(clawClose) CLAW.move_velocity(-50);
	else CLAW.move(0);

	pros::delay(20);
}
}
