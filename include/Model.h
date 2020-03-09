#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

namespace engine {
	class Model {
	public:
		/*  Functions   */
		Model(char *path);

		/*  Model Data  */
		std::vector<Mesh::Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;

		void Draw(Shader shader);
	private:
		/*  Functions   */
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Mesh::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
		unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = 0);
	};
}