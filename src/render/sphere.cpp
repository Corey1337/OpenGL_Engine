#include "sphere.h"

Sphere::Sphere(std::string obj_name, std::string texture_path, std::string normal_path)
{
    this->set_name(obj_name);
    this->position = Vector3(0.0f);
    this->scale = Vector3(1.0f);
    this->spin = {Vector3(0.0f), 0.0f};
    this->model = std::make_shared<Model>();

    /*const float PI = 3.14f;
    const float phi_step = 0.01;
    const float theta_step = 0.01;
    float r = 1.0f;                                           // constant radius
    for (float phi = -PI / 2; phi < +PI / 2; phi += phi_step) // phi_step ~ 0.01f for example
    {
        for (float theta = 0; theta < +2 * PI; theta += theta_step) // theta _step ~ 0.01f for example
        {
            float x = r * cos(phi) * cos(theta);
            float y = r * sin(phi);
            float z = r * cos(phi) * sin(theta);
            vertices.push_back({Vector3{x, y, z}});
            // generate vertex out of these coordinates
        }
    }*/
    if (texture_path != "")
        this->set_texture(texture_path);
    // if (normal_path != "")
    //     this->set_texture_norm(normal_path);

    int stacks = 20;
    int slices = 20;
    const float PI = 3.14f;

    for (int i = 0; i <= stacks; ++i)
    {
        float V = (float)i / (float)stacks;
        float phi = V * PI;

        for (int j = 0; j <= slices; ++j)
        {

            float U = (float)j / (float)slices;
            float theta = U * (PI * 2);

            float x = cos(theta) * sin(phi);
            float y = cos(phi);
            float z = sin(theta) * sin(phi);
            vertices.push_back({Vector3{x, y, z}});
        }
        for (int i = 0; i < slices * stacks + slices; ++i)
        {
            indices.push_back(GLuint(i));
            indices.push_back(GLuint(i + slices + 1));
            indices.push_back(GLuint(i + slices));

            indices.push_back(GLuint(i + slices + 1));
            indices.push_back(GLuint(i));
            indices.push_back(GLuint(i + 1));
        }
    }
    this->set_model("");
}

void Sphere::set_model(const std::string path)
{
    this->model->meshes.push_back(new Mesh(this->vertices, this->indices, 0));
}