#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <Functionality.h> 

namespace engine {
	class Shader {
		
	public:
		Shader(const std::string vertexShaderName, const std::string fragmentShaderName);
		~Shader();

		GLuint LoadShader(GLenum type, const char *shaderSrc);
		Functionality functions;
	};
}