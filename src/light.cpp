#include "light.h"

Light::Light()
{
    lightPos = Vector3(0.0f, 0.0f, 5.0f);
    lightAmb = Vector3(0.2f, 0.2f, 0.2f);
    lightDiff = Vector3(0.5f, 0.5f, 0.5f);
    lightSpec = Vector3(1.0f, 1.0f, 1.0f);

    materialSpec = Vector3(0.5f, 0.5f, 0.5f);
    materialShine = 32.0f;
}

void Light::set_pos(Vector3 pos)
{
    lightPos = pos;
}

void Light::render(std::shared_ptr<Shader>* shaderProgram)
{
    auto temp = *shaderProgram;
    
    temp->setUniformInt("material.diffuse", 0);
    temp->setUniformInt("material.normalMap", 1);
    temp->setUniformVec3("material.specular", materialSpec);
    temp->setUniformFloat("material.shininess", materialShine);

    temp->setUniformVec3("light.ambient", lightAmb);
    temp->setUniformVec3("light.diffuse", lightDiff);
    temp->setUniformVec3("light.specular", lightSpec);
    temp->setUniformVec3("light.position", lightPos);
}