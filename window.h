#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
//https://github.com/Saikedo/CPP-OpenGL-3D-Game-Engine/tree/master/Saik%20Engine

class Window {
public:
	Window(const int width, const int height, const char* title);
	~Window();

	GLFWwindow* getWindow() {
		return window;
	}

	int getWindowWidth() {
		return screenWidth;
	}

	int getWindowHeight() {
		return screenHeight;
	}

	static Window* getWindowInstance() { return instance; }

private:
	static Window* instance;
	GLFWwindow* window;
	int screenWidth;
	int screenHeight;
};