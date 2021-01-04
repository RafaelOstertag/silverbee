#include "alarmcontext.hh"

#include "armed.hh"

using namespace silverbee::state;

AlarmContext::AlarmContext(const silverbee::AlarmSettings& alarm_settings,
                           const std::string& sound_filename)
    : sounding{new Sounding{sound_filename}},
      snoozing{new Snoozing{alarm_settings.get_snooze()}} {
    armed->set_alarm_event(alarm_settings);

    armed->wire(sounding);
    sounding->wire(snoozing, armed);
    snoozing->wire(sounding);

    current_state = armed;
}

AlarmContext::~AlarmContext() {
    current_state = nullptr;
    delete armed;
    delete sounding;
    delete snoozing;
}
