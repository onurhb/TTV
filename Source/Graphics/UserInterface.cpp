#define NANOVG_GL3_IMPLEMENTATION
// -------------- INCLUDES
#include <chrono>
#include <iostream>
#include "UserInterface.h"
#include "nanovg_gl.h"


UserInterface::UserInterface(GLFWwindow *window) {
    // - Window
    this->window = window;

    // - NanoVG
    ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    nvgCreateFont(ctx, "system", "Ubuntu-M.ttf");

}

UserInterface::~UserInterface() {
    nvgDeleteGL3(ctx);
}

void UserInterface::preRender() {
    nvgBeginFrame(ctx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH / WINDOW_HEIGHT);
}

void UserInterface::postRender() {
    nvgEndFrame(ctx);
}

void UserInterface::render() {

    drawShadowBg();
    drawMenu(ctx, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, 100);
    drawClock(ctx, WINDOW_WIDTH - 265, WINDOW_HEIGHT - 100, 215, 50);

    if(selectedMenuOption > -1) drawChannelsMenu(ctx, WINDOW_WIDTH / 2 - 300, 65, 600, 325);

}

void UserInterface::update(double mouseX, double mouseY, bool click) {
    this->mouseY = mouseY;
    this->mouseX = mouseX;
    this->click = click;
}

// ------------------------------------------ COMPONENTS

void UserInterface::drawMenu(NVGcontext *ctx, float x, float y, float w, float h) {

    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y, x, y + h / 5, nvgRGBA(40, 45, 50, 250), nvgRGBA(10, 10, 15, 250));
    nvgBeginPath(ctx);
    nvgRect(ctx, x, y, w, h);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Outline
    nvgBeginPath(ctx);
    nvgRect(ctx, x + 0.5f, y + 0.5f, w - 1, h - 1);
    nvgStrokeWidth(ctx, 2);
    nvgStrokeColor(ctx, nvgRGB(0, 0, 0));
    nvgStroke(ctx);

    // - Menu options
    x += WINDOW_WIDTH / 6;
    y += h / 2;
    for (int i = 0; i < menuOptions.size(); ++i) {
        if (insideRectangle(x, y - 20, 150, 45) && click) selectedMenuOption = i;

        nvgFontSize(ctx, 36.0f);
        nvgFillColor(ctx,
                     selectedMenuOption == i ? nvgRGBA(255, 182, 38, 255) : nvgRGBA(255, 255, 255, 255));
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, x, y, menuOptions[i].c_str(), NULL);
        x += WINDOW_WIDTH / 4;
    }

}

void UserInterface::drawClock(NVGcontext *ctx, float x, float y, float w, float h) {


    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y, x, y + h / 5, nvgRGBA(40, 45, 50, 220), nvgRGBA(10, 10, 15, 220));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y, w, h, 3.0);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Outline
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x + 0.5f, y + 0.5f, w - 1, h - 1, 3.0);
    nvgStrokeWidth(ctx, 2);
    nvgStrokeColor(ctx, nvgRGB(0, 0, 0));
    nvgStroke(ctx);

    // - Clock
    time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string tString = ctime(&t);

    nvgFontSize(ctx, 24.0f);
    nvgFillColor(ctx, nvgRGBA(255, 255, 255, 255));
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(ctx, x + h * 0.3f, y + h * 0.5f, tString.substr(0, tString.length() - 6).c_str(), NULL);
}

void UserInterface::drawShadowBg() {
    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    nvgFillColor(ctx, nvgRGBA(1, 0, 5, 120));
    nvgFill(ctx);
}

bool UserInterface::insideRectangle(float rectX, float rectY, float rectW, float rectH) {
    // - Left
    if (this->mouseX < rectX) {
        return false;
    }
        // - Top
    else if (this->mouseY < rectY) {
        return false;
    }
        // - Right
    else if (this->mouseX > rectX + rectW) {
        return false;
    }
        // - Bellow
    else if (this->mouseY > rectY + rectH) {
        return false;
    }
    // - Not inside
    return true;
}

void UserInterface::drawChannelsMenu(NVGcontext *ctx, float x, float y, float w, float h) {


    // - Header
    float hh = h / 7;
    NVGpaint bg = nvgLinearGradient(ctx, x, y - hh, x, y + hh, nvgRGBA(40, 45, 50, 250), nvgRGBA(10, 10, 15, 250));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y - hh, w, hh, 3.0);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Background
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y, w, h, 3.0);
    nvgFillColor(ctx, nvgRGBA(10, 10, 15, 250));
    nvgFill(ctx);

    // - Header Text
    nvgFontSize(ctx, 24.0f);
    nvgFillColor(ctx, nvgRGBA(255, 255, 255, 255));
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(ctx, x + hh * 0.3f, y - hh * 0.5f, menuOptions[selectedMenuOption].c_str(), NULL);

    // - Channel list
    for (int i = 0; i < channels.size(); ++i) {
        if (insideRectangle(x + hh * 0.3f, y + hh * 0.5f + i * 35 - 10, 150, 30) && click) selectedChannelOption = i;
        nvgFontSize(ctx, 24.0f);
        nvgFillColor(ctx,  selectedChannelOption == i ? nvgRGBA(255, 182, 38, 255) : nvgRGBA(255, 255, 255, 255));
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, x + hh * 0.3f, y + hh * 0.5f + i * 35, channels[i].c_str(), NULL);
    }


    // - Outline
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x + 0.5f, y - hh + 0.5f, w - 1, h + hh - 1, 3.0);
    nvgStrokeWidth(ctx, 2);
    nvgStrokeColor(ctx, nvgRGB(0, 0, 0));
    nvgStroke(ctx);

}
