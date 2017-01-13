#define NANOVG_GL3_IMPLEMENTATION
// -------------- INCLUDES
#include <chrono>
#include <iostream>
#include "UserInterface.h"
#include "nanovg_gl.h"


UserInterface::UserInterface(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    // - NanoVG
    ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    nvgCreateFont(ctx, "system", "Ubuntu-M.ttf");

}

UserInterface::~UserInterface() {
    nvgDeleteGL3(ctx);
}

void UserInterface::preRender() {
    nvgBeginFrame(ctx, windowWidth, windowHeight, windowWidth / windowHeight);
}

void UserInterface::postRender() {
    nvgEndFrame(ctx);
}

void UserInterface::render() {

    drawShadowBg();
    drawMenu(ctx, 0, windowHeight / 1.65f, windowWidth, 100);
    drawClock(ctx, windowWidth - 265, windowHeight - 100, 215, 50);

    if (selectedMenuOption > -1)
        drawChannelsMenu(ctx, windowWidth / 4, 75, windowWidth / 2, windowHeight / 1.65f - 75);

}

void UserInterface::update(double mouseX, double mouseY, bool click, int wWidth, int wHeight) {

    if (wWidth > 0) {
        mouseX *= (float) this->windowWidth / (float) wWidth;
        mouseY *= (float) this->windowHeight / (float) wHeight;
    }

    this->mouseX = mouseX;
    this->mouseY = mouseY;
    this->click = click;
}

void UserInterface::setChannels(std::vector<std::string> channelNames) {
    this->channels = channelNames;
}

// ------------------------------------------ COMPONENTS

void UserInterface::drawMenu(NVGcontext *ctx, float x, float y, float w, float h) {

    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y - h, x, y + h, nvgRGBA(40, 45, 65, 250), nvgRGBA(10, 10, 15, 250));
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
    x += windowWidth / 6;
    y += h / 2;
    for (int i = 0; i < menuOptions.size(); ++i) {
        if (insideRectangle(x, y - 20, 150, 45) && click) selectedMenuOption = i;

        nvgFontSize(ctx, 36.0f);
        nvgFillColor(ctx,
                     selectedMenuOption == i ? nvgRGBA(255, 182, 38, 255) : nvgRGBA(255, 255, 255, 255));
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
        nvgText(ctx, x, y, menuOptions[i].c_str(), NULL);
        x += windowWidth / 4;
    }

}

void UserInterface::drawClock(NVGcontext *ctx, float x, float y, float w, float h) {

    // - Background
    NVGpaint bg = nvgLinearGradient(ctx, x, y - h, x, y + h, nvgRGBA(40, 45, 65, 250), nvgRGBA(10, 10, 15, 250));
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

    nvgFontSize(ctx, 22.0f);
    nvgFillColor(ctx, nvgRGBA(255, 255, 255, 255));
    nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(ctx, x + h * 0.3f, y + h * 0.5f, tString.substr(0, tString.length() - 6).c_str(), NULL);
}

void UserInterface::drawShadowBg() {
    nvgBeginPath(ctx);
    nvgRect(ctx, 0, 0, windowWidth, windowHeight);
    nvgFillColor(ctx, nvgRGBA(1, 0, 5, 75));
    nvgFill(ctx);
}

void UserInterface::drawChannelsMenu(NVGcontext *ctx, float x, float y, float w, float h) {


    // - Header
    float hh = h / 10;
    NVGpaint bg = nvgLinearGradient(ctx, x, y - hh, x, y + hh, nvgRGBA(40, 45, 65, 250), nvgRGBA(10, 10, 15, 250));
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y - hh, w, hh, 3.0);
    nvgFillPaint(ctx, bg);
    nvgFill(ctx);

    // - Background
    nvgBeginPath(ctx);
    nvgRoundedRect(ctx, x, y, w, h, 3.0);
    nvgFillColor(ctx, nvgRGBA(10, 10, 15, 230));
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
        nvgFillColor(ctx, selectedChannelOption == i ? nvgRGBA(255, 182, 38, 255) : nvgRGBA(255, 255, 255, 255));
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

unsigned int UserInterface::getActiveChannel() const {
    return selectedChannelOption;
}


