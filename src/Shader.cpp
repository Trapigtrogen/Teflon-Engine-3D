#include <Shader.h>

namespace engine {
	Shader::Shader() {
		GLuint programObject = glCreateProgram();

		std::string strVertexShader = functions.loadFile(vertexShaderName);
		GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, strVertexShader.c_str());

		std::string strFragmentShader = functions.loadFile(fragmentShaderName);
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
	}
	}

	GLuint Shader::LoadShader(GLenum type, const char *shaderSrc) {
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
}