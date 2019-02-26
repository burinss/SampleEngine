#pragma once
#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CScene.h"
#include "camera.h"
#include "model.h"
#include "window.h"


class RenderEngine{
private:
	static Camera*currentCamera;
public:
	static void SetCamera(Camera*NewCamera) {
		/*if (currentCamera)*/
			delete currentCamera;
		currentCamera = NewCamera;
	}
	static inline Camera* GetCamera() {
		return currentCamera;
	}
	static void AddObj(CSceneNode*node) {
		scene.AddChild(node);
	}
	static void Render() {
		currentShader->setVec3("viewPos",currentCamera->Position);
		currentShader->setVec3("lightPos", glm::vec3(0.0f,0.0f,5.0f));
		currentShader->setMat4("view", currentCamera->GetViewMatrix());
		currentShader->setMat4("projection", glm::perspective(glm::radians(currentCamera->Zoom), (float)Window::GetWidth() / (float)Window::GetHeight(), 0.1f, 100.0f));

		scene.Draw(currentShader);
	}
	inline static void Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	static void Init() {
		currentShader = new Shader("vertex.vs","fragment.fs");
		currentShader->use();
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);

		glEnable(GL_FRAMEBUFFER_SRGB);
	}
	static void Terminate() {
		glfwTerminate();
	}
public:
	static Shader*currentShader;
	static CSceneNode scene;
};
CSceneNode RenderEngine::scene;
Camera*RenderEngine::currentCamera;
Shader*RenderEngine::currentShader;
#endif