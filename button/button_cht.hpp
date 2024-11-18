#ifndef BUTTON_CHT_HPP_
#define BUTTON_CHT_HPP_

#include "button.hpp"

namespace hca {

class Button_CHT : public Button
{
private:
    uint32_t chattering_time = 0; // チャタリング判定時間
	uint32_t raw_change_time;
    bool last_raw_state;
public:
    Button_CHT(uint32_t chattering_time);
    void update(bool raw_state, uint32_t time);
};

} // namespace hca

#endif // BUTTON_CHT_HPP_
