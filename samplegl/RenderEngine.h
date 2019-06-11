#pragma once
#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CScene.h"
#include "camera.h"
#include "model.h"
#include "window.h"
#include "GUIrenderer.h"


class RenderEngine{
private:
	static GUIrender*Grender;
	static Camera*currentCamera;
	static Shader*currentShader;
	static CSceneNode*scene;
public:
	static CSceneNode* GetSceneNodePtr()  {
		return scene;
	}
	static void SetCamera(Camera*NewCamera) {
			delete currentCamera;
		currentCamera = NewCamera;
	}
	static inline Camera* GetCamera() {
		return currentCamera;
	}
	/*static void AddObj(CSceneNode*node) {
		scene->AddChild(node);
	}*/
	static void Render() {
		currentShader->use();
		currentShader->setVec3("lightColor", glm::vec3(15.0f, 15.0f, 15.0f));
		currentShader->setFloat("lightRadius", 40.0f);
		currentShader->setFloat("compression", 2.0f);
		currentShader->setVec3("viewPos",currentCamera->Position);
		currentShader->setVec3("lightPos", glm::vec3(-20.0f,30.0f,-3.0f));
		currentShader->setMat4("view", currentCamera->GetViewMatrix());
		currentShader->setMat4("projection", glm::perspective(glm::radians(currentCamera->Zoom), (float)Window::GetWidth() / (float)Window::GetHeight(), 0.1f, 100.0f));

		scene->Draw(currentShader);
		Grender->Render();
	}
	inline static void Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	static void Init(CSceneNode*scenePointer) {
		scene = scenePointer;

		currentShader = new Shader("vertex.vs","fragment.fs");

		Grender = new GUIrender;

		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);
		glEnable(GL_BLEND);
		glEnable(GL_MULTISAMPLE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_FRAMEBUFFER_SRGB);
	}
	static void Push_Text(GUI::Text text) {
		Grender->PushElement(text);
	}
	static void Terminate() {
		glfwTerminate();
	}
public:

};
GUIrender*RenderEngine::Grender;
CSceneNode*RenderEngine::scene;
Camera*RenderEngine::currentCamera;
Shader*RenderEngine::currentShader;
#endif