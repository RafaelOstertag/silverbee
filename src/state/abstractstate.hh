#ifndef ABSTRACTSTATE_HH
#define ABSTRACTSTATE_HH

#include <memory>

namespace silverbee {
namespace state {
class AlarmState {
   public:
    virtual ~AlarmState() = default;
    virtual AlarmState* trigger() = 0;
    virtual AlarmState* snooze() = 0;
    virtual AlarmState* stop() = 0;
};
}  // namespace state
}  // namespace silverbee

#endif
