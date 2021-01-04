#ifndef ARMED_HH
#define ARMED_HH

#include "../alarmsettings.hh"
#include "abstractstate.hh"
#include "sounding.hh"

namespace silverbee {
namespace state {
class Armed final : public AlarmState {
   public:
    AlarmState* trigger() override;
    AlarmState* snooze() override;
    AlarmState* stop() override;

    void wire(Sounding* sounding_state) { sounding = sounding_state; }

    constexpr void set_alarm_event(const silverbee::AlarmSettings& as) {
        alarm_settings = as;
    }

   private:
    silverbee::AlarmSettings alarm_settings{};
    Sounding* sounding{nullptr};
};
}  // namespace state
}  // namespace silverbee

#endif
