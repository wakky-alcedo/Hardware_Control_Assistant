#ifndef HCA_OUTPUT_FUNCTION_SUPPRESS_ABS_HPP_
#define HCA_OUTPUT_FUNCTION_SUPPRESS_ABS_HPP_

namespace hca {

/**
 *
 * @tparam T
 * @param value
 * @param max_abs_value
 * @return
 */
template <typename T> T suppress_abs(T value, T max_abs_value){
    max_abs_value = std::abs(max_abs_value);
    if (value > max_abs_value) {
        return max_abs_value;
    }else if (value < - max_abs_value) {
        return - max_abs_value;
    }else {
        return value;
    }
}

} // namespace hca

#endif /* HCA_OUTPUT_FUNCTION_SUPPRESS_ABS_HPP_ */
