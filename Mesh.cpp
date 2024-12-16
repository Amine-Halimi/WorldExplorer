
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "string"
#include "vector"
#include "Shader.h"
#include "Mesh.h"

using std::string;
using std::vector;
/*
* Constructor
*/
Mesh::Mesh(vector<Vertex> inputVertices, vector<unsigned int> inputIndices, vector<Texture> inputTextures)
{
	this->vertices = inputVertices;
	this->indices = inputIndices;
	this->textures = inputTextures;

	setupMesh();
}

/*
*  Draw function to draw the mesh on the screen.
*/
void Mesh::draw(Shader shader)
{
	unsigned int diffuseLayerNum = 1;
	unsigned int specularLayerNum = 1;

	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		
		string number;
		string name = textures[i].type;

		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseLayerNum++);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularLayerNum++);
		}
		
		string variable = name + number;
		shader.setInt(variable, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
/* 
* Set ups VBO, VAO and EBO and defines
*/
void Mesh::setupMesh()
{
	//Generate an object for VAO, VBO and EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	//Loading vertex data into the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//Loading indices data into the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Defining how to read the data to the VBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoords)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}