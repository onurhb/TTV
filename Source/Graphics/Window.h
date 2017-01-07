#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

// ------------------- MACROS
#define MAX_KEYS 1024
// ------------------- INCLUDES
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../config.h"



class Window {

    std::string windowTitle;
    GLFWwindow *windowPointer;

    bool mouseLeft = false, mouseRight = false;
    int windowWidth, windowHeight;
    double xoffset, yoffset;
    double mouseX, mouseY;
    bool keys[MAX_KEYS];

public:
    Window(std::string title, int height, int width);
    ~Window();
    // - Initialize window
    bool initialize();
    // - Handle window
    void update() const;
    void destroy() const;
    bool closed() const;
    void clear();
    // - Getters
    void getScrollOffset(double &xoffset, double &yoffset);
    void getMousePosition(double &x, double &y) const;
    bool isMouseLeftPressed() const;
    bool isMouseRightPressed() const;
    bool getKeyPressed(int key) const;
    GLFWwindow* getWindow() const;

private:
    static bool loadContext();
    friend void keyCallback(GLFWwindow *window_ptr, int key, int scancode, int state, int mods);
    friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    friend void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    friend void mouseCallback(GLFWwindow *window_ptr, double xpos, double ypos);
};

#endif // PROJECT_WINDOW_H
