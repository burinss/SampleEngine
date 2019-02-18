#pragma once
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include "camera.h"

class RenderEngine{
private:
	static Camera * mainCamera;
public:
	static void Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	static void Init() {
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);

		glEnable(GL_FRAMEBUFFER_SRGB);
	}
	static void Terminate() {
		glfwTerminate();
	}
};