
// ---------------- INCLUDES
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT), interface(window.getWindow()) {

}

Application::~Application() {

}

/**
 * Handling rendering here...
 */
void Application::render() {
    interface.render();
}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update(){
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

