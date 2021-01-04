#ifndef ALARMCONTEXT_HH
#define ALARMCONTEXT_HH

#include "../alarmsettings.hh"
#include "abstractstate.hh"
#include "armed.hh"
#include "snoozing.hh"
#include "sounding.hh"

namespace silverbee {
namespace state {
class AlarmContext final {
   public:
    AlarmContext(const silverbee::AlarmSettings& alarm_settings,
                 const std::string& sound_filename);
    ~AlarmContext();
    AlarmContext(const AlarmContext&) = delete;
    AlarmContext& operator=(const AlarmContext&) = delete;

    void set_alarm_event(const silverbee::AlarmSettings& ae) {
        armed->set_alarm_event(ae);
    }

    void trigger() { current_state = current_state->trigger(); }
    void snooze() { current_state = current_state->snooze(); }
    void stop() { current_state = current_state->stop(); }

    alarm_sounding_event on_alarm_sounding() const {
        return sounding->on_alarm_sounding();
    }

   private:
    AlarmState* current_state{nullptr};
    Armed* armed{new Armed{}};
    Sounding* sounding;
    Snoozing* snoozing;
};
}  // namespace state
}  // namespace silverbee

#endif
