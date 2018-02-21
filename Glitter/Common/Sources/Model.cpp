#include<Model.h>
#include<Layout.h>

Model::Model() = default;

void Model::load(const Program &program) {
    //Get data sizes
    int vertices_size = sizeof(glm::vec3)*vertices.size();
    int normals_size = sizeof(glm::vec3) * normals.size();
    int uv_size = sizeof(glm::vec2) * uvs.size();
    int vertexAttribSize = vertices_size + normals_size + uv_size;
    int indices_size = sizeof(GLuint) * indices.size();

    //Generate vertex array object and buffers
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    //Vertex attributes go in one buffer
    glGenBuffers(1, &vertexAttribBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexAttribBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexAttribSize, nullptr, GL_STATIC_DRAW);
    //Vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices_size, vertices.data());
    glVertexAttribPointer(VERTEX_POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(VERTEX_POSITION_LOC);
    //Normals
    glBufferSubData(GL_ARRAY_BUFFER, vertices_size, normals_size, normals.data());
    glVertexAttribPointer(VERTEX_NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, (void*)vertices_size);
    glEnableVertexAttribArray(VERTEX_NORMAL_LOC);
    //UVs
    glBufferSubData(GL_ARRAY_BUFFER, vertices_size + normals_size, uv_size, uvs.data());
    glVertexAttribPointer(VERTEX_UV_LOC, 2, GL_FLOAT, GL_FALSE, 0, (void*) vertices_size + normals_size);

    glGenBuffers(1, &vertexIndicesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Initialize textures
    for (int i = 0; i < diffuseTextures.size(); i++) {
        if (!diffuseTextures[i].init()){
            diffuseTextures.erase(diffuseTextures.begin()+i);
            --i;
        }
    }
}

void Model::draw(const Program &program, GLenum mode) const {
    program.use();
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndicesBuffer);

    material->load(program);
    //Using only first diffuse texture
    if(!diffuseTextures.empty()) {
        glUniform1i(TEXTURE_ACTIVATE_LOC, true);
        diffuseTextures.begin()->activate(DIFFUSE_TEXTURE_SAMPLER);
        glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);
        diffuseTextures.begin()->deactivate();
    }
    else{
        glUniform1i(TEXTURE_ACTIVATE_LOC, false);
        glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const std::vector<glm::vec3> &Model::getVertices() const {
    return vertices;
}

const std::vector<glm::vec3> &Model::getNormals() const {
    return normals;
}

const std::vector<glm::vec2> &Model::getUvs() const {
    return uvs;
}

const BoundingBox &Model::getBoundingBox() const {
    return boundingBox;
}

const std::vector<GLuint> &Model::getIndices() const {
    return indices;
}

const std::string &Model::getName() const {
    return name;
}

std::shared_ptr<Material> Model::getMaterial() const {
    return material;
}

const std::vector<Texture> &Model::getDiffuseTextures() const {
    return diffuseTextures;
}

Model::~Model() = default;


