#ifndef ADAPTER_H
#define ADAPTER_H

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

void AdapterTest();

struct much_less {
    static constexpr double tolerance = 2;
    template <typename T> bool operator()(T x, T y) {
        return x < y && std::abs(x - y) > tolerance*std::max(std::abs(x), std::abs(y));
    }
};

template<typename RandomIt> void sort_much_less(RandomIt first, RandomIt last) {
    auto f = std::bind(std::sort<RandomIt, much_less>, std::placeholders::_1, std::placeholders::_2, much_less());
    f(first, last, much_less());
}

template<typename Container> void sort_much_less(Container& c) {
    std::sort(c.begin(), c.end(), much_less());
}

template <typename T> class Buffer {
    public:
    explicit Buffer(size_t N) : N_(N), buffer_(new T[N_]) {}
    ~Buffer() { delete [] buffer_; }
    size_t size() const { return N_; }
    T& operator[](size_t i) { return buffer_[i]; }
    const T& operator[](size_t i) const { return buffer_[i]; }
    T* begin() const { return buffer_; }
    T* end() const { return buffer_ + N_; }

    private:
    const size_t N_;
    T* const buffer_;
};

//ambigous with template cout
//template <template <typename> class Container, typename T>
//std::ostream& operator<<(std::ostream& out, const Container<T>& c) {
//    bool first = true;
//    for (auto x : c) {
//        if (!first) out << ", ";
//        first = false;
//        out << x;
//    }
//    return out;
//}

//template <typename T> class vector1 : public std::vector<T> {
//    using base_t = std::vector<T>;
//    public:
//    using base_t::base_t;
//    //using std::vector<T>::vector;     // This works too
//};
////template <typename T> using vector1 = std::vector<T>; // Not deduced by template deduction!

//template <typename T> class array1 : public std::array<T, 10> {
//    using base_t = std::array<T, 10>;
//    public:
//    using base_t::base_t;
//};


template <typename T> class ValueAdapter {
    public:
    typedef T basic_type;
    typedef ValueAdapter value_type;
    explicit ValueAdapter() : val_(T()) {}
    explicit ValueAdapter(T v) : val_(v) {}
    ValueAdapter(const ValueAdapter& rhs) : val_(rhs.val_) {}
    ValueAdapter& operator=(ValueAdapter rhs) { val_ = rhs.val_; return *this; }
    ValueAdapter& operator=(basic_type rhs) { val_ = rhs; return *this; }
    friend std::ostream& operator<<(std::ostream& out, ValueAdapter x) { out << x.val_; return out; }
    friend std::istream& operator>>(std::istream& in, ValueAdapter& x) { in >> x.val_; return in; }

    protected:
    T val_;
};

template <typename V> class Comparable : public V {
    public:
    using V::V;
    typedef typename V::value_type value_type;
    typedef typename value_type::basic_type basic_type;
    Comparable(value_type v) : V(v) {}
    friend bool operator==(Comparable lhs, Comparable rhs) { return lhs.val_ == rhs.val_; }
    friend bool operator!=(Comparable lhs, Comparable rhs) { return lhs.val_ != rhs.val_; }
    friend bool operator==(Comparable lhs, basic_type rhs) { return lhs.val_ == rhs; }
    friend bool operator==(basic_type lhs, Comparable rhs) { return lhs == rhs.val_; }
    friend bool operator!=(Comparable lhs, basic_type rhs) { return lhs.val_ != rhs; }
    friend bool operator!=(basic_type lhs, Comparable rhs) { return lhs != rhs.val_; }
};

template <typename V> class Ordered : public V {
    public:
    using V::V;
    typedef typename V::value_type value_type;
    typedef typename value_type::basic_type basic_type;
    Ordered(value_type v) : V(v) {}
    friend bool operator<(Ordered lhs, Ordered rhs) { return lhs.val_ < rhs.val_; }
    friend bool operator<(basic_type lhs, Ordered rhs) { return lhs < rhs.val_; }
    friend bool operator<(Ordered lhs, basic_type rhs) { return lhs.val_ < rhs; }
    friend bool operator<=(Ordered lhs, Ordered rhs) { return lhs.val_ <= rhs.val_; }
    friend bool operator<=(basic_type lhs, Ordered rhs) { return lhs <= rhs.val_; }
    friend bool operator<=(Ordered lhs, basic_type rhs) { return lhs.val_ <= rhs; }
    friend bool operator>(Ordered lhs, Ordered rhs) { return lhs.val_ > rhs.val_; }
    friend bool operator>(basic_type lhs, Ordered rhs) { return lhs > rhs.val_; }
    friend bool operator>(Ordered lhs, basic_type rhs) { return lhs.val_ > rhs; }
    friend bool operator>=(Ordered lhs, Ordered rhs) { return lhs.val_ >= rhs.val_; }
    friend bool operator>=(basic_type lhs, Ordered rhs) { return lhs >= rhs.val_; }
    friend bool operator>=(Ordered lhs, basic_type rhs) { return lhs.val_ >= rhs; }
};

template <typename V> class Addable : public V {
    public:
    using V::V;
    typedef typename V::value_type value_type;
    typedef typename value_type::basic_type basic_type;
    Addable(value_type v) : V(v) {}
    friend Addable operator+(Addable lhs, Addable rhs) { return Addable(lhs.val_ + rhs.val_); }
    friend Addable operator+(Addable lhs, basic_type rhs) { return Addable(lhs.val_ + rhs); }
    friend Addable operator+(basic_type lhs, Addable rhs) { return Addable(lhs + rhs.val_); }
    friend Addable operator-(Addable lhs, Addable rhs) { return Addable(lhs.val_ - rhs.val_); }
    friend Addable operator-(Addable lhs, basic_type rhs) { return Addable(lhs.val_ - rhs); }
    friend Addable operator-(basic_type lhs, Addable rhs) { return Addable(lhs - rhs.val_); }
};

template <typename V> class Multipliable : public V {
    public:
    using V::V;
    typedef typename V::value_type value_type;
    typedef typename value_type::basic_type basic_type;
    Multipliable(value_type v) : V(v) {}
    friend Multipliable operator*(Multipliable lhs, Multipliable rhs) { return Multipliable(lhs.val_ * rhs.val_); }
    friend Multipliable operator*(Multipliable lhs, basic_type rhs) { return Multipliable(lhs.val_ * rhs); }
    friend Multipliable operator*(basic_type lhs, Multipliable rhs) { return Multipliable(lhs * rhs.val_); }
    friend Multipliable operator/(Multipliable lhs, Multipliable rhs) { return Multipliable(lhs.val_ / rhs.val_); }
    friend Multipliable operator/(Multipliable lhs, basic_type rhs) { return Multipliable(lhs.val_ / rhs); }
    friend Multipliable operator/(basic_type lhs, Multipliable rhs) { return Multipliable(lhs / rhs.val_); }
};

#endif // ADAPTER_H
