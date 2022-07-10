#include "pyramid.h"

void Pyramid::set_model(const std::string path)
{
    this->model->meshes.push_back(new Mesh(this->vertices));
}