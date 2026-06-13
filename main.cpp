#include <iostream>
#include "libs/miniaudio.h"
#include "utils/utils.h"
#include <conio.h>


int keyToNote( bool& exit, int key) {
    switch (key) {
        case '`': exit = true; return 0;

        case '\\':          return 48;
        case 'a': case 'A': return 49;
        case 'z': case 'Z': return 50;
        case 's': case 'S': return 51;
        case 'x': case 'X': return 52;
        case 'c': case 'C': return 53;
        case 'f': case 'F': return 54;
        case 'v': case 'V': return 55;
        case 'g': case 'G': return 56;
        case 'b': case 'B': return 57;
        case 'h': case 'H': return 58;
        case 'n': case 'N': return 59;
        case 'm': case 'M': return 60;
        case 'k': case 'K': return 61;
        case ',':           return 62;
        case 'l': case 'L': return 63;
        case '.':           return 64;
        case '/':           return 65;

        case 'q': case 'Q': return 60;
        case '2':           return 61;
        case 'w': case 'W': return 62;
        case '3':           return 63;
        case 'e': case 'E': return 64;
        case 'r': case 'R': return 65;
        case '5':           return 66;
        case 't': case 'T': return 67;
        case '6':           return 68;
        case 'y': case 'Y': return 69;
        case '7':           return 70;
        case 'u': case 'U': return 71;
        case 'i': case 'I': return 72;
        case '9':           return 73;
        case 'o': case 'O': return 74;
        case '0':           return 75;
        case 'p': case 'P': return 76;
        case '[':           return 77;
        case '=':           return 78;
        case ']':           return 79;
        default: return 0;
    }
}

int main() {
#ifdef _WIN32
    std::cout << "Windows\n";
#else
    std::cout << "Linux\n";
    #endif
    ma_engine engine;

    ma_engine_config engineConfig = ma_engine_config_init();
    engineConfig.channels = 2;
    engineConfig.sampleRate = 44100;

    if (ma_engine_init(&engineConfig, &engine) != MA_SUCCESS) {
        std::cout << "Failed to init engine" << std::endl;
        return -1;
    }
    ma_sound voice;
    //if (ma_sound_init_from_file(&engine, "D:\\_dev\\c++\\projects\\FLTracker\\samples\\melody16b.wav", 0, NULL, NULL, &voice) != MA_SUCCESS)
    //std::cout <<  "Error loading file..." << std::endl;

    //// Control por nota:
    //ma_sound_set_pitch(&voice, 1.5f);        // semitono → frecuencia
    //ma_sound_set_volume(&voice, 0.8f);       // velocity
    //ma_sound_set_looping(&voice, MA_TRUE);   // loop para instrumentos sostenidos
    //ma_sound_seek_to_pcm_frame(&voice, 0);   // rebobinar antes de cada trigger
    //ma_sound_start(&voice);
    ma_result result;
    int key{};
    int note{};
    bool exit{false};

    result = ma_sound_init_from_file(&engine, "samples/pno.wav", 0, NULL, NULL, &voice);
    std::cout << "Load result: " << result << std::endl;  // 0 = MA_SUCCESS

    while (!exit) {
        key = _getch();
        note = keyToNote(exit, key);

        ma_sound_set_pitch(&voice, midiToFactor(note));
        ma_sound_seek_to_pcm_frame(&voice, 0);   // rebobinar antes de cada trigger
        ma_result play = ma_sound_start(&voice);
        std::cout << "Play result: " << play << std::endl;    // 0 = MA_SUCCESS
        std::cout << "Is playing ["<< key <<"]: " << ma_sound_is_playing(&voice) << std::endl;  // 1 = sí
    }
    std::cout << "Press Enter to quit...";
    getchar();
    ma_sound_stop(&voice);

    ma_engine_uninit(&engine);

    return 0;
}
