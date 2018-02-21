#include<Mesh.h>
#include<algorithm>

Mesh::Mesh(const aiMesh *mesh, const aiMaterial* material) : Model() {
    name = mesh->mName.data;
    glm::vec3 minBox(FLT_MAX), maxBox(-FLT_MAX);

    aiVector3D v;
    for(int t = 0; t < mesh->mNumVertices; ++t) {
        //Vertices
        v = mesh->mVertices[t];
        vertices.emplace_back(glm::vec3(v.x, v.y, v.z));
        maxBox.x = std::max(maxBox.x, v.x);
        minBox.x = std::min(minBox.x, v.x);
        minBox.y = std::min(minBox.y, v.y);
        maxBox.y = std::max(maxBox.y, v.y);
        maxBox.z = std::max(maxBox.z, v.z);
        minBox.z = std::min(minBox.z, v.z);

        //Normals
        v = mesh->mNormals[t];
        normals.emplace_back(glm::vec3(v.x, v.y, v.z));

        //UVs (
        for(int i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
            if(mesh->mTextureCoords[i]) {
                v = mesh->mTextureCoords[i][t];
                uvs.emplace_back(glm::vec2(v.x, v.y));
            }
        }
    }

    //Indices
    for(int t = 0; t < mesh->mNumFaces; ++t){
        const aiFace* face = &mesh->mFaces[t];
        for(int i = 0; i < face->mNumIndices; ++i) {
            indices.push_back(face->mIndices[i]);
        }
    }

    boundingBox = BoundingBox(maxBox, minBox);
    this->material = std::make_shared<Material>(material);
    diffuseTextures = getTexturesFromMaterial(material, aiTextureType_DIFFUSE);
}

std::vector<Texture> Mesh::getTexturesFromMaterial(const aiMaterial *material, aiTextureType textureType) {
    int textureCount = material->GetTextureCount(textureType);
    aiString texture_path;
    std::vector<Texture> textures;

    for(int i = 0; i < textureCount; ++i) {
        if (material->GetTexture(textureType, i, &texture_path) == AI_SUCCESS) {
            textures.emplace_back(Texture(texture_path.data));
        }
    }
    return textures;
}

Mesh::~Mesh() = default;