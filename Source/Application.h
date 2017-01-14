#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

// --------------- INCLUDES
#include "Graphics/UserInterface.h"
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Video/Stream.h"
#include "Utils/Thread.h"
#include <json.hpp>
#include <glm.hpp>

// ---------------
class Application {

    // - Channel
    struct Channel{
        std::string name;
        std::string link;
        std::string lastRefresh;
    };

    // - Channel list
    std::vector<Channel> channels;

    Window window;
    UserInterface interface;
    Stream stream;
    Thread thread;

    // - Settings
    bool displayOverlay = true;
    unsigned int activeChannelIndex = 0;


public:
    Application();
    ~Application();
    bool loop();

private:
    void update(bool &closed);
    void render();
    bool getChannels();
};


#endif //PROJECT_APPLICATION_H
