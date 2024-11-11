#ifndef MESH_H
#define MESH_H
/*
* This file contains the declaration of the class Mesh and the structs Vertex and Texture.
* The role of this class is to hold the data loaded and drawing the respective mesh.
*/
#include "glm.hpp"
#include "string"
#include "vector"
#include "Shader.h"

using std::string;
using std::vector;


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
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
	~Mesh();
	Mesh(vector<Vertex> inputVertices, vector<unsigned int> inputIndices, vector<Texture> inputTextures);
	void draw(Shader shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif // !MESH_H