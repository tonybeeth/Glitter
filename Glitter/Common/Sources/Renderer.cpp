#include<Renderer.h>

Renderer::Renderer(int width, int height, const std::string& title, const glm::vec4& backGroundColor) :
        width(width), height(height), title(title), backGroundColor(backGroundColor), frame(0), timebase(0) {

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    // Check for Valid Context
    if (!window) {
        fprintf(stderr, "Failed to Create OpenGL Context: %s", title.c_str());
        exit(EXIT_FAILURE);
    }
}

void Renderer::makeCurrentContext() {
    glfwMakeContextCurrent(window);
}

void Renderer::prepare() {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Background Fill Color
    glClearColor(backGroundColor.r, backGroundColor.g, backGroundColor.b, backGroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    ++frame;
    double curTime = glfwGetTime();
    if (curTime - timebase > 1000) {
        double fps = frame*1000.0 / (curTime - timebase);
        std::string title = this->title + ". FPS: " + std::to_string(fps);
        glfwSetWindowTitle(window, title.c_str());
        timebase = curTime;
        frame = 0;
    }
}

int Renderer::getWidth() const {
    return width;
}

int Renderer::getHeight() const {
    return height;
}

const std::string &Renderer::getTitle() const {
    return title;
}

const glm::vec4 &Renderer::getBackGroundColor() const {
    return backGroundColor;
}

void Renderer::setBackGroundColor(const glm::vec4 &backGroundColor) {
    Renderer::backGroundColor = backGroundColor;
}

void Renderer::pollEvents() {
    glfwPollEvents();
}

void Renderer::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Renderer::shouldClose() const {
    return glfwWindowShouldClose(window);
}

GLFWwindow *Renderer::getWindow() const {
    return window;
}

void Renderer::close() const {
    glfwSetWindowShouldClose(window, true);
}

void Renderer::setTitle(const std::string &title) {
    this->title = title;
}

void Renderer::setFrameBufferSizeCallback(GLFWframebuffersizefun glfWframebuffersizefun) {
    glfwSetFramebufferSizeCallback(window, glfWframebuffersizefun);
}

void Renderer::setKeyboardCallback(GLFWkeyfun glfWkeyfun) {
    glfwSetKeyCallback(window, glfWkeyfun);
}

Renderer::~Renderer() {
    glfwDestroyWindow(window);
}


