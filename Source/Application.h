#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

// --------------- INCLUDES
#include "Graphics/UserInterface.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Video/Stream.h"
#include <glm.hpp>

// ---------------
class Application {

    Window window;
    UserInterface interface;
    Stream stream;

    // - Settings
    bool displayOverlay = true;


public:
    Application();
    ~Application();
    bool loop();

private:
    void update();
    void render();
};


#endif //PROJECT_APPLICATION_H
