#pragma once
#include <stdint.h>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functionality.h>
#include <fstream>

namespace engine {

	class GraphicsSystem {
	public:
		GraphicsSystem();
		~GraphicsSystem();

		// Clears the screen using given color
		void ClearScreen(GLFWwindow* window, float red, float green, float blue, bool setViewport = false);

		void DrawSprite(int shader, int texture);
		void DrawCube(int shader, int texture);

		GLuint CreateShader(const std::string vertexShaderName, const std::string fragmentShaderName);

		int loadTexture(char* filename);

		void transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
		void transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale);

		void moveCamera();

		Functionality *functions;
	private:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_model;


		float m_cam[2] = {0};
		const float radius = 10.0f;

		unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
		};

		// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
		// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
		/*GLfloat cubeVertices[108] = {
			-0.5f,-0.5f,-0.5f, // triangle 1 : begin
			-0.5f,-0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f, // triangle 1 : end
			0.5f, 0.5f,-0.5f, // triangle 2 : begin
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f,-0.5f, // triangle 2 : end
			0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f,-0.5f,
			0.5f,-0.5f,-0.5f,
			0.5f, 0.5f,-0.5f,
			0.5f,-0.5f,-0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f,-0.5f,
			0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f, 0.5f,
			-0.5f,-0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			-0.5f,-0.5f, 0.5f,
			0.5f,-0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f,-0.5f,-0.5f,
			0.5f, 0.5f,-0.5f,
			0.5f,-0.5f,-0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f,-0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f,-0.5f,
			-0.5f, 0.5f,-0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f,-0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f,-0.5f, 0.5f
		};*/

		GLfloat cubeVertices[180] = {
			// Positions		  // Textures
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
	};

}