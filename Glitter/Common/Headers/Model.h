#ifndef GLITTER_MODEL_H
#define GLITTER_MODEL_H

#include <vector>
#include<memory>
#include<glitter.hpp>
#include<Material.h>
#include<Texture.h>
#include<BoundingBox.h>

class Model {
public:
    Model();

    ~Model();

    const std::vector<glm::vec3> &getVertices() const;

    const std::vector<glm::vec3> &getNormals() const;

    std::shared_ptr<Material> getMaterial() const;

    const std::vector<Texture> &getDiffuseTextures() const;

    const std::vector<glm::vec2> &getUvs() const;

    const BoundingBox &getBoundingBox() const;

    const std::vector<GLuint> &getIndices() const;

    const std::string &getName() const;

    virtual void load(const Program& program);

    virtual void draw(const Program& program, GLenum mode) const;

protected:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<GLuint> indices;
    std::shared_ptr<Material> material;
    std::vector<Texture> diffuseTextures;
    BoundingBox boundingBox;
    std::string name;
    GLuint vertexArrayObject, vertexAttribBuffer, vertexIndicesBuffer;
};

#endif //GLITTER_MODEL_H
