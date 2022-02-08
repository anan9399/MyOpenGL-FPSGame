#include "Mesh.h"
const char* DIFFUSE_TEX_NAME = "texture_diffuse";
const char* SPECULAR_TEX_NAME = "texture_specular";
const char* NORMAL_TEX_NAME = "texture_normal";
const char* HEIGHT_TEX_NAME = "texture_height";

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<GLuint> indices, std::vector<MeshTexture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetUpMesh();
}

Mesh::Mesh(float vertices[])
{
    this->vertices.resize(36);
    memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));

    SetUpMesh();
}

Mesh::~Mesh()
{
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    //glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw(Shader* shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == DIFFUSE_TEX_NAME)
            number = std::to_string(diffuseNr++);
        else if (name == SPECULAR_TEX_NAME)
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == NORMAL_TEX_NAME)
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == HEIGHT_TEX_NAME)
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        shader->setUniform1i((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
  //  glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetUpMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(3*sizeof(GL_FLOAT)));
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(6 * sizeof(GL_FLOAT)));
    //// vertex tangent
    //glEnableVertexAttribArray(3);
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Tangent));
    //// vertex bitangent
    //glEnableVertexAttribArray(4);
    //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Bitangent));

    glBindVertexArray(0);

}