#include "Channel.h"
#include "utils/utils.h"

Channel::Channel() = default;
Channel::~Channel() = default;

void Channel::trigger(ma_engine& engine, const char* file, int note, float volume) {
    ma_sound_uninit(&sound);
    ma_sound_init_from_file(&engine, file,0, NULL, NULL, &sound);
    ma_sound_set_pitch(&sound, midiToFreq(note));
    ma_sound_set_volume(&sound, volume);
    ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);
}

void Channel::stop() {
    ma_sound_stop(&sound);
}