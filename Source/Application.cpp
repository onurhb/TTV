
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
    interface.render();

}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update() {
    if (window.getKeyPressed(GLFW_KEY_S)) {
        if(stream.isStreamPlaying()){
            return;
        }
//        stream.openExternal("http://trkvz-live.ercdn.net/ahaberhd/ahaberhd_720p.m3u8?st=ufqmcDHE5CzqKCAHN6WOdQ&e=1483736002");
        stream.openFile("sample.mp4");
        stream.play();
    }else if(window.getKeyPressed(GLFW_KEY_P)) {
        stream.pause();
    }else if(window.getKeyPressed(GLFW_KEY_R)) {
        stream.resume();
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

