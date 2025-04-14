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

#include "Logger.h"
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
auto map_filter(Map map, Seq seq, Filt filt = Filt()) {
    typedef typename Seq::value_type value_type;
    using return_type = decltype(map(std::declval<value_type>()));

    std::vector<return_type> result{};
    for (auto i :seq | std::views::filter(filt) | std::views::transform(map)) {
        result.push_back(i);
    }

    return result;
}

//вид контейнера
template <std::ranges::input_range Range>
requires std::ranges::view<Range>
class ContainerView : public std::ranges::view_interface<ContainerView<Range>> {
public:
    ContainerView() = default;

    constexpr ContainerView(Range r) :
        range_(std::move(r)),
        begin_(std::begin(r)),
        end_(std::end(r))
    {};

    constexpr auto begin() const {return begin_;};
    constexpr auto end() const {return end_;};

    constexpr auto to_vector() {
        using T = std::decay_t<std::ranges::range_value_t<Range>>;
        return std::vector<T>{this->begin(), this->end()};
    }
    constexpr auto to_string() {
        return std::string{this->begin(), this->end()};
    }
private:
    Range range_{};
    std::ranges::iterator_t<Range> begin_{std::begin(range_)};
    std::ranges::iterator_t<Range> end_{std::begin(range_)};
};

template<typename Range>
ContainerView(Range&& range) -> ContainerView<std::ranges::views::all_t<Range>>;

template <class T>
std::ostream& operator<<(std::stringstream& os, const ContainerView<T>& c) {
    return os << "[" << Join(c, ',') << "]";
}

template <class T>
QDebug operator<<(QDebug os, const ContainerView<T>& c) {
    return os << "[" << QString::fromStdString(Join(c, ',')) << "]";
}

//c++ 17 returne type resolver
class from_string {
public:
    from_string(const char *str) : _str(str) {}
    template <typename type>
    operator type(){
        //std::cout << typeid(type).name() << std::endl;
        if constexpr(std::is_same_v<type, float>) {
            return stof(_str);
        } else if (std::is_same_v<type, int>) {
            return stoi(_str);
        }
    }
private:
    const std::string _str;
};

#endif // TEMPLATES_20_H
