#pragma once

#include <GLFW/glfw3.h>
#include "window.h"
#include <map>
#include <iostream>
//#include "ErrorLogger.h"

class Input {
private:
	static double mouseX, mouseY;
	static double dxmouse, dymouse;
public:
	enum cursorState { NORMAL = GLFW_CURSOR_NORMAL, DISABLED = GLFW_CURSOR_DISABLED, HIDDEN = GLFW_CURSOR_HIDDEN };
	enum mouseButton { MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT, MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT, MOUSE_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE };
	Input() {
		static bool raw_input_initialized = false;
		if (raw_input_initialized == false)
		{
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 0x01; //Mouse
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;

			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				//ErrorLogger::Log(GetLastError(), "Failed to register raw input devices.");
				exit(-1);
			}

			raw_input_initialized = true;
		}
		//glfwSetInputMode(Window::GetWindow(), GLFW_STICKY_MOUSE_BUTTONS, 1);

		this->mouseX = .0;
		this->mouseY = .0;
	}
	static void Update() {
		//MouseEvent me = Window::mouse.ReadEvent();
		////if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		////{
		//	mouseX = me.GetPosX();
		//	mouseY = me.GetPosY();
		////}
		glfwGetCursorPos(Window::GetWindow(), &mouseX, &mouseY);
		static double lastX = mouseX, lastY = mouseY;

		dxmouse = mouseX - lastX;
		dymouse = lastY - mouseY;

		lastX = mouseX;
		lastY = mouseY;

	}
	inline static bool GetDownKey(int Key) {
		//return Window::keyboard.KeyIsPressed(Key);
		return glfwGetKey(Window::GetWindow(),Key);
	}
	inline static bool GetUpKey(int Key) {
		//return !Window::keyboard.KeyIsPressed(Key);
		return !glfwGetKey(Window::GetWindow(), Key);
	}
	inline static bool GetMouseButton(int Button) {
		/*switch (Button)
		{
		case MOUSE_LEFT:
			return Window::mouse.IsLeftDown();
		case MOUSE_MIDDLE:
			return Window::mouse.IsMiddleDown();
		case MOUSE_RIGHT:
			return Window::mouse.IsRightDown();
		}
		return false;*/
		return glfwGetMouseButton(Window::GetWindow(), Button) == GLFW_PRESS ? true : false;
	}
	inline static double GetMouseX() {
		return mouseX;
	}
	inline static double GetMouseY() {
		return mouseY;
	}
	inline static double GetMousedX() {
		return dxmouse;
	}
	inline static double GetMousedY() {
		return dymouse;
	}
	inline static float * GetAxisStates() {
		int count;
		return (float*)glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
	}
	inline static void SetCursorMode(int Value) {
		glfwSetInputMode(Window::GetWindow(), GLFW_CURSOR, Value);
	}
};
double Input::mouseX;
double Input::mouseY;
double Input::dxmouse;
double Input::dymouse;
