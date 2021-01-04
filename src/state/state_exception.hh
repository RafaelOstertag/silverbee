#ifndef STATE_EXCEPTION_HH
#define STATE_EXCEPTION_HH

#include <stdexcept>

namespace silverbee {
namespace state {
class StateException final : public std::logic_error {
    using std::logic_error::logic_error;
};
}  // namespace state
}  // namespace silverbee

#endif
