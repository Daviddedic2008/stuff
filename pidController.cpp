#include "pidController.h"

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

float pid_controller::get_result() {
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