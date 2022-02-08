#include "Model.h"
#include"stb_image.h"



unsigned int TextureFromFile(const char* path, const std::string& directory);

void Model::Draw(Shader* shader)
{
	for (auto mesh : meshes)
	{
		mesh.Draw(shader);
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("ERROR: Unable to load model\n");
		return;
	}

	directory = path.substr(0, path.find_last_of('\\'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<MeshVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<MeshTexture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	////Material
	if (mesh->mMaterialIndex >= 0)
	{
	
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<MeshTexture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<MeshTexture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}



std::vector<MeshTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<MeshTexture> textures;
//	std::cout << mat->GetTextureCount(type);
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;

		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (this->textures_loaded[j].Path == str)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{   // if texture hasn't been loaded already, load it
			MeshTexture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.Path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}


//
//std::vector<MeshTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,std::string typeName)
//{
//	std::vector<MeshTexture> textures;
//	std::cout << mat->GetTextureCount(type)<<std::endl;
//	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
//	{
//		
//		aiString str;
//		mat->GetTexture(type, i, &str);
//		GLboolean skip = false;
//
//		for (GLuint j = 0; j < textures_loaded.size(); j++)
//		{
//			if (textures_loaded[j].Path == str)
//			{
//				textures.push_back(textures_loaded[j]);
//				skip = true;
//				break;
//			}
//		}
//
//		if (!skip)
//		{
//			MeshTexture texture;
//			texture.id = TextureFromFile(str.C_Str(), directory);
//			texture.type = typeName;
//			texture.Path = str;
//			textures.push_back(texture);
//			textures_loaded.push_back(texture);
//		}
//	}
//
//	return textures;
//
//}


unsigned int TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '\\' + filename;

	std::cout << filename << std::endl;
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format=GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}