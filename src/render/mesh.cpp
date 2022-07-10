#include "mesh.h"

#include <vector>

void Mesh::createBuffers(std::vector<ew::Vertex>& p_vertices, std::vector<unsigned>& p_indices)
{
    vertexArray.bind();

    vertexBuffer = std::make_unique<VertexBuffer>();
    indexBuffer = std::make_unique<IndexBuffer>();

    uint32_t vertexSize = sizeof(ew::Vertex);

    vertexBuffer->bind(p_vertices);
    indexBuffer->bind(p_indices);

    vertexBuffer->bindAttribute(0, 3, vertexSize, offsetof(ew::Vertex, pos));
    vertexBuffer->bindAttribute(1, 2, vertexSize, offsetof(ew::Vertex, uv));
    vertexBuffer->bindAttribute(2, 3, vertexSize, offsetof(ew::Vertex, norm));
    vertexBuffer->bindAttribute(3, 3, vertexSize, offsetof(ew::Vertex, tangent));
    vertexBuffer->bindAttribute(4, 3, vertexSize, offsetof(ew::Vertex, bitangent));

    vertexArray.unbind();
    vertexBuffer->unbind();
    vertexBuffer->unbindAttribure();
    indexBuffer->unbind();
}

void Mesh::createBuffers(std::vector<ew::Vertex>& p_vertices)
{
    vertexArray.bind();

    vertexBuffer = std::make_unique<VertexBuffer>();

    uint32_t vertexSize = sizeof(ew::Vertex);

    vertexBuffer->bind(p_vertices);

    vertexBuffer->bindAttribute(0, 3, vertexSize, offsetof(ew::Vertex, pos));
    vertexBuffer->bindAttribute(1, 2, vertexSize, offsetof(ew::Vertex, uv));
    vertexBuffer->bindAttribute(2, 3, vertexSize, offsetof(ew::Vertex, norm));
    vertexBuffer->bindAttribute(3, 3, vertexSize, offsetof(ew::Vertex, tangent));
    vertexBuffer->bindAttribute(4, 3, vertexSize, offsetof(ew::Vertex, bitangent));

    vertexArray.unbind();
    vertexBuffer->unbind();
    vertexBuffer->unbindAttribure();
}