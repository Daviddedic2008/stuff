#pragma once
#include <cstring>

typedef struct {
	float radius;
	float dist_from_axis;
	bool horizontal, vertical;
	float dx, x;
}deadwheel;

typedef struct {
	float x, y, heading;
}pose;

deadwheel* init_deadwheel(float radius, float dist);

class odom_controller {
	public:

		odom_controller(deadwheel* d1, deadwheel* d2);

		void add_deadwheel(float dist, float radius, char* tag);

		deadwheel* deadwheels[2];

		float delta_theta;
		pose position_heading;

		void zero_position();

		void upd_heading(float nh);
		void upd_deadwheel_horizontal(float angle_traversed_rad);
		void upd_deadwheel_vertical(float angle_traversed_rad);
		void upd_pose();
		void upd_cycle(float deadwheel_dx[2], float new_heading);
};