#ifndef HCA_OUTPUT_RATE_LIMITER_HPP_
#define HCA_OUTPUT_RATE_LIMITER_HPP_

#include "function_limit_rate.hpp"

namespace hca {

/**
 * 出力 (モータのデューティなど) を，変化の速さの上限を守りながら目標値に近づける．
 * limit_rate() に今の値を覚えさせたもの．目標値は毎周期変えてよい．
 * @tparam T 値の型 (浮動小数点数)
 */
template <typename T> class RateLimiter {
private:
    RateLimit<T> limit;
    T value;

public:
    /**
     * @param limit 変化の速さの上限
     * @param initial_value 初期値
     */
    explicit RateLimiter(const RateLimit<T>& limit, T initial_value = static_cast<T>(0))
        : limit(limit), value(initial_value) {}

    /**
     * dt 秒だけ目標値に近づける
     * @param target 目標値
     * @param dt 前回からの経過時間 [s]
     * @return 近づけた値
     */
    T update(T target, T dt) {
        value = limit_rate(value, target, limit, dt);
        return value;
    }

    /**
     * 制限を無視して値を設定する (非常停止で 0 にするときなど)
     * @param new_value 新しい値
     */
    void reset(T new_value = static_cast<T>(0)) { value = new_value; }

    /** 今の値 */
    T get() const { return value; }
};

} // namespace hca

#endif /* HCA_OUTPUT_RATE_LIMITER_HPP_ */
