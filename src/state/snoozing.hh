#ifndef SNOOZING_HH
#define SNOOZING_HH

#include <glibmm/timer.h>

#include "../alarmsettings.hh"
#include "abstractstate.hh"

namespace silverbee {
namespace state {
class Snoozing final : public AlarmState {
   public:
    explicit Snoozing(silverbee::t_minute snooze_minutes = 5);

    AlarmState* trigger() override;
    AlarmState* snooze() override;
    AlarmState* stop() override;

    void wire(AlarmState* sounding_state) { sounding = sounding_state; }

   private:
    Glib::Timer timer{};
    AlarmState* sounding{nullptr};
    double snooze_seconds;
    bool timer_started{false};
};
}  // namespace state

}  // namespace silverbee

#endif
