#ifndef SOUNDING_HH
#define SOUNDING_HH

#include <sigc++/signal.h>

#include "../sound.hh"
#include "abstractstate.hh"

namespace silverbee {
namespace state {

using alarm_sounding_event = sigc::signal<void>;
class Sounding final : public AlarmState {
   public:
    explicit Sounding(const std::string& sound_filename);

    AlarmState* trigger() override;
    AlarmState* snooze() override;
    AlarmState* stop() override;

    void wire(AlarmState* snoozing_state, AlarmState* armed_state) {
        snoozing = snoozing_state;
        armed = armed_state;
    }

    alarm_sounding_event on_alarm_sounding() const { return alarm_sounding; }

   private:
    AlarmState* snoozing{nullptr};
    AlarmState* armed{nullptr};
    silverbee::Sound sound;
    alarm_sounding_event alarm_sounding{};
    bool playing_sound{false};

    void play_sound();
    void stop_sound();
};
}  // namespace state
}  // namespace silverbee

#endif
