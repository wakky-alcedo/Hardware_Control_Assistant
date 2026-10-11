#ifndef HCA_OUTPUT_FUNCTION_LIMIT_RATE_HPP_
#define HCA_OUTPUT_FUNCTION_LIMIT_RATE_HPP_

#include <cmath>

namespace hca {

/**
 * 変化の速さの上限 [unit/s]．0 以下で制限なし
 * 加速 = 0 から離れる向き (絶対値が大きくなる)，減速 = 0 に近づく向き．
 * 正負が入れ替わるときは，0 までを減速，0 からを加速として扱う．
 * @tparam T 値の型 (浮動小数点数)
 */
template <typename T> struct RateLimit {
    T acceleration;
    T deceleration;
};

/**
 * current から target へ，変化の速さの上限を守って dt 秒で動ける分だけ近づける
 * @tparam T 値の型 (浮動小数点数)
 * @param current 今の値
 * @param target 目標値
 * @param limit 変化の速さの上限
 * @param dt 経過時間 [s]
 * @return 近づけた値
 */
template <typename T> T limit_rate(T current, T target, const RateLimit<T>& limit, T dt){
    const T zero = static_cast<T>(0);
    T remaining = dt > zero ? dt : zero;
    // 正負が入れ替わるときは「0 まで減速」「0 から加速」の 2 区間になる
    for (int i = 0; i < 2 && current != target; i++) {
        const bool toward_zero = current != zero && ((target < current) == (current > zero));
        const bool crosses_zero = toward_zero && target != zero && ((target > zero) != (current > zero));
        const T end = crosses_zero ? zero : target;
        const T rate = toward_zero ? limit.deceleration : limit.acceleration;
        if (rate <= zero) {
            current = end;
            continue;
        }
        const T distance = std::abs(end - current);
        if (distance <= rate * remaining) {
            current = end;
            remaining -= distance / rate;
        } else {
            current += std::copysign(rate * remaining, end - current);
            break;
        }
    }
    return current;
}

} // namespace hca

#endif /* HCA_OUTPUT_FUNCTION_LIMIT_RATE_HPP_ */
