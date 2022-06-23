#pragma once

#include <memory>
#include <math/math.hpp>
#include <GL/glew.h>

template <typename T>
struct Id
{
    unsigned id = 0;
};

class Shader
{
    friend class ShaderLoader;

    Id<Shader> id;
    Shader() {}

public:
    void bind();
    void unbind();
    void setUniformMat4(std::string name, Mat4 mat);
    void setUniformVec3(std::string name, Vector3 vec);
    void setUniformFloat(std::string name, float number);
    void setUniformInt(std::string name, int number);
};

class ShaderLoader
{
public:
    ShaderLoader(ShaderLoader &) = delete;
    ShaderLoader(ShaderLoader &&) = delete;

    static ShaderLoader &getInstance();
    std::shared_ptr<Shader> load(std::string path);

private:
    ShaderLoader() = default;
    static std::unique_ptr<ShaderLoader> instance;
};

class Texture
{
    friend class TextureLoader;

    Id<Texture> id;
    Texture();

public:
    void bind(int texSlot);
    void unbind();
};

class TextureLoader
{
public:
    TextureLoader(TextureLoader &) = delete;
    TextureLoader(TextureLoader &&) = delete;

    static TextureLoader &getInstance();
    std::shared_ptr<Texture> load(std::string path);

private:
    TextureLoader() = default;
    static std::unique_ptr<TextureLoader> instance;
};

struct Vertex
{
    Vector3 pos;
    Vector2 uv;
    Vector3 norm;
    Vector3 tangent;
    Vector3 bitangent;
};

class VertexArray
{
    Id<VertexArray> id;

public:
    VertexArray()
    {
        glGenVertexArrays(1, &id.id);
    }
    void bind()
    {
        glBindVertexArray(id.id);
    }
    void unbind()
    {
        glBindVertexArray(0);
    }
};

class VertexBuffer
{
    Id<VertexBuffer> id;

public:
    VertexBuffer()
    {
        glGenBuffers(1, &id.id);
    }
    void bind(std::vector<Vertex> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id.id);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW);
    }
    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void bindAttribute(int index, int size, int vertSize, intptr_t offset)
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, vertSize, (void *)(intptr_t)offset);
        glEnableVertexAttribArray(index);
    }

        void unbindAttribure()
    {
        glDisableVertexAttribArray(0);
    }
};

class IndexBuffer {
    Id<IndexBuffer> id;

public:
    enum class UsageType : uint8_t{
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_COPY,
    };
    std::vector<GLenum> UsageTypeToEnum = {
        GL_STREAM_DRAW,
        GL_STREAM_READ,
        GL_STREAM_COPY,
        GL_STATIC_DRAW,
        GL_STATIC_READ,
        GL_STATIC_COPY,
        GL_DYNAMIC_DRAW,
        GL_DYNAMIC_READ,
        GL_DYNAMIC_COPY,
    };

    IndexBuffer()
    {
        glGenBuffers(1, &id.id);
    }
    void bind(std::vector<unsigned> &data)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id.id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
    }
    void unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

};

class Mesh
{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned>& indices, unsigned materialIndex):
    vertexCount(static_cast<unsigned>(vertices.size())),
    indicesCount(static_cast<unsigned>(vertices.size())),
    materialIndex(materialIndex),
    indices(indices),
    vertices(vertices)
    {
        createBuffers(vertices, indices);
    }
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    ~Mesh() = default;

    virtual void bind() {
        vertexArray.bind();
    }

    virtual void unbind() {
        vertexArray.unbind();
    }

    virtual unsigned getVertexCount() {
        return vertexCount;
    }

    virtual unsigned getIndexCount() {
        return indicesCount;
    }

    uint32_t getMaterialIndex() const {
        return materialIndex;
    }

private:
    void createBuffers(std::vector<Vertex>& p_vertices, std::vector<unsigned>& p_indices);

public:
    const unsigned int vertexCount;
    const unsigned int indicesCount;
    const unsigned int materialIndex;

    VertexArray vertexArray;
    // VertexBuffer vertexBuffer;
    // IndexBuffer indexBuffer;
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;
};

class Model
{
public:
    std::vector<Mesh*> meshes;
    std::vector<std::string> materialNames;
};