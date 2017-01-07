
// ---------------- INCLUDES
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
          stream(WINDOW_WIDTH, WINDOW_HEIGHT),
          interface(window.getWindow()) {


}

Application::~Application() {

}

/**
 * Handling rendering here...
 */
void Application::render() {

    stream.render();
    if(displayOverlay) interface.render();

}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update() {

    double x, y;
    window.getMousePosition(x, y);
    interface.update(x, y, window.isMouseLeftPressed());


    if (window.getKeyPressed(GLFW_KEY_S)) {
        if (stream.isStreamPlaying())return;
        displayOverlay = false;
        stream.openExternal("http://trkvz-live.ercdn.net/ahaberhd/ahaberhd.m3u8?st=NMOb1udJYVebDxWB31Bi9g&e=1483829728");
        stream.play();
    } else if (window.getKeyPressed(GLFW_KEY_P)) {
        displayOverlay = true;
    } else if (window.getKeyPressed(GLFW_KEY_R)) {
        displayOverlay = false;
    }
}

/**
 * When called, the application will run untill window has been closed or destroyed
 * @return Success / Unsuccess
 */
bool Application::loop() {
    while (!window.closed()) {
        window.clear();
        interface.preRender();
        {
            render();
            update();
        }
        interface.postRender();
        window.update();
    }
}

