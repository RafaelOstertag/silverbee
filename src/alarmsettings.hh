#ifndef ALARMEVENT_HH
#define ALARMEVENT_HH

#include <glibmm/date.h>

#include <algorithm>
#include <bitset>
#include <vector>

namespace silverbee {

using t_hour = unsigned char;
using t_minute = unsigned char;

enum class DAY {
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
};

class AlarmSettings {
   public:
    AlarmSettings(t_hour h = 0, t_minute m = 0, std::vector<DAY> d = {});

    constexpr t_hour get_hour() const { return hour; }
    constexpr t_minute get_minute() const { return minute; }
    bool is_day_set(DAY d) const { return days.test(static_cast<unsigned long>(d)); }
    t_minute get_snooze() const { return snooze; }

    void save() const;
    void load();

   private:
    t_hour hour;
    t_minute minute;
    t_minute snooze = 5;
    std::bitset<7> days = 0;

    void reset();
};

constexpr DAY int_to_day(int i) {
    switch (i) {
        case 0:
        case 7:
            return DAY::SUNDAY;
        case 1:
            return DAY::MONDAY;
        case 2:
            return DAY::TUESDAY;
        case 3:
            return DAY::WEDNESDAY;
        case 4:
            return DAY::THURSDAY;
        case 5:
            return DAY::FRIDAY;
        case 6:
            return DAY::SATURDAY;
        default:
            throw std::invalid_argument("Invalid day index: " +
                                        std::to_string(i));
    }
}

}  // namespace silverbee

#endif
