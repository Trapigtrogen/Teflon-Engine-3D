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
#include <Mesh.h>
#include <Shader.h>

namespace engine {
	class GraphicsSystem {
	public:
		GraphicsSystem();
		~GraphicsSystem();

		// Clears the screen using given color
		void ClearScreen(GLFWwindow* window, float red, float green, float blue, bool setViewport = false);

		void DrawSprite(Shader shader, int texture);
		void DrawCube(Shader shader, int texture);

		int loadTexture(char* filename);

		// Object movement
		void transform(Shader shader, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
		void transform(Shader shader, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale);

		// Camera movement
		void PositionCamera(float posX, float posY, float posZ);
		void MoveCamera(float posX, float posY, float posZ);

		void RotateCamera(float pitch, float yaw, float roll);
		void RotateCameraContinuous(float pitch, float yaw, float roll);

		void MoveCameraForwards(float speed);
		void MoveCameraBackwards(float speed);
		void MoveCameraRight(float speed);
		void MoveCameraLeft(float speed);
		void MoveCameraUp(float speed);
		void MoveCameraDown(float speed);
		
		void RotateCameraPitch(float angle);
		void RotateCameraYaw(float angle);
		void RotateCameraRoll(float angle);

		Functionality functions;
	private:
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 model;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);

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