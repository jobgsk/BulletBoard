#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

#include "Vector3.h"
#include "Matrix4.h"


namespace tanks {

	float grad_to_rad(float grad);

	float rad_to_grad(float rad);
	/*
	angle between of objects
	*/
	float get_angle_between(
		Vector3<float> current_position, Vector3<float> current_direction, Vector3<float> next_position);
	/*
	get perpendicular vector towards current
	*/
	Vector3<float> get_orthogonal(Vector3<float> direction);
	/*
	get angle by direction vector around Y
	*/
	float direction_to_angle(Vector3<float> direction);

	Vector3<float> euler_angle_to_direction(float angle, float magnitude);
	/*
	get angle by matrix
	*/
	Vector3<float> matrix_angle_to_direction(Vector3<float> angle);

};
#endif // MATH_HELPER_H
