#include "button_cht.hpp"

#define TICK_PIN 8  // クロック信号の出力ピン

namespace hca {

/**
 * @brief コンストラクタ
 * @param chattering_time チャタリング判定時間
 */
Button_CHT::Button_CHT(uint32_t chattering_time) :
    chattering_time(chattering_time),
    raw_change_time(0),
    last_raw_state(false)
{
}

/**
 * @brief ボタンの状態を更新する
 * @param raw_state ボタンの生の状態
 * @param time 現在の時間
 */
void Button_CHT::update(bool raw_state, uint32_t time) {
    // 共通
    last_state = state;
    
    // チャタリング防止 変更があってから一定時間経過したら状態を更新
    // if (last_raw_state != raw_state) {
    // 	raw_change_time = time;
    // }
    // if (chattering_time <= (time - raw_change_time)) {
    // 	state = raw_state;
    // last_raw_state = raw_state;
    // }

    // チャタリング防止 一度状態を変更したら一定時間は変更しない
    if (state != raw_state) {
        if (chattering_time <= (time - raw_change_time)) {
            state = raw_state;
            raw_change_time = time;
        }
    }

    if (is_pushed()) {
	    alternate_state = !alternate_state;
	}
}

} // namespace hca
