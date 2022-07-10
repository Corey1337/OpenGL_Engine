#pragma once

#include "ew.h"
#include "object.h"

class Sphere : public Object
{
public:
    Sphere(std::string obj_name, std::string texture_path = "", std::string normal_path = "");

    void set_model(const std::string path) override;
    void draw() override
    {
        for (auto &m : this->model->meshes)
            glDrawElements(GL_TRIANGLES, m->getIndexCount(), GL_UNSIGNED_INT, 0);
            // glDrawArrays(GL_TRIANGLES, 0, m->getVertexCount());
    }
private:
    std::vector<ew::Vertex> vertices;
    std::vector<unsigned> indices;
};