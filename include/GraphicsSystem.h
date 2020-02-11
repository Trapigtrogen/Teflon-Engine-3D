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

namespace engine {

	class GraphicsSystem {
	public:
		GraphicsSystem();
		~GraphicsSystem();

		// Clears the screen using given color
		void ClearScreen(float red, float green, float blue, bool setViewport);
		void DrawSprite(int shader, int texture);
		void DrawCube(int shader, int texture);
		GLuint CreateShader(int mode);

		int loadTexture(char* filename);

		void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
		void transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale);

		void moveCamera();
	private:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_model;


		float m_cam[2] = {0};
		const float radius = 10.0f;

		float spriteVertices[32] = {
			// positions            // texture coords
			 0.5f,  0.5f, 0.0f,     1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,     1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,     0.0f, 1.0f    // top left 
		};

		unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
		};

		// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
		// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
		GLfloat cubeVertices[108] = {
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
		};
	};

}