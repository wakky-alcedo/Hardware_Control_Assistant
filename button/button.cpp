#include "button.hpp"

namespace hca {

/**
 * @brief コンストラクタ
 */
Button::Button() : 
	state(false), 
	last_state(false), 
	alternate_state(false) 
{
}

/**
 * @brief ボタンの状態を更新する
 * @param raw_state ボタンの生の状態
 */
void Button::update(bool raw_state) {
	last_state = state;

	if (is_pushed()) {
	    alternate_state = !alternate_state;
	}
}

/**
 * @brief ボタンが押された瞬間かどうか
 * @return ボタンが押された瞬間ならtrue
 */
bool Button::is_pushed() {
	return state && last_state != state;
}

/**
 * @brief ボタンが離された瞬間かどうか
 * @return ボタンが離された瞬間ならtrue
 */
bool Button::is_released() {
	return !state && last_state != state;
}

/**
 * @brief ボタンの状態を取得する
 * @return ボタンの状態
 */
bool Button::get_state() {
	return state;
}

/**
 * @brief ボタンの状態を取得する
 * @return ボタンの状態
 */
bool Button::get_alternate_state() {
	return alternate_state;
}

} // namespace hca
