#pragma once
#include "libs/miniaudio.h"

class Channel {
    ma_sound sound{};
    int currentSample{};
    public:
    Channel();
    ~Channel();

    void trigger(ma_engine& engine, const char* file, int note, float volume);
    void stop();
};

