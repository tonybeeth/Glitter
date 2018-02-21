#define GLM_SWIZZLE
// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include<Program.h>
#include <BoundingBox.h>
#include <Material.h>
#include <MultiMesh.h>
#include<Layout.h>
#include<Renderer.h>
#include <iostream>

#define EXPAND_MACRO(macro) EXPAND_MACRO_2(macro)
#define EXPAND_MACRO_2(macro) #macro

#ifdef PROJECT_SOURCE_DIR
    const std::string PROJECT_DIRECTORY = EXPAND_MACRO(PROJECT_SOURCE_DIR);
#endif

#ifdef SHADERS_DIR
    const std::string SHADERS_DIRECTORY = EXPAND_MACRO(SHADERS_DIR);
#endif

std::shared_ptr<Program> program(nullptr);
std::shared_ptr<Renderer> renderer(nullptr);
std::shared_ptr<MultiMesh> multiMesh(nullptr);

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);

void keyBoardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

std::string getShaderPath(const std::string& file_name);

std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

std::ostream& operator<<(std::ostream& os, const glm::vec4& v);

void init();

void display();

int main(int argc, char * argv[]) {
    // Load GLFW and Create a Window
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create Context and Load OpenGL Functions
    renderer.reset(new Renderer(mWidth, mHeight, "OpenGL"));
    renderer->makeCurrentContext();
    renderer->setFrameBufferSizeCallback(frameBufferSizeCallback);
    renderer->setKeyboardCallback(keyBoardCallback);

    gladLoadGL();

    fprintf(stderr, "OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    glEnable(GL_DEPTH_TEST);

    init();

    // Rendering Loop
    while (!renderer->shouldClose()) {
        renderer->prepare();

        display();

        glfwPollEvents();
        // Flip Buffers
        renderer->swapBuffers();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void display() {
    multiMesh->draw(*program, GL_TRIANGLES);
}

void init() {
    //program = new Program({getShaderPath("basic.vert"), getShaderPath("basic.frag")});
    program.reset(new Program({getShaderPath("learnopengl.vert"), getShaderPath("learnopengl.frag")}));

    multiMesh.reset(new MultiMesh("C:\\Users\\Tonybeeth\\Desktop\\model1\\model.obj"));
    multiMesh->load(*program);

    program->use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)mWidth/mHeight, 0.1f, 20.0f);
    glm::mat4 m = glm::lookAt({0,0,3.0}, multiMesh->getBoundingBox().center(), {0,1,0});
    glm::mat4 t = glm::translate(glm::mat4(1.0), {0, 0, 1.5});

    glUniformMatrix4fv(MODEL_VIEW_MATRIX_LOC, 1, GL_FALSE, glm::value_ptr(m));
    glUniformMatrix4fv(TRANSFORMATION_MATRIX_LOC, 1, GL_FALSE, glm::value_ptr(t));
    glUniformMatrix4fv(PROJECTION_MATRIX_LOC, 1, GL_FALSE, glm::value_ptr(projection));
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 20.0f);
    glUniformMatrix4fv(PROJECTION_MATRIX_LOC, 1, GL_FALSE, glm::value_ptr(projection));
}

void keyBoardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_ENTER:
                break;
        }
    }
}

std::string getShaderPath(const std::string& file_name) {
    return SHADERS_DIRECTORY + "/" + file_name;
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
    os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
    return os;
}