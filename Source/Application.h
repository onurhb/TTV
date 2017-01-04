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
    Shader shader;
    UserInterface interface;
    Stream stream;
    Texture texture;
    GLuint VAO, VBO;
    unsigned char* pixels;

public:
    Application();
    ~Application();
    bool loop();

private:
    void update();
    void render();
};


#endif //PROJECT_APPLICATION_H
