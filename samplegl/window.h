#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_EXPOSE_NATIVE_WGL
//#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>
#include <WinUser.h>
#include <iostream>
#include <commdlg.h>
#include <CommCtrl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Keyboard/KeyboardClass.h"
#include "Mouse/MouseClass.h"


class Window {
private:
	static char*Title;
	static int SCR_WIDTH;
	static int SCR_HEIGHT;
	static GLFWwindow* window;
	static HMENU hMenu;
	static LONG glfwProc;
public:
	static KeyboardClass keyboard;
	static MouseClass mouse;

	static int Create(int scr_width, int scr_height, const char * title, bool fullscreen = false)
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

		glfwWindowHint(GLFW_SAMPLES, 4);

		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
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
		//hMenu = CreateMenu();

		HWND hWnd =  glfwGetWin32Window(window);

		int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - scr_width / 2;
		int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - scr_height / 2;

		RECT rect;
		rect.left = centerScreenX;
		rect.top = centerScreenY;
		rect.right = rect.left + scr_width;
		rect.bottom = rect.top + scr_height;

		AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,TRUE);

		SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);

		SetWindowSubclass(hWnd, &WndProc, 1, 0);
		HMENU hMenubar = CreateMenu();
		HMENU hFile = CreateMenu();
		HMENU hOptions = CreateMenu();
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, L"File");

		AppendMenu(hFile, MF_STRING, 0, L"New");
		AppendMenu(hFile, MF_STRING, 1, L"Open");
		AppendMenu(hFile, MF_STRING, 2, L"Exit");

		glfwShowWindow(window);

		SetMenu(hWnd, hMenubar);

		return 0;
	}

	static unsigned int GetWidth()
	{
		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		return SCR_WIDTH;
	}
	static unsigned int GetHeight()
	{
		glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
		return SCR_HEIGHT;
	}
	static char * GetTitle()
	{
		return Title;
	}
	static void SetTitle(char * NewTitle)
	{
		Title = NewTitle;
		glfwSetWindowTitle(window, Title);
	}

	static bool isClose()
	{
		return glfwWindowShouldClose(window);
	}
	static void Destroy()
	{
		glfwDestroyWindow(window);
	}
	static void Close()
	{
		glfwSetWindowShouldClose(window, true);
	}

	static GLFWwindow* GetWindow()
	{
		return window;
	}

	static void Render()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		switch (uMsg)
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case 1:
			{
				OPENFILENAME ofn;       // common dialog box structure
				LPWSTR szFile = (LPWSTR)"";       // buffer for file name
				HWND hwnd;              // owner window
				HANDLE hf;              // file handle

				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = L"All\0*.*\0Object (.obj)\0*.OBJ\0FBX (.FBX)\0*.FBX;*.blend\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				// Display the Open dialog box. 

				if (GetOpenFileName(&ofn) == TRUE)
					hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
						0, (LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
						(HANDLE)NULL);
				break;
			}
			case 2:
				Close();
				PostQuitMessage(0);
				return 0;
			}
		}
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
	}
};


#endif