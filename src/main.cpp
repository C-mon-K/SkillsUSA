#include "main.h"

//Define master controller
pros::Controller master (pros::E_CONTROLLER_MASTER);

//Define motor objects
pros::Motor LEFT (10);
pros::Motor RIGHT (1, true);
pros::Motor CLAW (20, true);
pros::Motor ARM (5, true);

/**
 * @brief function is called once when code is first loaded
 * 
 */
void initialize() {
	//set drive modes
	LEFT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	RIGHT.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	CLAW.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	ARM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}


/**
 * @brief is called once when driver control is started
 * 
 */
void opcontrol() {
	while(true){

		/**
		 * DRIVE
		 * 
		 * arcade drive - left analog stick
		 * 
		 */
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X); //controller input by left analog stick
		int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

		int left = power + turn; //basic arcade control calculations
		int right = power - turn;

		LEFT.move(left); //assigns motor voltages
		RIGHT.move(right);


		/**
		 * ARM
		 * 
		 * arm up - right analog stick up (hold)
		 * arm down - right analog stick down (hold)
		 * 
		 */
		int armInput = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y); //controller input by right analog stick
		ARM.move(0.5*armInput); //assigns motor voltage (slowed down by 0.5)


		/**
		 * CLAW
		 * 
		 * open claw - R1 (hold)
		 * close claw - R2 (hold)
		 * 
		 */
		bool clawOpen = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1); //controller input; R1 and R2
		bool clawClose = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

		if(clawOpen && clawClose) CLAW.move(0);				//do nothing, if both buttons are pressed 
		else if(clawOpen) CLAW.move(80);			//open at 50% speed, if R1 is pressed
		else if(clawClose) CLAW.move(-80);			//close at 50% speed, if R2 is pressed
		else CLAW.move(0);									//do nothing, if neither button is pressed

		pros::delay(20); //20ms delay to prevent the v5 brain from overloading
	}
}