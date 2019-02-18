#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include <stdlib.h>

class Window {
private:
	static char*Title;
	static int SCR_WIDTH;
	static int SCR_HEIGHT;
	static GLFWwindow* window;
public:
	static int Create(int scr_width, int scr_height, const char * title)
	{
		SCR_HEIGHT = scr_height;
		SCR_WIDTH = scr_width;
		Title = (char*)title;

		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return -1;
		}
		return 0;
	}
	static unsigned int GetWidth() {
		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		return SCR_WIDTH;
	}
	static unsigned int GetHeight() {
		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		return SCR_HEIGHT;
	}
	inline static char * GetTitle() {
		return Title;
	}
	inline static void SetTitle(char * NewTitle) {
		Title = NewTitle;
		glfwSetWindowTitle(window, Title);
	}
	inline static bool isClose() {
		return glfwWindowShouldClose(window);
	}
	static void Destroy() {
		glfwDestroyWindow(window);
	}
	static void Close() {
		glfwSetWindowShouldClose(window, true);
	}
	inline static GLFWwindow* GetWindow() {
		return window;
	}
	static void Render() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
};
#endif