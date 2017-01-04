#include <assert.h>
#include "Stream.h"


void *lock(void *data, void **p_pixels) {
    auto *ctx = static_cast<Stream::CTX *>(data);


    ctx->imagemutex.lock();
    *p_pixels = ctx->pixeldata;

}

void unlock(void *data, void *id, void *const *p_pixels) {
    auto *ctx = static_cast<Stream::CTX *>(data);

    ctx->imagemutex.unlock();

}

void display(void *data, void *id) {
    auto *ctx = static_cast<Stream::CTX *>(data);
}


// ----------------------------------------------------------------
Stream::Stream(unsigned int screenWidth, unsigned int screenHeight) {
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;
    // - Initialize libvlc
    instance = libvlc_new(0, NULL);
    // - Initialize pixel array
    ctx.pixeldata = new unsigned char[screenWidth * screenHeight * 3];
}

Stream::~Stream() {
    destroy();
}

/**
 * @brief Opens a file and initializes vlc for playback
 * @param path : path to file
 */
void Stream::openFile(std::string path) {
    if (this->playing) destroy();
    // - Open the media
    media = libvlc_media_new_path(instance, path.c_str());
    // - Initialize mediaplayer for playback with media
    mediaPlayer = libvlc_media_player_new_from_media(media);
    // - Free
    libvlc_media_release(media);
}

/**
 * @brief Returns a texture object
 * which can be used to render currently playing file
 * @return Texture object
 */
unsigned char *Stream::getPixels() {
    return this->ctx.pixeldata;
}

/**
 * @brief Should be called after a file has been initialized for playback
 * This will play the file and call the callback when a frame needs to be rendered
 */
void Stream::play() {
    libvlc_video_set_format(mediaPlayer, "RV16", screenWidth, screenHeight, screenWidth * 2);
    libvlc_video_set_callbacks(mediaPlayer, lock, unlock, display, &ctx);
    libvlc_media_player_play(mediaPlayer);
    this->playing = true;
}

/**
 * @brief Destroys stream and frees memory
 */
void Stream::destroy() {
    libvlc_media_player_stop(mediaPlayer);
    libvlc_media_player_release(mediaPlayer);
    libvlc_release(instance);
    delete[] ctx.pixeldata;
}
