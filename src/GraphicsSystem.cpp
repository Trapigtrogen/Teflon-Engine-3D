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
	
	void GraphicsSystem::DrawSprite(int shader, int texture) {
		glUseProgram(shader);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLES, 0, 12);
	}
	
	void GraphicsSystem::DrawCube(int shader, int texture) {
		glUseProgram(shader);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
	}

	GLuint LoadShader(GLenum type, const char *shaderSrc) {
		// Create the shader object
		GLuint shader = glCreateShader(type);
		if (shader == 0) return 0;

		// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, NULL);
		// Compile the shader
		glCompileShader(shader);
		// Check the compile status
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1) {
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				free(infoLog);
			}
			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	GLuint GraphicsSystem::CreateShader(const std::string vertexShaderName, const std::string fragmentShaderName) {
		GLuint programObject = glCreateProgram();

		std::string strVertexShader = functions->loadFile(vertexShaderName);
		GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, strVertexShader.c_str());

		std::string strFragmentShader = functions->loadFile(fragmentShaderName);
		GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, strFragmentShader.c_str());

		glAttachShader(programObject, vertexShader);
		glAttachShader(programObject, fragmentShader);

		glLinkProgram(programObject);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		// use shader
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// textures
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);

		return programObject;
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

	void GraphicsSystem::transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) {
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(traX, traY, traZ));
		model = glm::rotate(model, angle, glm::vec3(rotX, rotY, rotZ));
		model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

		unsigned int modelLoc = glGetUniformLocation(object, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(object, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projLoc = glGetUniformLocation(object, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void GraphicsSystem::transform(GLuint object, float angle, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale) {
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(traX, traY, traZ));
		model = glm::rotate(model, angle, glm::vec3(rotX, rotY, rotZ));
		model = glm::scale(model, glm::vec3(scale, scale, scale));

		unsigned int modelLoc = glGetUniformLocation(object, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(object, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projLoc = glGetUniformLocation(object, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void GraphicsSystem::MoveCameraContinuous(float posX, float posY, float posZ) {
		cameraPos += glm::vec3(posX, posY, posZ);
		cameraTarget += glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}
	
	void GraphicsSystem::MoveCamera(float posX, float posY, float posZ) {
		cameraPos = glm::vec3(posX, posY, posZ);
		cameraTarget = glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}
	
	void GraphicsSystem::RotateCameraContinuous(float posX, float posY, float posZ) {
		cameraPos += glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}
	
	void GraphicsSystem::RotateCamera(float posX, float posY, float posZ) {
		cameraPos = glm::vec3(posX, posY, posZ);
		
		view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
		unsigned int viewLoc = glGetUniformLocation(0, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	}

	
	void GraphicsSystem::MoveCameraForwards(float speed) {
		glm::vec3 moveVector = cameraFront * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraBackwards(float speed) {
		glm::vec3 moveVector = -cameraFront * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraLeft(float speed) {
		glm::vec3 moveVector = -glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraRight(float speed) {
		glm::vec3 moveVector = glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraUp(float speed) {
		glm::vec3 moveVector = cameraUp * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::MoveCameraDown(float speed) {
		glm::vec3 moveVector = -cameraUp * speed;
		MoveCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}


	void GraphicsSystem::RotateCameraUp(float speed) {
		glm::vec3 moveVector = cameraFront * speed;
		RotateCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::RotateCameraDown(float speed) {
		glm::vec3 moveVector = -cameraFront * speed;
		RotateCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::RotateCameraLeft(float speed) {
		glm::vec3 moveVector = -glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		RotateCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}
	
	void GraphicsSystem::RotateCameraRight(float speed) {
		glm::vec3 moveVector = glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		RotateCameraContinuous(moveVector.x, moveVector.y, moveVector.z);
	}

}