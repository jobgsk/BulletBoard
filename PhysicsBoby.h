#ifndef PHYSICS_BODY_H_
#define PHYSICS_BODY_H_

#include <iostream>
#include "btBulletDynamicsCommon.h"
#include "converter.h"

class PhysicsBody  {
protected:
	btRigidBody* m_body;
	float m_x;
	float m_y;
	float m_z;
	float m_mass;
public:
	
	PhysicsBody(float x, float y, float z, float mass)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_mass = mass;
	};

	~PhysicsBody()
	{
		btMotionState* motionState = m_body->getMotionState();
		btCollisionShape* shape = m_body->getCollisionShape();

		delete m_body;
		delete shape;
		delete motionState;
	};

	btRigidBody* get_body()
	{
		return m_body;
	};

	int get_type()
	{
		return m_body->getCollisionShape()->getShapeType();
		//STATIC_PLANE_PROXYTYPE
		//BOX_SHAPE_PROXYTYPE
		//SPHERE_SHAPE_PROXYTYPE
	};

	void rotate(const btScalar yaw, const btScalar pitch, const btScalar roll)
	{
		btTransform tr;
		tr.setIdentity();
		btQuaternion quat;
		quat.setEuler(yaw, pitch, roll); //or quat.setEulerZYX depending on the ordering you want
		tr.setRotation(quat);
		m_body->setCenterOfMassTransform(tr);
	}

	Vector3<float> get_position()
	{
		return tanks::bullet_to_tanks(m_body->getCenterOfMassPosition());
	}

	Quaternion4<float> get_orientation()
	{
		return tanks::bullet_to_tanks(m_body->getOrientation());
		//btQuaternion orientation = m_body->getOrientation();
		//orientation.w(), orientation.x(), orientation.y(), orientation.z()
		//return Vector3<float>(orientation.x(), orientation.y(), orientation.z());
	}

	void set_position(Vector3<float> pos)
	{
		btTransform transform = m_body->getCenterOfMassTransform();
		transform.setOrigin(tanks::tanks_to_bullet(pos));
		m_body->setCenterOfMassTransform(transform);

		m_body->activate(true);
	}

	void set_velocity(Vector3<float> velocity)
	{

		std::cout << "velocity "
			<< velocity.x << " "
			<< velocity.y << " "
			<< velocity.z << " "
			<< std::endl;

		m_body->setLinearVelocity(tanks::tanks_to_bullet(velocity));
		m_body->activate(true);
	}

	void get_mat(float mat[])
	{
		btTransform t;
		m_body->getMotionState()->getWorldTransform(t);
		//float mat[16];
		t.getOpenGLMatrix(mat);
		//return mat;
	};
};


class PlainePhysicsBody : public PhysicsBody   {

public:
	PlainePhysicsBody(float x, float y, float z, float mass)
		:PhysicsBody(x, y, z, mass)
	{
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(m_x, m_y, m_z));
		btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
		btMotionState* motion = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo info(m_mass, motion, plane);
		m_body = new btRigidBody(info);
		m_body->setCollisionFlags(btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	};

};

class SpherePhysicsBody : public PhysicsBody   {

	float m_rad;
public:

	SpherePhysicsBody(float rad, float x, float y, float z, float mass)
		:PhysicsBody(x, y, z, mass)
	{
		m_rad = rad;

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(m_x, m_y, m_z));
		btSphereShape* sphere = new btSphereShape(m_rad);
		btVector3 inertia(0, 0, 0);
		if (m_mass != 0.0)
			sphere->calculateLocalInertia(m_mass, inertia);

		btMotionState* motion = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo info(m_mass, motion, sphere, inertia);
		m_body = new btRigidBody(info);
	};

	float get_radius()
	{
		float radius = ((btSphereShape*)m_body->getCollisionShape())->getRadius();
		return radius;
	}

};


class CylinderPhysicsBody : public PhysicsBody   {

	float m_diametr;
	float m_height;
public:

	CylinderPhysicsBody(float d, float h, float x, float y, float z, float mass)
		:PhysicsBody(x, y, z, mass)
	{
		m_diametr = d;
		m_height = h;

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(m_x, m_y, m_z));
		btCylinderShape* sphere = new btCylinderShape(btVector3(d / 2.0, h / 2.0, d / 2.0));
		btVector3 inertia(0, 0, 0);
		if (m_mass != 0.0)
			sphere->calculateLocalInertia(m_mass, inertia);

		btMotionState* motion = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo info(m_mass, motion, sphere, inertia);
		m_body = new btRigidBody(info);
		m_body->setDamping(0.2, 0.1);
	};

	btVector3 get_extent()
	{
		btVector3 extent = ((btCylinderShape*)m_body->getCollisionShape())->getHalfExtentsWithoutMargin();
		return extent;
	}

};


class BoxPhysicsBody : public PhysicsBody   {

	float m_width;
	float m_height;
	float m_depth;

public:

	BoxPhysicsBody(float width, float height, float depth, float x, float y, float z, float mass)
		:PhysicsBody(x, y, z, mass)
	{
		m_width = width;
		m_height = height;
		m_depth = depth;

		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(m_x, m_y, m_z));
		btBoxShape* sphere = new btBoxShape(btVector3(m_width / 2.0, m_height / 2.0, m_depth / 2.0));
		btVector3 inertia(0, 0, 0);
		if (m_mass != 0.0)
			sphere->calculateLocalInertia(m_mass, inertia);

		btMotionState* motion = new btDefaultMotionState(t);
		btRigidBody::btRigidBodyConstructionInfo info(m_mass, motion, sphere, inertia);
		m_body = new btRigidBody(info);
	};

	btVector3 get_extent()
	{
		btVector3 extent = ((btBoxShape*)m_body->getCollisionShape())->getHalfExtentsWithoutMargin();
		return extent;
	}

};



#endif /* PHYSICS_BODY_H_ */