
#ifndef PROJECT_USERINTERFACE_H
#define PROJECT_USERINTERFACE_H
// -------------- INCLUDES
#include "../config.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <string>
#include <array>
#include <vector>

class UserInterface {

    // - NanoVG
    NVGcontext *ctx = nullptr;

    // - Window
    int windowWidth, windowHeight;
    double mouseX, mouseY;
    bool click = false;

    // - Menu
    std::array<std::string, 3> menuOptions = {"Channels", "Videos", "Settings"};
    std::vector<std::string> channels;
    unsigned int selectedMenuOption = 0;
    unsigned int selectedChannelOption = 0;


public:
    UserInterface(int windowWidth, int windowHeight);
    ~UserInterface();
    void postRender();
    void preRender();
    void render();
    void update(double mouseX, double mouseY, bool click, int wWidth, int wHeight);
    unsigned int getActiveChannel() const;

    // ------------------- COMPONENTS
    void drawMenu(NVGcontext *ctx, float x, float y, float w, float h);
    void drawClock(NVGcontext *ctx, float x, float y, float w, float h);
    void drawShadowBg();
    void drawChannelsMenu(NVGcontext *ctx, float x, float y, float w, float h);
    void renderState();
    // ------------------- HELPERS
    bool insideRectangle(float rectX, float rectY, float rectW, float rectH);
    void setChannels(std::vector<std::string> channelNames);
};


#endif //PROJECT_USERINTERFACE_H
