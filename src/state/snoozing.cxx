#include "snoozing.hh"

#include <stdexcept>

using namespace silverbee::state;

Snoozing::Snoozing(silverbee::t_minute snooze_minutes)
    : timer{},
      sounding{nullptr},
      snooze_seconds{snooze_minutes * 60.0},
      timer_started{false} {
    timer.stop();
    timer.reset();
}

AlarmState* Snoozing::trigger() {
    if (!timer_started) {
        timer.start();
        timer_started = true;
    }
    if (timer.elapsed() > snooze_seconds) {
        timer.stop();
        timer.reset();
        timer_started = false;
        return sounding;
    }

    return this;
}

AlarmState* Snoozing::snooze() {
    throw std::logic_error("Snoozing does not know transition 'snooze'");
}

AlarmState* Snoozing::stop() {
    throw std::logic_error("Snoozing does not know transition 'stop'");
}
