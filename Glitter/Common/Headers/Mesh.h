#ifndef GLITTER_MESH_H
#define GLITTER_MESH_H

#include<vector>
#include<string>

#include<glitter.hpp>
#include<Material.h>
#include<BoundingBox.h>
#include<Model.h>

class Mesh : public Model {
public:
    Mesh(const aiMesh* mesh, const aiMaterial* material);

    ~Mesh();

private:
    std::vector<Texture> getTexturesFromMaterial(const aiMaterial* material, aiTextureType textureType);

};


#endif //GLITTER_MESH_H
