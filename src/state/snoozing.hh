#ifndef SNOOZING_HH
#define SNOOZING_HH

#include <glibmm/timer.h>

#include "../alarmsettings.hh"
#include "abstractstate.hh"

namespace silverbee {
namespace state {
class Snoozing : public AlarmState {
   public:
    Snoozing(silverbee::t_minute snooze_minutes = 5);
    virtual ~Snoozing() = default;

    virtual AlarmState* trigger();
    virtual AlarmState* snooze();
    virtual AlarmState* stop();

    void wire(AlarmState* sounding_state) { sounding = sounding_state; }

   private:
    Glib::Timer timer;
    AlarmState* sounding;
    double snooze_seconds;
    bool timer_started;
};
}  // namespace state

}  // namespace silverbee

#endif
