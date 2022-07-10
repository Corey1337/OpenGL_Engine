#pragma once

#include "ew.h"

class Shader
{
    friend class ShaderLoader;

    ew::Id<Shader> id;
    Shader() {}

public:
    void bind();
    void unbind();
    void setUniformMat4(std::string name, Mat4 mat);
    void setUniformVec3(std::string name, Vector3 vec);
    void setUniformFloat(std::string name, float number);
    void setUniformInt(std::string name, int number);
};

class ShaderLoader
{
public:
    ShaderLoader(ShaderLoader &) = delete;
    ShaderLoader(ShaderLoader &&) = delete;

    static ShaderLoader &getInstance();
    std::shared_ptr<Shader> load(std::string path);

private:
    ShaderLoader() = default;
    static std::unique_ptr<ShaderLoader> instance;
};