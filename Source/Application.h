#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

// --------------- INCLUDES
#include "Graphics/UserInterface.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
// ---------------
class Application {

    Window window;
    Shader shader;
    UserInterface interface;

public:
    Application();
    ~Application();
    bool loop();

private:
    void update();
    void render();
};


#endif //PROJECT_APPLICATION_H
