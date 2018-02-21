#include<Material.h>
#include<Layout.h>

Material::Material() = default;

Material::Material(const aiMaterial *material) {
    aiReturn success;
    aiColor4D ai4d;
    if(aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &ai4d) == AI_SUCCESS) {
        diffuse = glm::vec3(ai4d.r, ai4d.g, ai4d.b);
    }
    if(aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ai4d) == AI_SUCCESS) {
        ambient = glm::vec3(ai4d.r, ai4d.g, ai4d.b);
    }
    if(aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &ai4d) == AI_SUCCESS) {
        specular = glm::vec3(ai4d.r, ai4d.g, ai4d.b);
    }
    if(aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &ai4d) == AI_SUCCESS) {
        emission = glm::vec3(ai4d.r, ai4d.g, ai4d.b);
    }
    if(aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess) == AI_SUCCESS) {
    }
}

Material::Material(const glm::vec3 &ambient, const glm::vec3 &specular, const glm::vec3 &diffuse,
                   const glm::vec3 &emission, const GLfloat& shininess) : ambient(ambient), specular(specular),
                                                                   diffuse(diffuse), emission(emission),
                                                                   shininess(shininess) {}

void Material::load(const Program &program) {
    program.use();
    glUniform3fv(MATERIAL_AMBIENT_LOC, 1, glm::value_ptr(ambient));
    glUniform3fv(MATERIAL_DIFFUSE_LOC, 1, glm::value_ptr(diffuse));
    glUniform3fv(MATERIAL_SPECULAR_LOC, 1, glm::value_ptr(specular));
    glUniform3fv(MATERIAL_EMISSION_LOC, 1, glm::value_ptr(emission));
    glUniform1f(MATERIAL_SHININESS_LOC, shininess);
}

const glm::vec3 &Material::getAmbient() const {
    return ambient;
}

void Material::setAmbient(const glm::vec3 &ambient) {
    this->ambient = ambient;
}

const glm::vec3 &Material::getSpecular() const {
    return specular;
}

void Material::setSpecular(const glm::vec3 &specular) {
    this->specular = specular;
}

const glm::vec3 &Material::getDiffuse() const {
    return diffuse;
}

void Material::setDiffuse(const glm::vec3 &diffuse) {
    this->diffuse = diffuse;
}

const glm::vec3 &Material::getEmission() const {
    return emission;
}

void Material::setEmission(const glm::vec3 &emission) {
    this->emission = emission;
}

GLfloat Material::getShininess() const {
    return shininess;
}

void Material::setShininess(GLfloat shininess) {
    this->shininess = shininess;
}

Material::~Material() = default;
