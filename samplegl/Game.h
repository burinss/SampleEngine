#pragma once
#ifndef GAME_H
#define GAME_H
#include "window.h"
#include "Input.h"
#include <iostream>
#include <string>

class Game {
public:
	Game() {
			
	}
	void Input() {
		if (Input::GetDownKey(GLFW_KEY_ESCAPE))
		{
			Window::Close();
		}
	}
	void Update() {
		static char*title=nullptr;
		if (title = nullptr) {
			title = Window::GetTitle();
		}
		float currentFrame = glfwGetTime();
		static float lastFrame = 0.0f;
		static float deltaTime = 0.0f;

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (true) {
			//std::string name = std::string(title) + std::string(" | FPS ") + std::to_string(1 / lastFrame);
			Window::SetTitle((char*)std::to_string(1/deltaTime).c_str());
			//std::cout << 1/deltaTime << std::endl;
		}
	}
	void Render() {

	}
};
#endif