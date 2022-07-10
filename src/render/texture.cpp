#include "texture.h"
#include "stb/stb_image.h"

Texture::Texture()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    id = ew::Id<Texture>{texture};

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind(int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, id.id);
}

void Texture::unbind(int texSlot)
{
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::unique_ptr<TextureLoader> TextureLoader::instance = nullptr;

TextureLoader &TextureLoader::getInstance()
{
    if (instance)
    {
        return *instance;
    }
    instance = std::unique_ptr<TextureLoader>(new TextureLoader());
    return *instance;
}

std::shared_ptr<Texture> TextureLoader::load(std::string path)
{
    stbi_set_flip_vertically_on_load(true);

    const auto texture = new Texture();
    texture->bind(0);
    int width, height, nrChannels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Cant load img" << std::endl;
    }

    stbi_image_free(data);
    texture->unbind(0);
    return std::shared_ptr<Texture>(texture);
}