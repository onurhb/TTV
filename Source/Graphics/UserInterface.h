
#ifndef PROJECT_USERINTERFACE_H
#define PROJECT_USERINTERFACE_H
// -------------- INCLUDES
#include "../config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <string>
#include <array>

class UserInterface {

    // - NanoVG
    NVGcontext *ctx = nullptr;

    // - Window
    GLFWwindow *window;


public:
    UserInterface(GLFWwindow *window);
    ~UserInterface();
    void postRender();
    void preRender();
    void render();
    void demo(double x, double y);
};


#endif //PROJECT_USERINTERFACE_H
