#ifndef GLITTER_BOUNDINGBOX_H
#define GLITTER_BOUNDINGBOX_H

#include <glitter.hpp>
#include<vector>

class BoundingBox {

public:
    BoundingBox();

    BoundingBox(const std::vector<BoundingBox>& boxes);

    BoundingBox(const glm::vec3& maxPt, const glm::vec3& minPt);

    ~BoundingBox();

    BoundingBox operator*(const glm::mat4& mat);

    GLfloat maxLength() const;

    glm::vec3 center() const;

    const glm::vec4 &getTopBackLeft() const;

    void setTopBackLeft(const glm::vec4 &topBackLeft);

    const glm::vec4 &getTopBackRight() const;

    void setTopBackRight(const glm::vec4 &topBackRight);

    const glm::vec4 &getTopFrontLeft() const;

    void setTopFrontLeft(const glm::vec4 &topFrontLeft);

    const glm::vec4 &getTopFrontRight() const;

    void setTopFrontRight(const glm::vec4 &topFrontRight);

    const glm::vec4 &getBottomBackLeft() const;

    void setBottomBackLeft(const glm::vec4 &bottomBackLeft);

    const glm::vec4 &getBottomBackRight() const;

    void setBottomBackRight(const glm::vec4 &bottomBackRight);

    const glm::vec4 &getBottomFrontLeft() const;

    void setBottomFrontLeft(const glm::vec4 &bottomFrontLeft);

    const glm::vec4 &getBottomFrontRight() const;

    void setBottomFrontRight(const glm::vec4 &bottomFrontRight);

private:
    glm::vec4 topBackLeft, topBackRight, topFrontLeft, topFrontRight, bottomBackLeft,
            bottomBackRight, bottomFrontLeft, bottomFrontRight;

    std::vector<glm::vec4*> getVertices();

    void generateFromMaxMinPts(const glm::vec3 &maxPt, const glm::vec3 &minPt);
};


#endif //GLITTER_BOUNDINGBOX_H
