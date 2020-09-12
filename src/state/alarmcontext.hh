#ifndef ALARMCONTEXT_HH
#define ALARMCONTEXT_HH

#include "../alarmsettings.hh"
#include "abstractstate.hh"
#include "armed.hh"
#include "snoozing.hh"
#include "sounding.hh"

namespace silverbee {
namespace state {
class AlarmContext {
   public:
    AlarmContext(const silverbee::AlarmSettings& alarm_settings,
                 const std::string& sound_filename);
    ~AlarmContext();
    AlarmContext(const AlarmContext&) = delete;

    void set_alarm_event(const silverbee::AlarmSettings& ae) {
        armed->set_alarm_event(ae);
    }

    void trigger() { current_state = current_state->trigger(); }
    void snooze() { current_state = current_state->snooze(); }
    void stop() { current_state = current_state->stop(); }

    alarm_sounding_event on_alarm_sounding() {
        return sounding->on_alarm_sounding();
    }

   private:
    AlarmState* current_state;
    Armed* armed;
    Sounding* sounding;
    Snoozing* snoozing;
};
}  // namespace state
}  // namespace silverbee

#endif
