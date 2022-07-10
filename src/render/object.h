#pragma once

#include "ew.h"
#include "model.h"
#include "texture.h"

class Object
{
    struct Spin
    {
        Vector3 spin_vec;
        float spin_deg;
    };

public:
    Object() {}

    Object(std::string obj_name, std::string model_path, std::string texture_path = "", std::string normal_path = "")
    {
        this->set_name(obj_name);
        this->position = Vector3(0.0f);
        this->scale = Vector3(1.0f);
        this->spin = {Vector3(0.0f), 0.0f};
        this->model = std::make_shared<Model>();
        this->set_model(model_path);
        if (texture_path != "")
            this->set_texture(texture_path);
        if (normal_path != "")
            this->set_texture_norm(normal_path);
    }

    virtual void draw()
    {
        for (auto &m : this->model->meshes)
            glDrawElements(GL_TRIANGLES, m->getIndexCount(), GL_UNSIGNED_INT, 0);
    }

    void bind()
    {
        if (this->texture != 0x0)
        {
            this->texture->bind(0);
        }
        if (this->textureNorm != 0x0)
        {
            this->textureNorm->bind(1);
        }
        for (auto &m : this->model->meshes)
            m->bind();
    }

    void unbind()
    {
        this->texture->unbind(0);
        this->textureNorm->unbind(1);
        for (auto &m : this->model->meshes)
            m->unbind();
    }

    void set_name(std::string name)
    {
        this->name = name;
    }

    std::string get_name()
    {
        return this->name;
    }

    virtual void set_model(const std::string path);

    void set_texture(std::string path)
    {
        this->texture = TextureLoader::getInstance().load(path);
    }

    void set_texture_norm(std::string path)
    {
        this->textureNorm = TextureLoader::getInstance().load(path);
    }

    void set_position(Vector3 pos)
    {
        this->position = pos;
    }

    Vector3 get_position()
    {
        return this->position;
    }

    void set_scale(Vector3 scale)
    {
        this->scale = scale;
    }

    Vector3 get_scale()
    {
        return this->scale;
    }

    void set_rotation(Vector3 spin_vec, float spin_deg)
    {
        if (spin_deg > 360)
            spin_deg = 360;
        else if (spin_deg < -360)
            spin_deg = -360;
        this->spin = {spin_vec, spin_deg};
    }

    Spin get_rotation()
    {
        return this->spin;
    }

protected:
    ew::Id<Object> id;
    std::string name;
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> textureNorm;
    Vector3 position;
    Vector3 scale;
    Spin spin;
    int rotationX;
    int rotationY;
    int rotationZ;
};