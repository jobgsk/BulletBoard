#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector3.h"
#include "matrix4.h"
#include "GameObject.h"

class Camera  {	

public:

	GameObject *m_target;
	float m_distance;

	Vector3<float> m_position;
	Vector3<float> m_orientation;

	Camera(GameObject *target, float distance) :
		m_target(target), m_distance(distance)

	{
		update();
	};

	void update()
	{
		Matrix4<float> mat4 = Matrix4 <float>();
		Vector3<float> ptarget = m_target->m_body->get_position();
		Quaternion4<float> qtarget = m_target->m_body->get_orientation();

		//qtarget.addScaledVector(Vector3<float>(1, 0, 1), -1);
		/*std::cout << "camera position "
		<< qtarget.w << " "
		<< qtarget.x << " "
		<< qtarget.y << " "
		<< qtarget.y << " "
		<< std::endl;
		*/
		mat4.set_quaternion(qtarget.w, qtarget.x, -qtarget.y, qtarget.z);
		Vector3<float> otarget = mat4.vProduct(1, 0, 0);

		//otarget.invert();
		otarget.normalize();

		Vector3<float> pos = (otarget * m_distance) + ptarget;
		m_position = Vector3<float>(pos.x, pos.y + 10, pos.z);
		//m_position = Vector3<float>(p.x + 10, p.y + 10, p.z + 10);
		m_orientation = ptarget;



		//m_position = Vector3<float>(10, 10, 10);
		//m_orientation = Vector3<float>(0, 0, 0);
	};

};

#endif /* CAMERA_H_ */