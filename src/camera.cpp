#include "camera.h"

Camera::Camera(Vector3 pos = {}, Vector3 dir = {})
{
    set_position(pos);
    set_direction(dir);
}

void Camera::set_position(Vector3 pos)
{
    this->position = pos;
}

void Camera::set_direction(Vector3 dir)
{
    this->direction = dir;
}

Vector3 Camera::get_position()
{
    return this->position;
}

Vector3 Camera::get_direction()
{
    return this->direction;
}

void Camera::render(std::shared_ptr<Shader>* shaderProgram)
{
    auto temp = *shaderProgram;
    Mat4 view = CreateViewMatrix(position, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    temp->setUniformVec3("viewPos", position);
    temp->setUniformMat4("view", view);
}


