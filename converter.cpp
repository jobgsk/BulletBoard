
#include "converter.h"

Vector3<float> tanks::bullet_to_tanks(const btVector3& v)
{
	return Vector3<float>(v.x(), v.y(), v.z());
};

Quaternion4<float> tanks::bullet_to_tanks(const btQuaternion& q)
{
	return Quaternion4<float>(q.w(), q.x(), q.y(), q.z());
};


btVector3 tanks::tanks_to_bullet(Vector3<float> v)
{
	return btVector3(v.x, v.y, v.z);
};

btQuaternion tanks::tanks_to_bullet(Quaternion4<float> q)
{
	return btQuaternion(q.x, q.y, q.z, q.w);
};