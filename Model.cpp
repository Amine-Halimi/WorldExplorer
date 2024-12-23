
#include "Model.h"
#include "Mesh.h"
#include "string"
#include "vector"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/glm.hpp"
#include "stb/stb_image.h"

using std::string;
using std::vector;

vector<Texture> textures_loaded;

unsigned int TextureFromFile(char const* path, string directory);


void Model::Draw(Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(shader);
	}
}

bool inline Model::isModelLoaded()
{
	return isLoaded;
}

void Model::loadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	
	directory = path.substr(0, path.find_last_of('\\'));
	processNode(scene->mRootNode, scene);

	isLoaded = true;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	//Fetches the vertex data
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 tempVector3;
		tempVector3.x = mesh->mVertices[i].x;
		tempVector3.y = mesh->mVertices[i].y;
		tempVector3.z = mesh->mVertices[i].z;
		vertex.position = tempVector3;
		if (mesh->HasNormals())
		{ 
			tempVector3.x = mesh->mNormals[i].x;
			tempVector3.y = mesh->mNormals[i].y;
			tempVector3.z = mesh->mNormals[i].z;
			vertex.normal = tempVector3;
		}
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 tempVector2;
			tempVector2.x = mesh->mTextureCoords[0][i].x;
			tempVector2.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = tempVector2;
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	//Fetches the indices data
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//Fetches material data
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

//Function
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> tempTexturesList;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		
		bool skip = false;

		for (int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				tempTexturesList.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures_loaded.push_back(texture);
			tempTexturesList.push_back(texture);
		}

	}
	return tempTexturesList;
}

unsigned int TextureFromFile(char const* path, string directory)
{
	string filename = string(path);
	filename = directory + '\\' + filename;
	//Creating a OpenGL texture object
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
		{
			format = GL_RED;
		}
		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//Options for the textures wrapping around the S and T axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//Texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		std::cout << "Failed to load texture at path: " << filename << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}