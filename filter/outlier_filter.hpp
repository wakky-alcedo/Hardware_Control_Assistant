#ifndef FILTER_OUTLIER_FILTER_HPP_
#define FILTER_OUTLIER_FILTER_HPP_

#include <cstdint>
#include <valarray>
#include <limits>
#include "filter_interface.hpp"

namespace hca {

class OutlierFilter : public FilterInterface {
private:
    float diff_of_outlier;
    float last_value;
    bool is_reseted;
public:
    OutlierFilter();
    void init(const float diff_of_outlier);
    void update(float value, float base_value);
    void update(float value) override;
    void reset();
};

} /* namespace hca */

#endif /* FILTER_OUTLIER_FILTER_HPP_ */
