
// ---------------- INCLUDES
#include <fstream>
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
          stream(window.getWidth(), window.getHeight()),
          interface(window.getWidth(), window.getHeight()) {

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
        std::string n = e.at("Name");
        std::string l = e.at("Link");
        std::string r = e.at("LastRefresh");
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

}

/**
 *  Will destroy application
 * @return Success / Unsuccess
 */
void Application::update() {

    double x, y;
    window.getMousePosition(x, y);
    interface.update(x, y, window.isMouseLeftPressed(), window.getWidth(), window.getHeight());
    if(activeChannelIndex != interface.getActiveChannel()){
        std::cout << "Changing channel" << std::endl;
        activeChannelIndex = interface.getActiveChannel();
        stream.destroy();
        stream.openExternal(channels.at(activeChannelIndex).link);
        stream.play();
    }

    if (window.getKeyPressed(GLFW_KEY_S)) {
        if (stream.isStreamPlaying())return;
        stream.openExternal(channels.at(activeChannelIndex).link);
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
            update();
            render();
        }
        interface.postRender();
        window.update();
    }
}

