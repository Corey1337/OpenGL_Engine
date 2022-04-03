#include <memory>
#include <math/math.hpp>

struct Id {
    unsigned int id;
};

class Shader{
    public:
        //Id id;
        Id id;
        Shader(Id id_);
        //Shader(Id _id): id(id) {}
        void bind();
        void unbind();
        void setUniformMat4(std::string name, Mat4 mat);
};

class ShaderLoader{
    public:
        ShaderLoader(ShaderLoader&) = delete;
        ShaderLoader(ShaderLoader&&) = delete;

        static ShaderLoader& getInstance();
        Shader load(std::string path);

    private:
        ShaderLoader() = default;
        static std::unique_ptr<ShaderLoader> instance;

};