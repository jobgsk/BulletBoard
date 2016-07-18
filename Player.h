#ifndef PLAYER_H_
#define PLAYER_H_

#include "Vector3.h"
#include "math_helper.h"
#include "GameObject.h"

class Player {
public:

	int m_x, m_y;

	float m_force;
	float m_angle;
	Vector3<float> m_orientation;
	ArrowRender* m_render;
	Matrix4<float> m_matrix;

	GameObject * m_chip;

	int score;

	Player(ArrowRender* r, GameObject* chip) :
		m_render(r), m_chip(chip)
	{
		m_x = 0.0;
		m_y = 0.0;
		m_matrix = Matrix4<float>();
		score = 0;
	};

	void set_chip(GameObject* chip)
	{
		m_chip = chip;
	}

	void setup(int x, int y)
	{
		m_x = x;
		m_y = y;

		m_force = 0;
		m_angle = 0;

		m_orientation = Vector3<float>();
	};

	void shoot()
	{
		Vector3<float> direct = tanks::matrix_angle_to_direction(
			Vector3<float>(0, tanks::grad_to_rad(m_angle), 0));
		direct.normalize();
		direct.invert();
		direct *= m_force;
		m_chip->m_body->set_velocity(direct);
	}

	bool update()
	{
		bool res = false;
		Vector3<float> pos = m_chip->m_body->get_position();
		/*
		z
			0.75 >	10 > -0.75
			0 > right 8 > -1.5
			0 > right 7 > -2.5
			
			0 < left 8 < 1.5
			0 < left 7 < 2.5
		
		*/
		if ((pos.magnitude() - m_chip->prev_pos.magnitude()) == 0)
		{
			score = 0;
			res = true;
			if ((pos.x < -3 && pos.x > -4) && 
				(pos.z < 0.75 && pos.z > -0.75))
			{
				score = 10;
			}
			else if ((pos.x < -4 && pos.x > -5) && 
				(pos.z > -1.5 && pos.z < 1.5))
			{
				score = 8;
			}
			else if ((pos.x < -5 && pos.x > -6) && 
				(pos.z > -2.5 && pos.z < 2.5))
			{
				score = 7;
			}
		}
		m_chip->prev_pos = pos;
		return res;
	}

	void aim(int x, int y)
	{
		// update deltaAngle
		m_angle = (x - m_x) * 0.2;
		m_force = (y - m_y) * 0.1;
		if (m_force < 0)
			m_force = 0;

		//m_orientation.x = sin(m_angle);
		//m_orientation.z = -cos(m_angle);
		m_orientation = tanks::euler_angle_to_direction(m_angle, 1);

		std::cout << " force " << m_force 
			<< " angle " << m_angle
			<< " orientation " 
			<< m_orientation.x << " " 
			<< m_orientation.y << " "
			<< m_orientation.z << " "
			<< std::endl;
	};

	void render()
	{
		Vector3<float> pos = m_chip->m_body->get_position();
		m_matrix.init();
		m_matrix.translate(pos.x, pos.y - 0.2, pos.z);
		//m_matrix.scale(m_force, 1, 1);
		//float angle = tanks::direction_to_angle(m_orientation);
		//m_matrix.rotate(0, tanks::grad_to_rad(angle), 0);
		m_matrix.rotate(0, tanks::grad_to_rad(m_angle), 0);

		float mat[16];
		m_matrix.get_mat(mat);

		m_render->set_force(m_force);
		m_render->render(mat);
	};
};

#endif /* PLAYER_H_ */