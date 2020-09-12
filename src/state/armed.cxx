#include "armed.hh"

#include <glibmm/datetime.h>

#include <stdexcept>

using namespace silverbee::state;

Armed::Armed() : alarm_settings{}, sounding{nullptr} {}

AlarmState* Armed::trigger() {
    auto current_time = Glib::DateTime::create_now_local();
    auto current_day = silverbee::int_to_day(current_time.get_day_of_week());
    if (alarm_settings.is_day_set(current_day) &&
        current_time.get_hour() == alarm_settings.get_hour() &&
        current_time.get_minute() == alarm_settings.get_minute() &&
        current_time.get_second() == 0) {
        return sounding;
    }
    return this;
}

AlarmState* Armed::snooze() {
    throw std::logic_error("Armed does not know transition 'snooze'");
}

AlarmState* Armed::stop() {
    throw std::logic_error("Armed does not know transition 'stop'");
}
