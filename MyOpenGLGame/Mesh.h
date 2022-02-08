#pragma once
#include <assimp/types.h>
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"Shader.h"

struct MeshVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	//glm::vec3 Tangent;
	//glm::vec3 Bitangent;
};

struct MeshTexture
{
	GLuint id;
	std::string type;
	aiString Path;
};

class Mesh
{
public:
	GLuint VBO, VAO, EBO;
	std::vector<MeshVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<MeshTexture> textures;

	Mesh(std::vector<MeshVertex> vertices, std::vector<GLuint> indices, std::vector<MeshTexture> textures);
	Mesh(float vertices[]);
	~Mesh();

	void Draw(Shader* shader);

private:

	void SetUpMesh();
};

