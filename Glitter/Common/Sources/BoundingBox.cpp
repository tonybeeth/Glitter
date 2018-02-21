#include<BoundingBox.h>
#include<initializer_list>

BoundingBox::BoundingBox() = default;

BoundingBox::BoundingBox(const std::vector<BoundingBox>& boxes) {
    glm::vec3 minPt(FLT_MAX), maxPt(-FLT_MAX);
    for(const BoundingBox& box : boxes) {
        maxPt.x = std::max(maxPt.x, box.topFrontRight.x);
        minPt.x = std::min(minPt.x, box.bottomBackLeft.x);
        minPt.y = std::min(minPt.y, box.bottomBackLeft.y);
        maxPt.y = std::max(maxPt.y, box.topFrontRight.y);
        maxPt.z = std::max(maxPt.z, box.topFrontRight.z);
        minPt.z = std::min(minPt.z, box.bottomBackLeft.z);
    }
    generateFromMaxMinPts(maxPt, minPt);
}

BoundingBox::BoundingBox(const glm::vec3 &maxPt, const glm::vec3 &minPt) {
    generateFromMaxMinPts(maxPt, minPt);
}

void BoundingBox::generateFromMaxMinPts(const glm::vec3 &maxPt, const glm::vec3 &minPt) {
    topBackLeft = glm::vec4(minPt.x, maxPt.y, minPt.z, 1);
    bottomBackLeft = glm::vec4(minPt.x, minPt.y, minPt.z, 1);
    bottomBackRight = glm::vec4(maxPt.x, minPt.y, minPt.z, 1);
    topBackRight = glm::vec4(maxPt.x, maxPt.y, minPt.z, 1);
    topFrontLeft = glm::vec4(minPt.x, maxPt.y, maxPt.z, 1);
    bottomFrontLeft = glm::vec4(minPt.x, minPt.y, maxPt.z, 1);
    bottomFrontRight = glm::vec4(maxPt.x, minPt.y, maxPt.z, 1);
    topFrontRight = glm::vec4(maxPt.x, maxPt.y, maxPt.z, 1);
}

const glm::vec4 &BoundingBox::getTopBackLeft() const {
    return topBackLeft;
}

void BoundingBox::setTopBackLeft(const glm::vec4 &topBackLeft) {
    this->topBackLeft = topBackLeft;
}

const glm::vec4 &BoundingBox::getTopBackRight() const {
    return topBackRight;
}

void BoundingBox::setTopBackRight(const glm::vec4 &topBackRight) {
    this->topBackRight = topBackRight;
}

const glm::vec4 &BoundingBox::getTopFrontLeft() const {
    return topFrontLeft;
}

void BoundingBox::setTopFrontLeft(const glm::vec4 &topFrontLeft) {
    this->topFrontLeft = topFrontLeft;
}

const glm::vec4 &BoundingBox::getTopFrontRight() const {
    return topFrontRight;
}

void BoundingBox::setTopFrontRight(const glm::vec4 &topFrontRight) {
    this->topFrontRight = topFrontRight;
}

const glm::vec4 &BoundingBox::getBottomBackLeft() const {
    return bottomBackLeft;
}

void BoundingBox::setBottomBackLeft(const glm::vec4 &bottomBackLeft) {
    this->bottomBackLeft = bottomBackLeft;
}

const glm::vec4 &BoundingBox::getBottomBackRight() const {
    return bottomBackRight;
}

void BoundingBox::setBottomBackRight(const glm::vec4 &bottomBackRight) {
    this->bottomBackRight = bottomBackRight;
}

const glm::vec4 &BoundingBox::getBottomFrontLeft() const {
    return bottomFrontLeft;
}

void BoundingBox::setBottomFrontLeft(const glm::vec4 &bottomFrontLeft) {
    this->bottomFrontLeft = bottomFrontLeft;
}

const glm::vec4 &BoundingBox::getBottomFrontRight() const {
    return bottomFrontRight;
}

void BoundingBox::setBottomFrontRight(const glm::vec4 &bottomFrontRight) {
    this->bottomFrontRight = bottomFrontRight;
}

BoundingBox BoundingBox::operator*(const glm::mat4 &mat) {
    BoundingBox boundingBox;
    boundingBox.bottomBackLeft = mat * bottomBackLeft;
    boundingBox.bottomFrontLeft = mat * bottomFrontLeft;
    boundingBox.bottomBackRight = mat * bottomBackRight;
    boundingBox.bottomFrontRight = mat * bottomFrontRight;
    boundingBox.topBackLeft = mat * topBackLeft;
    boundingBox.topBackRight = mat * topBackRight;
    boundingBox.topFrontLeft = mat * topFrontLeft;
    boundingBox.topFrontRight = mat * topFrontRight;

    return boundingBox;
}

std::vector<glm::vec4 *> BoundingBox::getVertices() {
    return {&topBackLeft, &topBackRight, &topFrontLeft, &topFrontRight, &bottomBackLeft,
            &bottomBackRight, &bottomFrontLeft, &bottomFrontRight};
}

GLfloat BoundingBox::maxLength() const {
    std::initializer_list<GLfloat> lengths = {std::abs(topBackRight.x-topBackLeft.x),
        std::abs(topBackLeft.y-bottomBackLeft.y), std::abs(topBackLeft.z-topFrontLeft.z)};

    return std::max(lengths);
}

glm::vec3 BoundingBox::center() const {
    return glm::vec3((topBackLeft.x+topBackRight.x)/2, (topBackLeft.y+bottomBackLeft.y)/2, (topBackLeft.z+topFrontLeft.z)/2);
}

BoundingBox::~BoundingBox() = default;


