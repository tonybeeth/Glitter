#ifndef GLITTER_MULTIMESH_H
#define GLITTER_MULTIMESH_H

#include<Mesh.h>

class MultiMesh {
public:
    MultiMesh(const std::string& filePath);

    ~MultiMesh();

    bool loadFile(const std::string& filePath);

    void load(const Program& program);

    void draw(const Program& program, GLenum mode) const;

    const std::string &getName() const;

    const BoundingBox &getBoundingBox() const;

    const std::vector<Mesh> &getMeshes() const;

private:
    std::vector<Mesh> meshes;
    std::string name;
    BoundingBox boundingBox;
};

#endif //GLITTER_MULTIMESH_H
