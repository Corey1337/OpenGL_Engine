#pragma once

#include "ew.h"
#include "object.h"
#include "camera.h"
#include "shader.h"
#include "cube.h"
#include "pyramid.h"
#include "sphere.h"
#include "light.h"

class Scene
{
public:
    Scene();

    void render();

    std::shared_ptr<std::vector<Object *>> get_objects()
    {
        return objects;
    }

    std::shared_ptr<Light> get_light()
    {
        return light;
    }

    std::shared_ptr<Camera> get_camera()
    {
        return camera;
    }

private:
    std::shared_ptr<std::vector<Object *>> objects;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Shader> shaderProgram;
    std::shared_ptr<Light> light;
    // shader...
};