#include "sounding.hh"

#ifndef NDEBUG
#include <iostream>
#endif

using namespace silverbee::state;

Sounding::Sounding(const std::string& sound_filename)
    : snoozing{nullptr},
      armed{nullptr},
      sound{sound_filename},
      playing_sound{false} {}

AlarmState* Sounding::trigger() {
    play_sound();
    return this;
}

AlarmState* Sounding::snooze() {
    stop_sound();
    return snoozing;
}

AlarmState* Sounding::stop() {
    stop_sound();
    return armed;
}

void Sounding::play_sound() {
    if (!playing_sound) {
#ifndef NDEBUG
        std::cout << "Play sound\n";
#endif
        sound.play();
        playing_sound = true;
        alarm_sounding.emit();
    }
}
void Sounding::stop_sound() {
    if (playing_sound) {
#ifndef NDEBUG
        std::cout << "Stop sound\n";
#endif
        sound.stop();
        playing_sound = false;
    }
}
