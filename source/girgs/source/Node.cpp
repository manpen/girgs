
#include <girgs/Node.h>

#include <cmath>
#include <cassert>
#include <algorithm>


double girgs::distance(const std::vector<double>& a, const std::vector<double>& b) {
    assert(a.size() == b.size());
    auto result = 0.0;
    for(auto d=0u; d<a.size(); ++d){
        auto dist = std::abs(a[d] - b[d]);
        dist = std::min(dist, 1.0-dist);
        result = std::max(result, dist);
    }
    return result;
}
