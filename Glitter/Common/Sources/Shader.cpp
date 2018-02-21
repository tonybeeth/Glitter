#include<Shader.h>
#include<fstream>

Shader::Shader(const std::string& filename) {
    this->filename = filename;
    char* source = readSource(filename);
    if(!source) {
        fprintf(stderr, "Failed to read Shader source: %s\n", filename.c_str());
        exit(EXIT_FAILURE);
    }

    shaderType = extractShaderType(filename);
    shader_ref = glCreateShader(shaderType);
    glShaderSource(shader_ref, 1, (const GLchar**)&source, nullptr);
    glCompileShader(shader_ref);

    GLint compiled;
    glGetShaderiv(shader_ref, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint logSize;
        glGetShaderiv(shader_ref, GL_INFO_LOG_LENGTH, &logSize);
        auto logMsg = new char[logSize];
        glGetShaderInfoLog(shader_ref, logSize, nullptr, logMsg);
        fprintf(stderr, "Failed to compile shader: %s\n", filename.c_str());
        fprintf(stderr, logMsg);
        delete[] logMsg;

        exit(EXIT_FAILURE);
    }

    delete[] source;
}

Shader::~Shader() {
    deleteReference();
}

GLenum Shader::extractShaderType(std::string filename){
    std::string file_ext = filename.substr(filename.find_last_of('.') + 1);
    if (file_ext == "vert"){
        return GL_VERTEX_SHADER;
    }
    else if (file_ext == "frag") {
        return GL_FRAGMENT_SHADER;
    }
    else if (file_ext == "comp") {
        return GL_COMPUTE_SHADER;
    }
    else if (file_ext == "geom") {
        return GL_GEOMETRY_SHADER;
    }
    else {
        fprintf(stderr, "Cannot Determine shader type for %s\n", filename.c_str());
        exit(EXIT_FAILURE);
    }
}

char * Shader::readSource(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile)
        return nullptr;

    std::string str;

    infile.seekg(0, std::ios::end);
    str.reserve(infile.tellg());
    infile.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(infile)),
               std::istreambuf_iterator<char>());

    auto buf = new char[str.size()+1];
    strcpy(buf, str.c_str());
    buf[str.size()] = '\0';
    return buf;
}

GLuint Shader::getReference() const {
    return shader_ref;
}

void Shader::deleteReference() {
    glDeleteShader(shader_ref);
}
