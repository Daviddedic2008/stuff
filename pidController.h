#pragma once
class pid_controller {
public:
	float kp, ki, kd;
	float target;
	float val;
	float prev_error;
	float error;
	float cumulative_err;
	float threshold_val;
	unsigned int threshold_cycles;
	unsigned int cycles;

	pid_controller(float P, float I, float D, float T, float startVal, unsigned int threshold_c);
	float get_result();
	bool is_settled();
};