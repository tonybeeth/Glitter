#ifndef GLITTER_PROGRAM_H
#define GLITTER_PROGRAM_H

#include<vector>
#include<string>
#include<Shader.h>
#include<glitter.hpp>

class Program {
private:
    GLuint program_ref;
public:
    Program(const std::vector<Shader>& shaders);
    void use() const;
    GLuint getReference() const;
    void deleteReference();
    ~Program();
};


#endif //GLITTER_PROGRAM_H
