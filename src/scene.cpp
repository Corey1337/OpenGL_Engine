#include "scene.h"

#include "render/shader.h"

Scene::Scene()
{

    objects = std::make_shared<std::vector<Object *>>();
    
    camera = std::make_shared<Camera>(Vector3(3.0f), Vector3(0.0f));
    light = std::make_shared<Light>();
    shaderProgram = ShaderLoader::getInstance().load(".\\res\\shaders\\shader");
}

void Scene::render()
{
    shaderProgram->bind();

    Mat4 proj = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    shaderProgram->setUniformMat4("projection", proj);

    light->render(&shaderProgram);
    camera->render(&shaderProgram);

    for (auto &obj_ : *objects)
    {
        obj_->bind();
        Mat4 translation = translationMat(obj_->get_position());
        Mat4 rotation = rotateMat(obj_->get_rotation().spin_vec, radians(obj_->get_rotation().spin_deg));
        Mat4 scale = scaleMat(obj_->get_scale());
        Mat4 model = CraeteModelMatrix(translation, rotation, scale);
        shaderProgram->setUniformMat4("model", model);
        obj_->draw();
        obj_->unbind();
    }

    shaderProgram->unbind();
}