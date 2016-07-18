#ifndef PHYSICS_WORLD_H_
#define PHYSICS_WORLD_H_

#include "btBulletDynamicsCommon.h"
#include "GameObject.h"
#include <GL/glut.h>

class PhysicsWorld  {

	btDynamicsWorld* m_world;
	btDispatcher* m_dispatcher;
	btCollisionConfiguration* m_collisionConfig;
	btBroadphaseInterface* m_broadphase;
	btConstraintSolver* m_solver;

public:
	

	PhysicsWorld()
	{
		m_collisionConfig = new btDefaultCollisionConfiguration();
		m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
		m_broadphase = new btDbvtBroadphase();
		m_solver = new btSequentialImpulseConstraintSolver();
		m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);
		m_world->setGravity(btVector3(0, -10, 0));

	};

	~PhysicsWorld()
	{
		delete m_dispatcher;
		delete m_collisionConfig;
		delete m_solver;
		delete m_broadphase;
		delete m_world;
	}

	void add_body(GameObject* obj)
	{
		btRigidBody* body = obj->m_body->get_body();
		m_world->addRigidBody(body);
		body->setUserPointer(obj);
	}

	void delete_body(GameObject* obj)
	{
		btRigidBody* body = obj->m_body->get_body();
		m_world->removeCollisionObject(body);
	}

	void run()
	{
		m_world->stepSimulation(1 / 60.0);
	}
};

#endif /* PHYSICS_WORLD_H_ */