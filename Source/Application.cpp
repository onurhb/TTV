
// ---------------- INCLUDES
#include <fstream>
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
          stream(window.getWidth(), window.getHeight()),
          interface(window.getWidth(), window.getHeight()),
            thread(false){

    if (!getChannels()) {
        std::cerr << "Could not parse playlist.tivi. Make sure it exists and is in correct format." << std::endl;
    }else{
        std::vector<std::string> channelNames;
        for (auto &&channel : channels) channelNames.push_back(channel.name);
        interface.setChannels(channelNames);
    }

}

Application::~Application() {

}

/**
 * Looks for playlist.tivi and parses the file
 * Must be in json format having same format as struct Stream
 * @return true if success
 */
bool Application::getChannels() {

    std::ifstream t("playlist.tivi");
    nlohmann::json j;
    t >> j;
    if(j.empty()) return false;

    // - Parse and fill channels list
    for (nlohmann::json e : j) {
        std::string n = e.at("StreamName");
        std::string l = e.at("StreamSource");
        std::string r = e.at("StreamLastRefresh");
        channels.push_back(Channel{n, l, r});
    }

    return true;
}

/**
 * Handling rendering here...
 */
void Application::render() {

    stream.render();
    if(displayOverlay) interface.render();
    if(stream.getState() == LOADING) interface.renderState("Loading stream");
    else if(stream.getState() == ERR) interface.renderState("Failed opening stream");
}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update(bool& closed) {

    // - Initially open first channel
    stream.openExternal(channels.at(activeChannelIndex).link);
    stream.play();

   while(!closed){


       // - Give interface mouse information
       double x, y;
       window.getMousePosition(x, y);
       interface.update(x, y, window.isMouseLeftPressed(), window.getWidth(), window.getHeight());

       // - If any other channel is selected
       if(activeChannelIndex != interface.getActiveChannel()){
           activeChannelIndex = interface.getActiveChannel();
           if(stream.isStreamPlaying()) stream.destroy();
           stream.openExternal(channels.at(activeChannelIndex).link);
           stream.play();
           displayOverlay = false;
       }

       // - Display menu
       if (window.getKeyPressed(GLFW_KEY_P)) {
           displayOverlay = true;
       } else if (window.getKeyPressed(GLFW_KEY_R)) {
           displayOverlay = false;
       }
   }
}

/**
 * When called, the application will run untill window has been closed or destroyed
 * @return Success / Unsuccess
 */
bool Application::loop() {

    bool closed = false;

    // - Updates are handled by another thread
    thread.startThread(&Application::update, this, std::ref(closed));

    while (!window.closed()) {
        window.clear();
        interface.preRender();
        {
            render();
        }
        interface.postRender();
        window.update();
    }

    closed = true;
    thread.join();
}

