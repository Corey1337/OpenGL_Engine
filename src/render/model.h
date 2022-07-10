#pragma once

#include "mesh.h"

class Model
{
public:
    std::vector<Mesh *> meshes;
    std::vector<std::string> materialNames;
};