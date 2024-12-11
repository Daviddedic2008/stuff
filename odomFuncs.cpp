#include "odomFuncs.h"
#define HORIZONTAL 0
#define VERTICAL 1

odom_controller::odom_controller(deadwheel* d1, deadwheel* d2) {
	deadwheels[0] = d1;
	deadwheels[1] = d2;
}

void odom_controller::zero_position() {
	position_heading.x = 0.0f; position_heading.y = 0.0f;
}

void odom_controller::upd_heading(float nh) {
	delta_theta = position_heading.heading - nh;
	position_heading.heading = nh;
}

void odom_controller::upd_deadwheel_horizontal(float angle_traversed_rad) {
	deadwheels[HORIZONTAL]->x += angle_traversed_rad;
	deadwheels[HORIZONTAL]->dx = angle_traversed_rad;
}

void odom_controller::upd_deadwheel_vertical(float angle_traversed_rad) {
	deadwheels[VERTICAL]->x += angle_traversed_rad;
	deadwheels[VERTICAL]->dx = angle_traversed_rad;
}

void odom_controller::upd_pose() {
	position_heading.x = deadwheels[HORIZONTAL]->dx * deadwheels[HORIZONTAL]->radius - delta_theta * deadwheels[HORIZONTAL]->dist_from_axis;
	position_heading.y = deadwheels[VERTICAL]->dx * deadwheels[HORIZONTAL]->radius - delta_theta * deadwheels[VERTICAL]->dist_from_axis;
}

void odom_controller::upd_cycle(float deadwheel_x[2], float new_heading) {
	upd_deadwheel_horizontal(deadwheel_x[HORIZONTAL] - deadwheels[HORIZONTAL]->x); upd_deadwheel_vertical(deadwheel_x[VERTICAL] - deadwheels[VERTICAL]->x);
	upd_heading(new_heading);
	upd_pose();
}

deadwheel* init_deadwheel(float radius, float dist) {
	// type: "horizontal" or "vertical"
	deadwheel* ret = new deadwheel;
	ret->radius = radius;
	ret->dist_from_axis = dist;
	ret->x = 0.0f;
	return ret;
}

void odom_controller::add_deadwheel(float dist, float radius, char* tag) {
	deadwheels[strcmp(tag, "vertical")] = init_deadwheel(radius, dist);
}
