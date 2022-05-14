#include "loader.h"
#include "utils/shaderLoader.h"
#include "stb/stb_image.h"
#include <iostream>

void Shader::bind()
{
    glUseProgram(id.id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::setUniformMat4(std::string name, Mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(id.id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformVec3(std::string name, Vector3 vec)
{
    glUniform3fv(glGetUniformLocation(id.id, name.c_str()), 1, &vec[0]);
}

void Shader::setUniformFloat(std::string name, float number)
{
    glUniform1f(glGetUniformLocation(id.id, name.c_str()), number);
}

std::unique_ptr<ShaderLoader> ShaderLoader::instance = nullptr;

ShaderLoader &ShaderLoader::getInstance()
{
    if (instance)
    {
        return *instance;
    }
    instance = std::unique_ptr<ShaderLoader>(new ShaderLoader());
    return *instance;
}

std::shared_ptr<Shader> ShaderLoader::load(std::string path)
{
    auto _id = LoadShaders(path + ".vs", path + ".fs");
    auto shader = new Shader();
    shader->id.id = _id;
    return std::shared_ptr<Shader>(shader);
}

Texture::Texture()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    id = Id<Texture>{texture};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id.id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::unique_ptr<TextureLoader> TextureLoader::instance = nullptr;

TextureLoader &TextureLoader::getInstance()
{
    if (instance)
    {
        return *instance;
    }
    instance = std::unique_ptr<TextureLoader>(new TextureLoader());
    return *instance;
}

std::shared_ptr<Texture> TextureLoader::load(std::string path)
{
    stbi_set_flip_vertically_on_load(true);

    const auto texture = new Texture();
    texture->bind();
    int width, height, nrChannels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Cant load img" << std::endl;
    }

    stbi_image_free(data);
    texture->unbind();
    return std::shared_ptr<Texture>(texture);
}

// void Mesh::createBuffers(std::vector<Vertex>& p_vertices, std::vector<uint32_t>& p_indices)
// {
//     vertexArray.bind();

//     vertexBuffer = std::make_unique<VertexBuffer>(p_vertices);
//     indexBuffer = std::make_unique<IndexBuffer>(p_indices);

//     uint32_t vertexSize = sizeof(Vertex);
//     vertexBuffer->bind();
//     vertexBuffer->bindAttribute(0, 3, vertexSize, offsetof(Vertex, pos));
//     vertexBuffer->bindAttribute(1, 2, vertexSize, offsetof(Vertex, uv));
//     vertexBuffer->bindAttribute(2, 3, vertexSize, offsetof(Vertex, norm));

//     vertexArray->unbind();
//     vertexBuffer->unbind();


// }