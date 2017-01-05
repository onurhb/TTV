
// ---------------- INCLUDES
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
          stream(WINDOW_WIDTH, WINDOW_HEIGHT),
          interface(window.getWindow()) {

    stream.openExternal("http://trkvz-live.ercdn.net/ahaberhd/ahaberhd_720p.m3u8?st=7iNh2ZfQ1Qo1Xt0BUhKU3A&e=1483672006");
//    stream.openFile("sample.mp4");
    stream.play();

}

Application::~Application() {

}

/**
 * Handling rendering here...
 */
void Application::render() {

    stream.render();

}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update() {

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

