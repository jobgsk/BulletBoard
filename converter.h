#ifndef CONVERTER_H
#define CONVERTER_H

#include "btBulletDynamicsCommon.h"
#include "Vector3.h"
#include "quaternion4.h"


namespace tanks {

	Vector3<float> bullet_to_tanks(const btVector3& v);
	Quaternion4<float> bullet_to_tanks(const btQuaternion& q);

	btVector3 tanks_to_bullet(Vector3<float> v);
	btQuaternion tanks_to_bullet(Quaternion4<float> v);
};
#endif // CONVERTER_H
