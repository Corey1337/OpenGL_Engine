#pragma once

#include "ew.h"
#include "object.h"

class Pyramid : public Object
{
public:
    Pyramid(std::string obj_name, std::string texture_path = "", std::string normal_path = "")
    {
        this->set_name(obj_name);
        this->position = Vector3(0.0f);
        this->scale = Vector3(1.0f);
        this->spin = {Vector3(0.0f), 0.0f};
        this->model = std::make_shared<Model>();
        this->set_model("");
        if (texture_path != "")
            this->set_texture(texture_path);
        // if (normal_path != "")
        //     this->set_texture_norm(normal_path);
    }

    void set_model(const std::string path) override;
    void draw() override
    {
        for (auto &m : this->model->meshes)
            glDrawArrays(GL_TRIANGLES, 0, m->getVertexCount());
    }

private:
    std::vector<ew::Vertex> vertices = {
        ew::Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
        ew::Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, -1.0f)},

        ew::Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
        ew::Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(0.0f, 0.0f, 1.0f)},

        ew::Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},
        ew::Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f)},

        ew::Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},
        ew::Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(1.0f, 0.0f, 0.0f)},

        ew::Vertex{Vector3(0.5f, -0.5f, -0.5f), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},
        ew::Vertex{Vector3(0.5f, -0.5f, 0.5f), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)},

        ew::Vertex{Vector3(-0.5f, -0.5f, 0.5f), Vector2(0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)},
        ew::Vertex{Vector3(-0.5f, -0.5f, -0.5f), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)},
        ew::Vertex{Vector3(0.0f, 0.5f, 0.0f), Vector2(0.5f, 1.0f), Vector3(0.0f, 1.0f, 0.0f)}};
};