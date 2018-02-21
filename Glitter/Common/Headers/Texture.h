#ifndef GLITTER_TEXTURE_H
#define GLITTER_TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION

#include<glitter.hpp>

class Texture {
public:
    Texture(const std::string& imagePath, GLenum texUnit = GL_TEXTURE0);

    ~Texture();

    bool init();

    void activate(GLint samplerLocation) const;

    void deactivate() const;

private:
    int width, height, channels;
    GLuint texUnit, texId;
    std::string path;
};


#endif //GLITTER_TEXTURE_H
