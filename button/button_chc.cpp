#include "button_chc.hpp"

namespace hca {

/**
 * @brief コンストラクタ
 * @param chattering_count チャタリング判定回数
 */
Button_CHC::Button_CHC(uint32_t chattering_count) :
    chattering_count(chattering_count),
    chattering_counter(0),
    last_raw_state(false)
{
}

/**
 * @brief ボタンの状態を更新する
 * @param raw_state ボタンの生の状態
 */
void Button_CHC::update(bool raw_state) {
    // 共通
    last_state = state;

    // チャタリング防止 変更があってから一定回数読み取りが同じだったら状態を更新
    // if (last_raw_state != raw_state) {
    //     chattering_counter = 0;
    // } else {
    //     chattering_counter++;
    // }
    // if (chattering_counter >= chattering_count) {
    //     state = raw_state;
    //     chattering_counter = 0;
    // }
    // last_raw_state = raw_state;

    // チャタリング防止 一度状態を変更したら一定回数は変更しない
    if (state != raw_state) {
        if (chattering_count <= chattering_counter) {
            state = raw_state;
            chattering_counter = 0;
        }else{
            chattering_counter++;
        }
    }    

    if (is_pushed()) {
        alternate_state = !alternate_state;
    }
}

} // namespace hca
