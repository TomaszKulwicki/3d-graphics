#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/gl.h>

namespace xe {
    GLuint create_texture(const std::string &name);
}

#endif //TEXTURE_H
