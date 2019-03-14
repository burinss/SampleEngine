#pragma once
#include "RenderEngine.h"
#include "window.h"
#include "Game.h"
#include "Input.h"
#include <btBulletDynamicsCommon.h>


GLFWwindow* Window::window;
int Window::SCR_WIDTH;
int Window::SCR_HEIGHT;
char* Window::Title;


class EngineCore {
public:
	EngineCore(int width,int height,const char*title,Game*game) {
		Window::Create(width,height,title);
		sceneRoot= new CSceneNode;
		RenderEngine::Init(sceneRoot);
		this->game = *game;
		IsRunning = true;
		Run();
	};
	~EngineCore() {
		Window::Destroy();
	} 
	void Run() {
		game.Init();
		while (IsRunning) {
			if (Window::isClose()) {
				Stop();
				return;
			}
			Input::Update();
			game.Input();
			game.Update();
			Render();
		}
	}
	void Stop() {
		if (!IsRunning)
			return;
		IsRunning = false;
		Window::Destroy();
		RenderEngine::Terminate();
	}
	void Start() {
		if (IsRunning)
			return;
		Run();
	}
private:
	CSceneNode * sceneRoot;
	Game game;
	bool IsRunning;

	void Render() {
		RenderEngine::Clear();
		game.Render();
		RenderEngine::Render();
		Window::Render();
	}
};