#ifndef GLITTER_RENDERER_H
#define GLITTER_RENDERER_H

#include<glitter.hpp>
#include <GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>

class Renderer {
public:
    Renderer(int width, int height, const std::string& title = "OpenGL", const glm::vec4& backGroundColor = {0.25, 0.25, 0.25, 1.0});

    void makeCurrentContext();

    void prepare();

    void swapBuffers();

    void pollEvents();

    int getWidth() const;

    int getHeight() const;

    const std::string &getTitle() const;

    void setTitle(const std::string &title);

    const glm::vec4 &getBackGroundColor() const;

    void setBackGroundColor(const glm::vec4 &backGroundColor);

    GLFWwindow *getWindow() const;

    bool shouldClose() const;

    void close() const;

    void setFrameBufferSizeCallback(GLFWframebuffersizefun glfWframebuffersizefun);

    void setKeyboardCallback(GLFWkeyfun glfWkeyfun);

    virtual ~Renderer();

private:
    int width;
    int height;
    std::string title;
    glm::vec4 backGroundColor;
    GLFWwindow* window;
    double timebase;
    int frame;
};

#endif //GLITTER_RENDERER_H
