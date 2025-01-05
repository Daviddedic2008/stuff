#include "pidController.h"

// general pid
pid_controller::pid_controller(float P, float I, float D, float T, float startVal, unsigned int threshold_c) {
	kp = P;
	ki = I;
	kd = D;
	target = T;
	val = startVal;
	prev_error = 0.0f;
	cumulative_err = 0.0f;
	error = 0.0f;
	threshold_cycles = threshold_c;
}

float pid_controller::get_result_and_update() {
	error = target - val;
	cumulative_err += error;
	float d = error - prev_error;
	prev_error = error;
	if (error < threshold_val) {
		++cycles;
	}
	return (error * kp + cumulative_err * ki + d * kd);
}

bool pid_controller::is_settled() {
	if (cycles >= threshold_cycles) {
		return true;
	}
	return false;
}

void pid_controller::settle() {
	error = 0;
	cumulative_err = 0;
	prev_error = 0;
	val = target;
}

void pid_controller::set_target(float t) {
	target = t;
}

float lateral_controller::get_result_and_update() {
	pidc.val = dist(pos, target);
	pidc.val *= 
	pidc.error = pidc.target - pidc.val;
	pidc.cumulative_err += pidc.error;
	float d = pidc.error - pidc.prev_error;
	pidc.prev_error = pidc.error;
	if (pidc.error < pidc.threshold_val) {
		++pidc.cycles;
	}
	return (pidc.error * pidc.kp + pidc.cumulative_err * pidc.ki + d * pidc.kd);
}

bool lateral_controller::is_settled() {
	if (pidc.cycles >= pidc.threshold_cycles) {
		return true;
	}
	return false;
}

void lateral_controller::settle() {
	pidc.error = 0;
	pidc.cumulative_err = 0;
	pidc.prev_error = 0;
	pidc.val = pidc.target;
	pos = target;
}

void lateral_controller::set_target(pose t) {
	target = t;
}

