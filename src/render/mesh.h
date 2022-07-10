#pragma once

#include "ew.h"
#include "buffer_manager.h"

class Mesh
{
public:
    Mesh(std::vector<ew::Vertex> &vertices, std::vector<unsigned> &indices, unsigned materialIndex) : vertexCount(static_cast<unsigned>(vertices.size())),
                                                                                                  indicesCount(static_cast<unsigned>(indices.size())),
                                                                                                  materialIndex(materialIndex),
                                                                                                  indices(indices),
                                                                                                  vertices(vertices)
    {
        createBuffers(vertices, indices);
    }
    Mesh(std::vector<ew::Vertex> &vertices) : vertexCount(static_cast<unsigned>(vertices.size())),
                                          indicesCount(0),
                                          materialIndex(0),
                                          vertices(vertices)
    {
        createBuffers(vertices);
    }
    std::vector<ew::Vertex> vertices;
    std::vector<unsigned> indices;
    ~Mesh() = default;

    virtual void bind()
    {
        vertexArray.bind();
    }

    virtual void unbind()
    {
        vertexArray.unbind();
    }

    virtual unsigned getVertexCount()
    {
        return vertexCount;
    }

    virtual unsigned getIndexCount()
    {
        return indicesCount;
    }

    uint32_t getMaterialIndex() const
    {
        return materialIndex;
    }

private:
    void createBuffers(std::vector<ew::Vertex> &p_vertices, std::vector<unsigned> &p_indices);
    void createBuffers(std::vector<ew::Vertex> &p_vertices);

public:
    const unsigned int vertexCount;
    const unsigned int indicesCount;
    const unsigned int materialIndex;

    VertexArray vertexArray;
    std::unique_ptr<VertexBuffer> vertexBuffer;
    std::unique_ptr<IndexBuffer> indexBuffer;
};