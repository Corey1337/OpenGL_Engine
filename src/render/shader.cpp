#include "shader.h"

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

void Shader::setUniformInt(std::string name, int number)
{
    glUniform1i(glGetUniformLocation(id.id, name.c_str()), number);
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