#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb/stb_image.h"
#include <iostream>

namespace engine
{
    class Texture
    {
        public:
            Texture(const char *source);
            void use();
            int get_width();
            int get_height();
            int get_id();
            
        private:
            unsigned int m_id;
            int m_width;
            int m_height;
    };
}

#endif
