#pragma once

#include <GLFW/glfw3.h>
#include "window.h"
#include <map>
#include <iostream>

class Input {
public:
	Input() {

	}
	static void Update() {
		
	}
	inline static bool GetDownKey(int Key) {
		return glfwGetKey(Window::GetWindow(), Key);
	}
	inline static bool GetUpKey(int Key) {
		return !glfwGetKey(Window::GetWindow(), Key);
	}
};
