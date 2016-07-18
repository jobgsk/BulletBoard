#include "math_helper.h"

float tanks::grad_to_rad(float grad)
{
	return (grad * 3.14) / 180;
};

float tanks::rad_to_grad(float rad)
{
	return rad * 180.0 / 3.14;
}

float tanks::get_angle_between(
	Vector3<float> current_position, Vector3<float> current_direction, Vector3<float> next_position)
{
	// vertex from object to player
	float vpx = next_position.x - current_position.x;
	float vpy = next_position.y - current_position.y;
	float vpz = next_position.z - current_position.z;

	float rad_angle_betwen = acos(
		(current_direction.x * vpx + current_direction.y * vpy + current_direction.z * vpz)
		/
		(
		sqrt(pow(current_direction.x, 2) + pow(current_direction.y, 2) + pow(current_direction.z, 2)) *
		sqrt(pow(vpx, 2) + pow(vpy, 2) + pow(vpz, 2)))
		);

	float grad_angle_betwen = tanks::rad_to_grad(rad_angle_betwen);
	return grad_angle_betwen;
};

Vector3<float> tanks::get_orthogonal(Vector3<float> direction)
{
	/*
	get perpendicular vector towards current
	u * v = vx * ux + vy * uy + vz * uz = 0
	ux = 1, uy = 1 - arbitrary
	vz * uz = -vx * ux - vy * uy
	uz = (-vx * ux - vy * uy) / vz
	*/
	float vx = direction.x, vy = direction.y, vz = direction.z;
	float ux = 0, uy = 0;
	float uz = (-vx * ux - vy * uy) / vz;
	Vector3<float> orthogonal = Vector3<float>(ux, uy, uz);
	orthogonal.normalize();
	return orthogonal;
};

float tanks::direction_to_angle(Vector3<float> direction)
{
	/*
		| arctan(y/x)			if x > 0
		| arctan(y / x) + Pi	if x < 0 and y >= 0
	Q =	| arctan(y / x) - Pi	if x < 0 and y < 0
		| Pi/2					if x = 0 and y > 0
		| -Pi/2					if x = 0 and y < 0
		| 0						if x = 0 and y = 0
 	*/
	float Pi = 3.14;
	float angle;

	if (direction.x > 0)
		angle = atan(direction.z / direction.x);
	else if (direction.x < 0 && direction.z >= 0)
		angle = atan(direction.z / direction.x) + Pi;
	else if(direction.x < 0 && direction.z < 0)
		angle = atan(direction.z / direction.x) - Pi;
	else if(direction.x == 0 && direction.z > 0)
		angle = Pi / 2;
	else if(direction.x == 0 && direction.z < 0)
		angle = -Pi / 2;
	else //direction.x == 0 && direction.z == 0
		angle = 0;
	
	return tanks::rad_to_grad(angle);
};

Vector3<float> tanks::euler_angle_to_direction(float angle, float magnitude)
{
	/*
		(r, Q) -> (x, y) = r * cosQ , r * sinQ
	*/
	float x = magnitude * cos(angle);
	float z = magnitude * sin(angle);
	Vector3<float> direction(x, 0.0, z);
	return direction;
};

Vector3<float> tanks::matrix_angle_to_direction(Vector3<float> v_angle)
{
	Matrix4<float> r_matrix = Matrix4<float>();
	r_matrix.rotate(v_angle.x, v_angle.y, v_angle.z);
	Vector3<float> direction = r_matrix.vProduct(1, 0, 0);
	return direction;
};