#include<Texture.h>

Texture::Texture(const std::string& imagePath, GLenum texUnit) {
    this->texUnit = texUnit;
    path = imagePath;
}

Texture::~Texture() {
    glDeleteTextures(1, &texId);
}

void Texture::activate(GLint samplerLocation) const {
    glBindTexture(GL_TEXTURE_2D, texId);
    glUniform1i(samplerLocation, texUnit);
}

void Texture::deactivate() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::init() {
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if(image) {
        GLenum format;
        switch (channels)
        {
            case 1 : format = GL_ALPHA;     break;
            case 2 : format = GL_LUMINANCE; break;
            case 3 : format = GL_RGB;       break;
            case 4 : format = GL_RGBA;      break;
        }

        //generate and bind texture Id
        glActiveTexture(texUnit);
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //specify texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, image);

        //glGenerateTextureMipmap(texId);
        stbi_image_free(image);
        deactivate();
        return true;

    }
    else {
        fprintf(stderr, "Failed to Load texture: %s\n", path.c_str());
        return false;
    }
}
