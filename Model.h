#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include "string"
#include "vector"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


using std::string;
using std::vector;

class Model {
public: 
	Model(const char* path)
	{
		loadModel(path);
	};
	void Draw(Shader &shader);

private:
	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};


#endif