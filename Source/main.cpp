#include <vlc/vlc.h>
#include <iostream>

int main(int argc, char* argv[])
{
    libvlc_instance_t * inst;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;

    std::cout << libvlc_get_version();


    return 0;
}