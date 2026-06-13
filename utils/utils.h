#pragma once
#include <cmath>

inline float midiToFactor(int midiNote) {
    //return 440.0f * pow(2, (midiNote - 69) /12);
    return pow(2.f,(static_cast<float>(midiNote) - 69.f) / 12.f) ;
}

inline float midiToFreq(int midiNote) {
    return 440.f * pow(2.f, (static_cast<float>(midiNote) - 69.f) /12.f);
}
