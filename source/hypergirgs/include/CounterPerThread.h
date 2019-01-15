#pragma once

#include <algorithm>
#include <numeric>
#include <omp.h>
#include <vector>
#include <utility>

template <typename T>
class CounterPerThread {
public:
    using value_type = T;

    explicit  CounterPerThread(unsigned maxThreads = omp_get_max_threads())
        : per_thread_(maxThreads)
    {
        for(auto& x : per_thread_)
            x.first = value_type{0};
    }

    void add(unsigned int tid, value_type x = {1}) {
        assert(tid < per_thread_.size());
        per_thread_[tid].first += x;
    }

    value_type total() const {
        return std::accumulate(
            per_thread_.cbegin(), per_thread_.cend(), value_type{},
            [] (value_type val, const value_with_padding& x) {return val + x.first;}
        );
    }

private:
    static constexpr size_t kCachelineSize = 64;
    // chosen, s.t. each counter hits a different spot in cachelines
    static constexpr size_t kPaddingSize = kCachelineSize - (sizeof(value_type) % kCachelineSize) + 1;
    using value_with_padding = std::pair<value_type, char[kPaddingSize]>;

    std::vector<value_with_padding> per_thread_;
};
