#ifndef MESH_H
#define MESH_H
/*
* This file contains the declaration of the class Mesh and the structs Vertex and Texture.
* The role of this class is to hold the data loaded and drawing the respective mesh.
* Implementation from LearnOpenGL website:https://github.com/JoeyDeVries/LearnOpenGL
*/
#include "glm\glm.hpp"
#include "string"
#include "vector"
#include "Shader.h"

using std::string;
using std::vector;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> inputVertices, vector<unsigned int> inputIndices, vector<Texture> inputTextures);
	void draw(Shader shader);

private:
	unsigned int VBO, EBO;
	void setupMesh();
};

#endif // !MESH_H
