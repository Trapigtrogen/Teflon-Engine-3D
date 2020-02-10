#pragma once
#include <stdint.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>

namespace engine {

	class GraphicsSystem {
	public:
		GraphicsSystem();
		~GraphicsSystem();

		// Clears the screen using given color
		void ClearScreen(float red, float green, float blue, bool setViewport);
		void DrawSprite(int shader);
		void DrawCube(int shader);
		int CreateShader(GLfloat* vertices);
	private:
		
	};

}