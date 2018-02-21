#include<MultiMesh.h>
#include<fstream>

MultiMesh::MultiMesh(const std::string &filePath) {
    loadFile(filePath);
}

bool MultiMesh::loadFile(const std::string &filePath) {
    this->name = filePath;

    Assimp::Importer importer;

    std::ifstream in;
    if(in.fail()){
        fprintf(stderr, "Cannot load MultiMesh: %s\n", filePath.c_str());
        return false;
    }
    const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcessPreset_TargetRealtime_Quality);

    if(!scene) {
        fprintf(stderr, importer.GetErrorString());
        return false;
    }

    std::vector<BoundingBox> boxes;
    for (int idx = 0; idx < scene->mNumMeshes; ++idx) {
        meshes.emplace_back(Mesh(scene->mMeshes[idx], scene->mMaterials[scene->mMeshes[idx]->mMaterialIndex]));
        boxes.push_back(meshes.back().getBoundingBox());
    }
    boundingBox = BoundingBox(boxes);

    importer.FreeScene();
}

void MultiMesh::load(const Program &program) {
    for(Mesh& mesh : meshes) {
        mesh.load(program);
    }
}

void MultiMesh::draw(const Program& program, GLenum mode) const {
    for(const Mesh& mesh : meshes) {
        mesh.draw(program, mode);
    }
}

const std::string &MultiMesh::getName() const {
    return name;
}

const BoundingBox &MultiMesh::getBoundingBox() const {
    return boundingBox;
}

const std::vector<Mesh> &MultiMesh::getMeshes() const {
    return meshes;
}

MultiMesh::~MultiMesh() = default;


