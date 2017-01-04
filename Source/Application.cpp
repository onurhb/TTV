
// ---------------- INCLUDES
#include "Application.h"
// ----------------


Application::Application()
        : window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT),
          stream(WINDOW_WIDTH, WINDOW_HEIGHT),
          texture(WINDOW_WIDTH, WINDOW_HEIGHT),
          interface(window.getWindow()) {
    // - Initialize a big rectangle to render on
    GLfloat vertices[] = {
            // First triangle
            1.0f, 1.0f, 0.0f,  // Top Right
            1.0f, -1.0f, 0.0f,  // Bottom Right
            -1.0f, 1.0f, 0.0f,  // Top Left
            // Second triangle
            1.0f, -1.0f, 0.0f,  // Bottom Right
            -1.0f, -1.0f, 0.0f,  // Bottom Left
            -1.0f, 1.0f, 0.0f   // Top Left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader.bindShader();
    shader.loadFromFile("shader.vert", "shader.frag");
    shader.setUniform2f("iResolution", glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

    pixels = stream.getPixels();
    texture.bindTexture();
    texture.loadData(pixels, GL_RGB);
    texture.unbindTexture();

    stream.openFile("sample.mp4");
    stream.play();

}

Application::~Application() {

}

/**
 * Handling rendering here...
 */
void Application::render() {

    texture.bindTexture();
    texture.loadSubData(stream.getPixels(), WINDOW_WIDTH, WINDOW_HEIGHT);
    shader.bindShader();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    shader.unbindShader();
    texture.unbindTexture();
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

