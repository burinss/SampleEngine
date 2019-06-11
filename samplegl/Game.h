#pragma once
#ifndef GAME_H
#define GAME_H

#include "RenderEngine.h"
#include "window.h"
#include "Input.h"
#include "model.h"
#include <iostream>
#include "filesystem.h"
#include <string>
#include "camera.h"
#include <math.h>
#include <ctime>
#include <thread>

class Game {
public:
	CSceneNode*obj;
	float deltaTime;
	Game() {

	}
	void Init() {
		Physics physics;
		deltaTime = 0;
		
		
		RenderEngine::SetCamera(new Camera(glm::vec3(0.0f, 20.0f, 0.0f)));

		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -48, 0));

		{
			btScalar mass(0.);

			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);

			btVector3 localInertia(0, 0, 0);
			if (isDynamic)
				groundShape->calculateLocalInertia(mass, localInertia);

			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);
			body->setUserPointer(nullptr);
			//add the body to the dynamics world
			physics.getPointer()->getDynamicsWorldPointer()->addRigidBody(body);
		}

			Model model(FileSystem::getPath("scene.bin"));
			obj = RenderEngine::GetSceneNodePtr()->AddChild(model.getNode(), "House");
			//obj->Update(false);
			//obj->SetScale(glm::vec3(0.2f));
			obj->SetRotation(glm::vec3(00.f, 0.0f, -90.0f));
			//obj->SetTranslation(glm::vec3(0.0f,35.0f,0.0f));

	}
	void Input() {
		RenderEngine::GetCamera()->body->activate();
		float offset = 5.0f;
		if (Input::GetDownKey(VK_ESCAPE))
		{
			Window::Close();
		}
		if (Input::GetDownKey(GLFW_KEY_W) || (Input::GetAxisStates()[1] > 0.1)) {
			//RenderEngine::GetCamera()->ProcessKeyboard(FORWARD, Input::GetAxisStates()[1] > 0.1 ? deltaTime* Input::GetAxisStates()[1] * 5  : deltaTime);
			
			//btVector3 dir(btScalar(0.1f), btScalar(0.0f), btScalar(0.0f));
			auto movedir = RenderEngine::GetCamera()->Front*2.f;

			RenderEngine::GetCamera()->body->applyCentralForce(btVector3(movedir.x, movedir.y, movedir.z));//applyCentralForce(btVector3(10.0f,0.0f,0.0f));
			//RenderEngine::GetCamera()->body->applyCentralImpulse
			//RenderEngine::GetCamera()->body->setLinearVelocity(btVector3(movedir.x, movedir.y, movedir.z));
		}
		if (Input::GetDownKey(GLFW_KEY_S) || Input::GetAxisStates()[1] < -0.1) {
			RenderEngine::GetCamera()->ProcessKeyboard(BACKWARD, Input::GetAxisStates()[1] < -0.1 ? deltaTime * -Input::GetAxisStates()[1] * 5 : deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_D) || Input::GetAxisStates()[0] > 0.025) {
			RenderEngine::GetCamera()->ProcessKeyboard(RIGHT, Input::GetAxisStates()[0] > 0.1 ? deltaTime * Input::GetAxisStates()[0] * 5 : deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_A) || Input::GetAxisStates()[0] < -0.1) {
			RenderEngine::GetCamera()->ProcessKeyboard(LEFT, Input::GetAxisStates()[0] < -0.1 ? deltaTime * -Input::GetAxisStates()[0] * 5 : deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_SPACE)) {
			RenderEngine::GetCamera()->body->applyCentralImpulse(btVector3(.0f, 1.0f, .0f));

			//RenderEngine::GetCamera()->body->
		}
		if (Input::GetDownKey(GLFW_KEY_UP)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.0f, offset);
		}
		if (Input::GetDownKey(GLFW_KEY_DOWN)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.1f, -offset);
		}
		if (Input::GetDownKey(GLFW_KEY_RIGHT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(offset,0.0f);
		}
		if (Input::GetDownKey(GLFW_KEY_LEFT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(-offset, 0.0f);
		}
		if (Input::GetDownKey(GLFW_KEY_Q)) {
			RenderEngine::GetCamera()->ProcessMouseScroll(0.1f);
		}
		if (Input::GetDownKey(GLFW_KEY_Z)) {
			RenderEngine::GetCamera()->ProcessMouseScroll(-0.1f);
		}

		if (Input::GetMouseButton(Input::MOUSE_LEFT)&& !Input::GetMouseButton(Input::MOUSE_RIGHT)) {
			Input::SetCursorMode(Input::DISABLED);
			RenderEngine::GetCamera()->ProcessMouseMovement(Input::GetMousedX(), Input::GetMousedY());
			//RenderEngine::GetCamera()->body->setAngularVelocity(btVector3(Input::GetMouseX(), Input::GetMouseY(), 0.0f));
			//RenderEngine::GetCamera()->ProcessMouseMovement(0.0f, 0.0f);
		}
		else if(!Input::GetMouseButton(Input::MOUSE_LEFT) && !Input::GetMouseButton(Input::MOUSE_RIGHT)) {
			Input::SetCursorMode(Input::NORMAL);
		}

		if (Input::GetMouseButton(Input::MOUSE_RIGHT)) {
			Input::SetCursorMode(Input::DISABLED);
			RenderEngine::GetCamera()->Position += (float)Input::GetMousedY()*0.05f*RenderEngine::GetCamera()->Front;
			RenderEngine::GetCamera()->Position += (float)Input::GetMousedX()*0.05f*RenderEngine::GetCamera()->Right;
		}
		else if (!Input::GetMouseButton(Input::MOUSE_RIGHT) && !Input::GetMouseButton(Input::MOUSE_LEFT)) {
			Input::SetCursorMode(Input::NORMAL);
		}
		/*RenderEngine::GetCamera()->ProcessMouseScroll((Input::GetAxisStates()[4]+2)/2);
		RenderEngine::GetCamera()->ProcessMouseScroll(-((Input::GetAxisStates()[5] + 2) / 2));
		RenderEngine::GetCamera()->ProcessMouseMovement(Input::GetAxisStates()[2]*10, Input::GetAxisStates()[3] * 10);*/
	}
	void Update() {


		Physics physics;
		
		static unsigned long int frames = 0;
		static float rotate = 0.0f;
		static float red, green, blue;
		double currentFrame = glfwGetTime();
		double lastFrame = 0.0f;
		static float time = 0;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		physics.getPointer()->getDynamicsWorldPointer()->stepSimulation(deltaTime);

		for (int j = physics.getPointer()->
							getDynamicsWorldPointer()->
							getNumCollisionObjects() - 1; 
			j >= 0;
			j--)
		{
			btCollisionObject* obj = physics.getPointer()->
											getDynamicsWorldPointer()->
											getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
			//printf("world pos = %f,%f,%f\n", float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
				Camera*obj = (Camera*)(body->getUserPointer());
				if (obj != nullptr) {
					obj->Position = glm::vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
					//obj->Pitch = trans.getRotation().getAxis().getX();
					//obj->Yaw= trans.getRotation().getAxis().getZ();
				}
			}
		}

		GUI::Text fps;

		fps.text = std::string("FPS : ") +std::to_string(1 / deltaTime)+ std::string(" |  TIME :")+ std::to_string(deltaTime) + std::string(" | Curr.frame : ")+std::to_string(++frames);
		fps.color = glm::vec3(1.0f);
		fps.x = 0.0f;
		fps.y = 700.0f;
		fps.scale = 0.4f;
		RenderEngine::Push_Text(fps);

		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);
		GUI::Text(date) {
			std::to_string(now->tm_mday) + "."
				+ std::to_string((now->tm_mon + 1)) + "."
				+ std::to_string((now->tm_year + 1900)),50.0f,50.0f,1.0f,glm::vec3(1.0f)
		};
		RenderEngine::Push_Text(date);

		GUI::Text(nowtime) {
			std::to_string(now->tm_hour) + ":"
				+ std::to_string(now->tm_min) + ":"
				+ std::to_string(now->tm_sec), 50.0f, 100.0f, 1.0f, glm::vec3(1.0f)
		};

		RenderEngine::Push_Text(nowtime);

		//fps.text = std::to_string();
		//geometry->SetRotation(new glm::vec3(0.0f, rotate, 0.0f));
		rotate += 0.1f;

		//obj->Update(true);
		//obj->SetRotation(glm::vec3(0.0f, 0.0f, rotate));
		//RenderEngine::currentShader->setVec3("lightColor", glm::vec3((sin(rotate)), (cos(rotate)), (sin(rotate+0.5f))));
		time += deltaTime;

	}
	void Render() {

	}
};
#endif