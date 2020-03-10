#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <Functionality.h> 

namespace engine {
	class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

		void use();

		// Shader id
		GLuint id;

		Functionality functions;
	private:
		void checkCompileErrors(GLuint shader, std::string type);
	};
}