#ifndef GLITTER_MATERIAL_H
#define GLITTER_MATERIAL_H

#include<vector>
#include<string>
#include<glitter.hpp>
#include<Program.h>

class Material {

public:
    Material();

    Material(const aiMaterial* material);

    Material(const glm::vec3& ambient, const glm::vec3& specular, const glm::vec3& diffuse,
             const glm::vec3& emission, const GLfloat& shininess);

    ~Material();

    void load(const Program& program);

    const glm::vec3 &getAmbient() const;

    void setAmbient(const glm::vec3 &ambient);

    const glm::vec3 &getSpecular() const;

    void setSpecular(const glm::vec3 &specular);

    const glm::vec3 &getDiffuse() const;

    void setDiffuse(const glm::vec3 &diffuse);

    const glm::vec3 &getEmission() const;

    void setEmission(const glm::vec3 &emission);

    GLfloat getShininess() const;

    void setShininess(GLfloat shininess);

private:
    glm::vec3 ambient, specular, diffuse, emission;
    GLfloat shininess;
};

#endif //GLITTER_MATERIAL_H
