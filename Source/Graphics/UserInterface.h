
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

    // - Menu
    std::array<std::string,3> menuOptions = {"Channels", "Videos", "Settings"};


public:
    UserInterface(GLFWwindow *window);
    ~UserInterface();
    void postRender();
    void preRender();
    void render();

    // ------------------- COMPONENTS
    void drawMenu(NVGcontext* ctx, float x, float y, float w, float h);
    void drawClock(NVGcontext* ctx, float x, float y, float w, float h);
};


#endif //PROJECT_USERINTERFACE_H
