#pragma once
#include <math.h>
#include "globaldefs.h"

#define dist(p1, p2) sqrtf((p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y))

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
	float get_result_and_update();
	bool is_settled();

	void settle();
	void set_target(float);
};

class lateral_controller {
public:
	pose target;
	pose pos;
	pid_controller pidc;
	lateral_controller(float P, float I, float D, pose T, pose start, unsigned int threshold_c) : target(T), pos(start), pidc(pid_controller(P, I, D, 0.0f, dist(target, pos), threshold_c)){}

	float get_result_and_update();
	bool is_settled();

	void settle();
	void set_target(pose);
};