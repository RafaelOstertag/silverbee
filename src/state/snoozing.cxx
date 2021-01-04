#include "snoozing.hh"

#include "state_exception.hh"

using namespace silverbee::state;

Snoozing::Snoozing(silverbee::t_minute snooze_minutes)
    : snooze_seconds{snooze_minutes * 60.0} {
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
    throw StateException("Snoozing does not know transition 'snooze'");
}

AlarmState* Snoozing::stop() {
    throw StateException("Snoozing does not know transition 'stop'");
}
