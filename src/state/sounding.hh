#ifndef SOUNDING_HH
#define SOUNDING_HH

#include <sigc++/signal.h>

#include "../sound.hh"
#include "abstractstate.hh"

namespace silverbee {
namespace state {

using alarm_sounding_event = sigc::signal<void>;
class Sounding : public AlarmState {
   public:
    Sounding(const std::string& sound_filename);
    virtual ~Sounding() = default;
    virtual AlarmState* trigger();
    virtual AlarmState* snooze();
    virtual AlarmState* stop();

    void wire(AlarmState* snoozing_state, AlarmState* armed_state) {
        snoozing = snoozing_state;
        armed = armed_state;
    }

    alarm_sounding_event on_alarm_sounding() { return alarm_sounding; }

   private:
    AlarmState* snoozing;
    AlarmState* armed;
    silverbee::Sound sound;
    alarm_sounding_event alarm_sounding;
    bool playing_sound;

    void play_sound();
    void stop_sound();
};
}  // namespace state
}  // namespace silverbee

#endif
