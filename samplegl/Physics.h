#pragma once
#include <btBulletDynamicsCommon.h>



class Physics {
private:
	static Physics * thispointer;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
public:
	static Physics *getPointer() {
		return thispointer;
	}
	btDiscreteDynamicsWorld* getDynamicsWorldPointer() {
		return dynamicsWorld;
	}
	Physics() {
		if (thispointer == nullptr) {
			thispointer = this;
			Init();
		}
	}
	~Physics() {
		//thispointer = nullptr;
		//Stop();
	}
private:

	void Init() {
		broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
		//btAlignedObjectArray<btCollisionShape*> collisionShapes;
	}
	void Stop() {
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		/*for (int j = 0; j < collisionShapes.size(); j++)
		{
			btCollisionShape* shape = collisionShapes[j];
			collisionShapes[j] = 0;
			delete shape;
		}*/
		//delete dynamics world
		delete dynamicsWorld;

		//delete solver
		delete solver;

		delete broadphase;
		//delete overlappingPairCache;

		//delete dispatcher
		delete dispatcher;

		delete collisionConfiguration;

		//next line is optional: it will be cleared by the destructor when the array goes out of scope
		//collisionShapes.clear();
	}
};
#ifndef _THISPOINTER_
#define _THISPOINTER_
//Physics * Physics::thispointer;
#endif

class PhysicsObject {
public:
	btRigidBody* body;
	btCollisionShape* CollisionShape;
};
