#define NANOVG_GL3_IMPLEMENTATION
// -------------- INCLUDES
#include "UserInterface.h"
#include "nanovg_gl.h"

UserInterface::UserInterface(GLFWwindow *window) {
    // - Window
    this->window = window;

    // - NanoVG
    ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
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

void UserInterface::render(){
    nvgBeginPath(ctx);
    nvgRect(ctx, 100, 200, 300, 300);
    nvgFillColor(ctx, nvgRGB(255, 125, 125));
    nvgFill(ctx);
}

void UserInterface::demo(double x, double y) {
    nvgBeginPath(ctx);
    nvgCircle(ctx, x, y, 50);
    nvgFillColor(ctx, nvgRGB(90, 50, 125));
    nvgFill(ctx);
}
