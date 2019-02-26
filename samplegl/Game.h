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

class Game {
public:
	CGeometryNode*geometry;
	float deltaTime;
	Game() {

	}
	void Init() {
		deltaTime = 0;
		Model*model=new Model(FileSystem::getPath("house/WoodenCabinObj.obj"));
		geometry = new CGeometryNode(model->GetMeshes());
		RenderEngine::AddObj(geometry);
		RenderEngine::SetCamera(new Camera(glm::vec3(0.0f, 0.0f, 3.0f)));
		delete model;
	}
	void Input() {
		float offset = 5.0f;
		if (Input::GetDownKey(GLFW_KEY_ESCAPE))
		{
			Window::Close();
		}
		if (Input::GetDownKey(GLFW_KEY_W)) {
			RenderEngine::GetCamera()->ProcessKeyboard(FORWARD,deltaTime);
			//std::cout << "forward " << deltaTime << std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_S)) {
			RenderEngine::GetCamera()->ProcessKeyboard(BACKWARD, deltaTime);
			//std::cout << "backward" << deltaTime << std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_D)) {
			RenderEngine::GetCamera()->ProcessKeyboard(RIGHT, deltaTime);
			//std::cout << "right " << deltaTime << std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_A)) {
			RenderEngine::GetCamera()->ProcessKeyboard(LEFT, deltaTime);
			//std::cout << "left "<<deltaTime<<std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_UP)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.0f, offset);
			//std::cout << "left "<<deltaTime<<std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_DOWN)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.1f, -offset);
			//std::cout << "left "<<deltaTime<<std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_RIGHT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(offset,0.0f);
			//std::cout << "left "<<deltaTime<<std::endl;
		}
		if (Input::GetDownKey(GLFW_KEY_LEFT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(-offset, 0.0f);
			//std::cout << "left "<<deltaTime<<std::endl;
		}
	}
	void Update() {
		static glm::vec3 rotation(0.0f,.0f,.0f);
		float currentFrame = glfwGetTime();
		static float lastFrame = 0.0f;
		static float time = 0;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (time>0.1) {
			//rotation += glm::vec3(0.0f,0.0f,0.1f);
			//std::string name = std::string(title) + std::string(" | FPS ") + std::to_string(1 / lastFrame);
			Window::SetTitle((char*)std::to_string(1/deltaTime).c_str());
			time = 0;
			//std::cout << 1/deltaTime << std::endl;
			
		}
		//geometry->SetRotation(&rotation);
		time += deltaTime;
	}
	void Render() {
	}
};
#endif