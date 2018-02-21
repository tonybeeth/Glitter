#ifndef GLITTER_SHADER_H
#define GLITTER_SHADER_H

#include<string>
#include<glitter.hpp>

class Shader
{
private:
    std::string filename;
    char* readSource(const std::string& filename);
    GLenum extractShaderType(std::string filename);
    GLenum shaderType;
    GLuint shader_ref;

public:
    Shader(const std::string& filename);
    GLuint getReference() const;
    void deleteReference();
    ~Shader();
};
#endif //GLITTER_SHADER_H
