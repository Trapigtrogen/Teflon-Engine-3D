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
	public:
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};

		struct Texture {
			unsigned int id;
			std::string type;
			std::string path;
		};

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		unsigned int VAO;
		
		/*  Functions  */
		void Draw(Shader shader);
	private:
		/*  Render data  */
		unsigned int VBO, EBO;
		/*  Functions    */
		void setupMesh();
	};
}