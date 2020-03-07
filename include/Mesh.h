#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>

namespace engine {
	class Mesh {
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

		struct Texture {
			unsigned int id;
			std::string type;
		};
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh(); 
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		/*  Functions  */
		void Draw(Shader shader);
	private:
		/*  Render data  */
		unsigned int VAO, VBO, EBO;
		/*  Functions    */
		void setupMesh();
	};
}