#include <GraphicsSystem.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace engine {
	GraphicsSystem::GraphicsSystem(){}
	GraphicsSystem::~GraphicsSystem(){}
	
	// Clears the screen using given color
	void GraphicsSystem::ClearScreen(float red, float green, float blue, bool setViewport) {
		// Sets wiewport and clears the screen by given color.
		//if (setViewport)
			//glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
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

	GLuint GraphicsSystem::CreateShader(int mode) {
		const char *vertexShaderSource = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"layout(location = 1) in vec2 aTexCoord;\n"
			"out vec2 TexCoord;\n"
			"uniform mat4 transform;\n"
			"void main()\n"
			"{\n"
				"gl_Position = vec4(aPos, 1.0);\n"
				"TexCoord = aTexCoord;\n"
			"}"	;
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;\n"
			"in vec2 TexCoord;\n"
			"uniform sampler2D ourTexture;\n"
			"void main()\n"
			"{\n"
				"FragColor = texture(ourTexture, TexCoord);\n"
			"}"	;

		const char *vertexShaderSourceuus = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"layout(location = 1) in vec2 aTexCoord;\n"
			"out vec2 TexCoord;\n"
			"uniform mat4 transform;\n"
			"void main()\n"
			"{\n"
				"gl_Position = transform * vec4(aPos, 1.0);\n"
				"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
			"}";
		const char *fragmentShaderSourceuus = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec2 TexCoord;\n"
			"uniform sampler2D texture;\n"
			"void main()\n"
			"{\n"
			"}";

		// build and compile our shader program
		// vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// link shaders
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
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
		if (mode = 0) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// textures
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		else if (mode = 1) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}
		else {
			std::cout << "error! Mode not available";
			return -1;
		}

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);

		return shaderProgram;
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

	void GraphicsSystem::transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) {
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(traX, traY, traZ));
		m_model = glm::rotate(m_model, speed, glm::vec3(rotX, rotY, rotZ));
		m_model = glm::scale(m_model, glm::vec3(scaleX, scaleY, scaleZ));

		m_view = glm::mat4(1.0f);
		m_projection = glm::ortho(0.0f, 1800.0f, 1000.0f, 0.0f);

		// Set MVP
		glm::mat4 mvp = m_projection * glm::inverse(m_view) * m_model;
		GLuint mvpLoc = glGetUniformLocation(object, "MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	void GraphicsSystem::transform(GLuint object, float speed, float traX, float traY, float traZ, float rotX, float rotY, float rotZ, float scale) {
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, glm::vec3(traX, traY, traZ));
		m_model = glm::rotate(m_model, glm::radians(90.0f), glm::vec3(rotX, rotY, rotZ));
		m_model = glm::scale(m_model, glm::vec3(scale, scale, scale));

		unsigned int transformLoc = glGetUniformLocation(object, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(m_model));

		m_view = glm::mat4(1.0f);
		m_projection = glm::ortho(0.0f, 1800.0f, 1000.0f, 0.0f);
	}

	void GraphicsSystem::moveCamera(){
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		m_cam[0] = sin(glfwGetTime()) * radius;
		m_cam[1] = cos(glfwGetTime()) * radius;

		m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}

}