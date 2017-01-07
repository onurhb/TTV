
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

    double mouseX, mouseY;
    bool click = false;

    // - Menu
    std::array<std::string, 3> menuOptions = {"Channels", "Videos", "Settings"};
    std::array<std::string, 5> channels = {"A Haber", "HaberTurk", "NTV", "CNN", "TVNET"};
    int selectedMenuOption = -1;
    int selectedChannelOption = 0;

public:
    UserInterface(GLFWwindow *window);
    ~UserInterface();
    void postRender();
    void preRender();
    void render();
    void update(double mouseX, double mouseY, bool click);
    // ------------------- COMPONENTS
    void drawMenu(NVGcontext *ctx, float x, float y, float w, float h);
    void drawClock(NVGcontext *ctx, float x, float y, float w, float h);
    void drawShadowBg();
    void drawChannelsMenu(NVGcontext *ctx, float x, float y, float w, float h);

    // ------------------- HELPERS
    bool insideRectangle(float rectX, float rectY, float rectW, float rectH);
};


#endif //PROJECT_USERINTERFACE_H
