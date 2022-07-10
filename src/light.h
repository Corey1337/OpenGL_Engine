#pragma once

#include "render/ew.h"
#include "render/shader.h"

class Light
{
public:
    Light();
    void render(std::shared_ptr<Shader>* shaderProgram);
    void set_pos(Vector3 pos);
    void set_shine(float shine)
    {
        materialShine = shine;
    }
    float get_shine()
    {
        return materialShine;
    }
private:
    Vector3 lightPos;
	Vector3 lightAmb;
	Vector3 lightDiff;
	Vector3 lightSpec;

    Vector3 materialSpec;
    float materialShine;
};