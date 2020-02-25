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

		// Object movement
		void transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
		void transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale);

		// Camera movement
		void MoveCamera(float posX, float posY, float posZ);
		void MoveCameraContinuous(float posX, float posY, float posZ);

		void RotateCamera(float rotX, float rotY, float rotZ);
		void RotateCameraContinuous(float rotX, float rotY, float rotZ);

		void MoveCameraForwards(float speed);
		void MoveCameraBackwards(float speed);
		void MoveCameraRight(float speed);
		void MoveCameraLeft(float speed);
		void MoveCameraUp(float speed);
		void MoveCameraDown(float speed);
		
		void RotateCameraUp(float speed);
		void RotateCameraDown(float speed);
		void RotateCameraRight(float speed);
		void RotateCameraLeft(float speed);
		void RotateCameraRoll(float speed);

		Functionality *functions;
	private:
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		unsigned int indices[6] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

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

		GLfloat spriteVertices[180] = {
			// Positions		  // Textures
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f
		};
	};
}