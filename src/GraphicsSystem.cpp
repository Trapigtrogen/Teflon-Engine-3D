#include <GraphicsSystem.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace engine {
	GraphicsSystem::GraphicsSystem() {
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	}
	GraphicsSystem::~GraphicsSystem() {}
	
	// Clears the screen using given color
	void GraphicsSystem::ClearScreen(GLFWwindow* window, float red, float green, float blue, bool setViewport) {
		// Sets wiewport and clears the screen by given color.
		if (setViewport) {
			int size[2];
			glfwGetWindowSize(window, &size[0], &size[1]);
			glViewport(0, 0, size[0], size[1]);
		}

		glClearColor(red, green, blue, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void GraphicsSystem::DrawCube(Shader shader, int texture) {
		glUseProgram(shader.id);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
	}

	int GraphicsSystem::loadTexture(char* filename) {
		unsigned int texture;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		int width, height, nrChannels;
		unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
		return texture;
	}

	void GraphicsSystem::Transform(Model model_, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) {
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(traX, traY, traZ));
		model = glm::rotate(model, angle, glm::vec3(rotX, rotY, rotZ));
		model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

		unsigned int modelLoc = glGetUniformLocation(model_.attachedShaderId, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(model_.attachedShaderId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projLoc = glGetUniformLocation(model_.attachedShaderId, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void GraphicsSystem::Transform(Model model_, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale) {
		
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(traX, traY, traZ));
		model = glm::rotate(model, angle, glm::vec3(rotX, rotY, rotZ));
		model = glm::scale(model, glm::vec3(scale, scale, scale));

		unsigned int modelLoc = glGetUniformLocation(model_.attachedShaderId, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(model_.attachedShaderId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projLoc = glGetUniformLocation(model_.attachedShaderId, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void GraphicsSystem::MoveCamera(float posX, float posY, float posZ) {
		cameraPos += glm::vec3(posX, posY, posZ);
		cameraTarget += glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}
	
	void GraphicsSystem::PositionCamera(float posX, float posY, float posZ) {
		cameraPos = glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}
	
	void GraphicsSystem::RotateCameraContinuous(float yaw, float pitch, float roll) {
		
	}
	
	void GraphicsSystem::RotateCamera(float yaw, float pitch, float roll) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		cameraFront = glm::normalize(direction);
		cameraTarget = glm::normalize(direction);

		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	}
	
	void GraphicsSystem::MoveCameraForwards(float speed) {
		glm::vec3 moveVector = cameraFront * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraBackwards(float speed) {
		glm::vec3 moveVector = -cameraFront * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraLeft(float speed) {
		glm::vec3 moveVector = -glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraRight(float speed) {
		glm::vec3 moveVector = glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraUp(float speed) {
		glm::vec3 moveVector = cameraUp * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraDown(float speed) {
		glm::vec3 moveVector = -cameraUp * speed;
		MoveCamera(moveVector.x, moveVector.y, moveVector.z);
	}


	void GraphicsSystem::RotateCameraPitch(float angle) {
		
	}
	
	void GraphicsSystem::RotateCameraYaw(float amount) {
		
	}
	
	void GraphicsSystem::RotateCameraRoll(float amount) {
		
	}

}