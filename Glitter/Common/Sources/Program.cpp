#include<Program.h>

Program::Program(const std::vector<Shader>& shaders) {
    program_ref = glCreateProgram();
    for(const Shader& shader : shaders) {
        glAttachShader(program_ref, shader.getReference());
    }

    glLinkProgram(program_ref);
    GLint linked;
    glGetProgramiv(program_ref, GL_LINK_STATUS, &linked);
    if(!linked) {
        GLint logSize;
        glGetProgramiv(program_ref, GL_INFO_LOG_LENGTH, &logSize);
        auto logMsg = new char[logSize];
        glGetProgramInfoLog(program_ref, logSize, nullptr, logMsg);
        fprintf(stderr, "Program failed to link %d\n", logSize);
        fprintf(stderr, logMsg);
        delete[] logMsg;

        exit(EXIT_FAILURE);
    }
}

Program::~Program() {
    deleteReference();
}

void Program::use() const {
    glUseProgram(program_ref);
}

GLuint Program::getReference() const {
    return program_ref;
}

void Program::deleteReference() {
    glDeleteProgram(program_ref);
}
