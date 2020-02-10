#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>
#include <GraphicsSystem.h>

namespace engine {
	class GraphicsSystem;

	class Window {
	public:
		Window();
		~Window();

		GLFWwindow* CreateWindow(int windowWidth, int windowHeight);
		void ProcessInput(GLFWwindow *window);
	private:
		GraphicsSystem*		m_graphics;
	};
}