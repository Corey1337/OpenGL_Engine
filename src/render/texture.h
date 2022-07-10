#pragma once

#include "ew.h"

class Texture
{
    friend class TextureLoader;

    ew::Id<Texture> id;
    Texture();

public:
    void bind(int texSlot);
    void unbind(int texSlot);
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