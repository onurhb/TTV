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

    drawMenu(ctx, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, 100);
    drawClock(ctx, WINDOW_WIDTH - 265, 50, 215, 50);

}

// ------------------------------------------ COMPONENTS

void UserInterface::drawMenu(NVGcontext *ctx, float x, float y, float w, float h) {

    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y, x, y + h, nvgRGBA(30, 35, 50, 230), nvgRGBA(0, 0, 5, 230));
    nvgBeginPath(ctx);
    nvgRect(ctx, x, y, w, h);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Outline
    nvgBeginPath(ctx);
    nvgRect(ctx, x + 0.5f, y + 0.5f, w - 1, h - 1);
    nvgStrokeColor(ctx, nvgRGB(30, 30, 30));
    nvgStroke(ctx);

    // - Menu options
    x += WINDOW_WIDTH / 6;
    for (auto &&menuOption : menuOptions) {
        nvgFontSize(ctx, 34.0f);
        nvgFillColor(ctx, nvgRGBA(225, 225, 225, 230));
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, x + h * 0.3f, y + h * 0.5f, menuOption.c_str(), NULL);
        x += WINDOW_WIDTH / 4;
    }
}

void UserInterface::drawClock(NVGcontext *ctx, float x, float y, float w, float h) {
    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y, x, y + h, nvgRGBA(30, 35, 50, 190), nvgRGBA(0, 0, 5, 190));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y, w, h, 3.0);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Outline
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x + 0.5f, y + 0.5f, w - 1, h - 1, 3.0);
    nvgStrokeWidth(ctx, 2);
    nvgStrokeColor(ctx, nvgRGB(30, 30, 30));
    nvgStroke(ctx);

    // - Clock
    std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(time);
    std::string tString = ctime(&t);

    nvgFontSize(ctx, 24.0f);
    nvgFillColor(ctx, nvgRGBA(225, 225, 225, 255));
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(ctx, x + h * 0.3f, y + h * 0.5f, tString.substr(0, tString.length() - 6).c_str(), NULL);
}
