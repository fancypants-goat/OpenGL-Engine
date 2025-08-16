#include "texture.h"

namespace engine
{
    Texture::Texture(const char *source)
        : m_width(-1)
        , m_height(-1)
        , m_id(-1)
    {
        // generate the texture id and bind it
        glGenTextures(1, &m_id);
        use();
        
        // set the texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        
        // load the texture data
        stbi_set_flip_vertically_on_load(true);  
        int nrChannels;
        unsigned char *data = stbi_load(source, &m_width, &m_height, &nrChannels, 0);
        
        if (data)
        {    // generate the texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load texture" << std::endl;
        }
        
        // free up image memory
        stbi_image_free(data);
    }

    void Texture::use()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
    
    int Texture::get_width()
    {
        return m_width;
    }
    int Texture::get_height()
    {
        return m_height;
    }
    int Texture::get_id()
    {
        return m_id;
    }
}
