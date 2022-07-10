#pragma once

#include "ew.h"

class VertexArray
{
    ew::Id<VertexArray> id;

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
    ew::Id<VertexBuffer> id;

public:
    VertexBuffer()
    {
        glGenBuffers(1, &id.id);
    }
    void bind(std::vector<ew::Vertex> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id.id);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(ew::Vertex), data.data(), GL_STATIC_DRAW);
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

class IndexBuffer
{
    ew::Id<IndexBuffer> id;

public:
    enum class UsageType : uint8_t
    {
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