#pragma once

// std includes
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

// 3d includes
#include "GL/glew.h"
#include "utils/shaderLoader.h"
#include "math/math.hpp"

namespace ew
{
    template <typename T>
    struct Id
    {
        unsigned id = 0;
    };

    struct Vertex
    {
        Vector3 pos;
        Vector2 uv;
        Vector3 norm;
        Vector3 tangent;
        Vector3 bitangent;
    };
}