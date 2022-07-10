#include "object.h"
#include "utils/assimpParser.h"

void Object::set_model(const std::string path)
{
    EModelParserFlags flags = EModelParserFlags::TRIANGULATE;
    flags |= EModelParserFlags::GEN_SMOOTH_NORMALS;
    flags |= EModelParserFlags::CALC_TANGENT_SPACE;
    AssimpParser().LoadModel(path, this->model, flags);
}