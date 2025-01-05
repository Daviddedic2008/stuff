#include "chassis.h"
#include "globaldefs.h"
#include "pidController.h"
#include "odomFuncs.h"

struct chassis_voltage {
	float right, left;

	chassis_voltage() : right(0.0f), left(0.0f){}

	chassis_voltage(float r, float l) : right(r), left(l){}

	inline chassis_voltage operator+(const chassis_voltage& v) {
		return chassis_voltage(right + v.right, left + v.left);
	}

	inline chassis_voltage operator-(const chassis_voltage& v) {
		return chassis_voltage(right - v.right, left - v.left);
	}

	inline chassis_voltage operator*(const float f) {
		return chassis_voltage(right * f, left * f);
	}
};

struct chassis {
	pose p; // current pos
	float wheelDiameter, driveWidth, driveLength;
	unsigned int rpm;
	pid_controller angular;
	lateral_controller lateral;
	pose target;
	odom_controller odom;

	float angularScale; // angular change is multiplied by float to accentuate turns

	inline void set_pose(float x, float y, float h) {
		p.x = x;
		p.y = y;
		p.heading = h;
	}

	inline void set_target(pose t) {
		target = t;
	}

	inline void move(const float r, const float l) {
		// pros implementation here
	}

	inline void update_pose() {
		float deadwheel_pos[2]; // use pros to fill w deadwheel pos
		float heading; // use pros to fill w heading

		odom.upd_cycle(deadwheel_pos, heading);
		p = odom.position_heading;
	}

	inline void update() {
		update_pose();
		angular.val = p.heading;
		lateral.pos = p;
		const float angular_result = angular.get_result_and_update() * angularScale;
		const float lateral_result = lateral.get_result_and_update();
		move(lateral_result + angular_result, lateral_result - angular_result);
	}
};