#include <assert.h>
#include "Stream.h"

const char *vertShaderSrc = "#version 330 core\n"
        "layout (location = 0) in vec4 position;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "     gl_Position = position;\n"
        "     TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n"
        "}";

const char *fragShaderSrc = "#version 330 core\n"
        "uniform sampler2D iChannel0;\n"
        "uniform vec2 iResolution;\n"
        "in vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = texture2D(iChannel0, TexCoord).zyxw;\n"
        "}";

void *lock(void *data, void **p_pixels) {
    auto *ctx = static_cast<Stream::CTX *>(data);
    ctx->imagemutex.lock();
    *p_pixels = ctx->pixeldata;

    return NULL;
}

void unlock(void *data, void *id, void *const *p_pixels) {
    auto *ctx = static_cast<Stream::CTX *>(data);
    ctx->imagemutex.unlock();
}

// ----------------------------------------------------------------
Stream::Stream(unsigned int screenWidth, unsigned int screenHeight)
        : texture(screenWidth, screenHeight) {

    // - Member variables
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    // - Setup
    createQuad();
    initializeVLC();
    initializeShader();
}

Stream::~Stream() {
    // - Free OpenGL
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // - Free VLC
    if (streamPlaying) {
        libvlc_media_player_stop(mediaPlayer);
        libvlc_media_player_release(mediaPlayer);
        libvlc_release(instance);
    }
    // - Free Pixels
    delete[] ctx.pixeldata;
}

void Stream::createQuad() {
    // - Initialize a big rectangle to render on
    GLfloat vertices[] = {1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                          -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    GLushort indices[] = {0, 1, 3, 1, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // - Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    // - TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // - Unbind VAO
    glBindVertexArray(0);
}

void Stream::initializeVLC() {
    // - Initialize libvlc
    const char *vlc_argv[] = {};
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
    instance = libvlc_new(vlc_argc, vlc_argv);

    // - Initialize pixel array
    ctx.pixeldata = new unsigned char[screenWidth * screenHeight * 3];
}

void Stream::initializeShader() {
    texture.bindTexture();
    texture.loadData(ctx.pixeldata, GL_RGB);
    texture.unbindTexture();

    shader.loadFromString(vertShaderSrc, fragShaderSrc);
}

/**
 * @brief Opens a file and initializes vlc for playback
 * @param path : path to file
 */
void Stream::openFile(std::string path) {

    // - Open the media
    media = libvlc_media_new_path(instance, path.c_str());
    // - Initialize mediaplayer for playback with media
    mediaPlayer = libvlc_media_player_new_from_media(media);
    // - Free
    libvlc_media_release(media);
}

void Stream::openExternal(std::string URL) {

    // - Open the media
    media = libvlc_media_new_location(instance, URL.c_str());
    // - Initialize mediaplayer for playback with media
    mediaPlayer = libvlc_media_player_new_from_media(media);
    // - Free
    libvlc_media_release(media);
}

/**
 * @brief Should be called after a file has been initialized for playback
 * This will play the file and call the callback when a frame needs to be rendered
 * @return returns true if stream is started
 */
bool Stream::play() {
    if(streamPlaying) return false;
    libvlc_video_set_format(mediaPlayer, "RV24", screenWidth, screenHeight, screenWidth * 3);
    libvlc_video_set_callbacks(mediaPlayer, lock, unlock, NULL, &ctx);
    libvlc_media_player_play(mediaPlayer);
    this->streamPlaying = true;
    return true;
}


/**
 * @brief Render to screen
 */
void Stream::render() {
    shader.bindShader();
    texture.bindTexture();
    texture.loadSubData(ctx.pixeldata, screenWidth, screenHeight);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    texture.unbindTexture();
    shader.unbindShader();
}

/**
 * @brief Returns pixels
 * @return unsigned char * of pixels
 */
unsigned char *Stream::getPixels() {
    return this->ctx.pixeldata;
}

/**
 * @brief Returns true or false on stream playing
 * @return bool : is stream running
 */
bool Stream::isStreamPlaying() const {
    return this->streamPlaying;
}

bool Stream::pause() {
    if(!streamPlaying) return false;
    libvlc_media_player_pause(mediaPlayer);
    this->streamPlaying = false;
    return true;
}

bool Stream::resume() {
    if(streamPlaying) return false;
    libvlc_media_player_play(mediaPlayer);
    this->streamPlaying = true;
    return true;
}

bool Stream::destroy() {
    if(!streamPlaying) return false;
    libvlc_media_player_stop(mediaPlayer);
    libvlc_media_player_release(mediaPlayer);
    this->streamPlaying = false;
    return true;
}

