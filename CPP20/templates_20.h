#ifndef TEMPLATES_20_H
#define TEMPLATES_20_H

#include <algorithm>
#include <cctype>
#include <list>
#include <functional>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>
#include <utility>

#include "templates_cout.h"
#include "TestRunner.h"

void Templates20Test();

template <typename Func, typename Seq>
auto filter(Func func, const Seq& seq) {
    typedef typename Seq::value_type value_type;

    std::vector<value_type> result{};
    for (auto i : seq | std::views::filter(func)) {
        result.push_back(i);
    }

    return result;
}

template <typename Func, typename Seq>
auto map(Func func, const Seq& seq) {
    typedef typename Seq::value_type value_type;
    using return_type = decltype(func(std::declval<value_type>()));

    std::vector<return_type> result{};
    for (auto i :seq | std::views::transform(func)) {
        result.push_back(i);
    }

    return result;
}

template <typename T>
struct AlwaysTrue {
    constexpr bool operator()(const T&) const {
        return true;
    }
};

template <typename Map, typename Seq, typename Filt = AlwaysTrue<typename Seq::value_type>>
auto mapFilter(Map map, Seq seq, Filt filt = Filt()) {
    typedef typename Seq::value_type value_type;
    using return_type = decltype(map(std::declval<value_type>()));

    std::vector<return_type> result{};
    for (auto i :seq | std::views::filter(filt) | std::views::transform(map)) {
        result.push_back(i);
    }

    return result;
}

#endif // TEMPLATES_20_H
