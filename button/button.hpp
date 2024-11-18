#ifndef HCA_BUTTON_HPP_
#define HCA_BUTTON_HPP_

#include <stdint.h>

namespace hca {

class Button {
protected:
	bool state;
	bool last_state;
	bool alternate_state;
public:
	Button();
	virtual void update(bool raw_state);
	bool is_pushed();
	bool is_released();
	bool get_state();
	bool get_alternate_state();
};

} // namespace hca

#endif /* HCA_BUTTON_HPP_ */
