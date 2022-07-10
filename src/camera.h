#pragma once

#include "render/ew.h"
#include "render/shader.h"

class Camera
{
public:

    Camera(Vector3 pos, Vector3 dir);

    void set_position(Vector3 pos);
    void set_direction(Vector3 dir);

    Vector3 get_position();
    Vector3 get_direction();

    void render(std::shared_ptr<Shader>* shaderProgram);

private:

    Vector3 position;
    Vector3 direction;
};