#ifndef BUTTON_CHC_HPP_
#define BUTTON_CHC_HPP_

#include "button.hpp"

namespace hca {

class Button_CHC : public Button
{
private:
    uint32_t chattering_count = 0;
    uint32_t chattering_counter = 0;
    bool last_raw_state;
public:
    Button_CHC(uint32_t chattering_count);
    void update(bool raw_state);
};

} // namespace hca

#endif // BUTTON_CHC_HPP_