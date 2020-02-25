#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>
#include <GraphicsSystem.h>
#include <InputManager.h>

namespace engine {
	class Window {
	public:
		Window();
		~Window();

		GLFWwindow* CreateWindow(int windowWidth, int windowHeight, bool fullscreen = 0);

		InputManager input;
		Functionality* functions;
	private:
		GraphicsSystem* m_graphics;
		GLFWwindow* appWindow;

		const GLFWvidmode* monitorInfo;
		GLFWmonitor* monitorContext;
	};
}