#ifndef DECORATOR_H
#define DECORATOR_H

#include <cassert>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <typeinfo>

#include "DebugDecorator.h"

void DecoratorTest();

// Basic decorator
class Unit {
    public:
    Unit(double strength, double armor) : strength_(strength), armor_(armor) {}
    virtual bool hit(Unit& target) { return attack() > target.defense(); }
    virtual double attack() = 0;
    virtual double defense() = 0;
    protected:
    double strength_;
    double armor_;
};
using Unit_ptr = std::unique_ptr<Unit>;

class Knight : public Unit {
    public:
    Knight(double strength, double armor) : Unit(strength, armor), charge_bonus_(0) {}
    double attack() { double res = strength_ + sword_bonus_ + charge_bonus_; charge_bonus_ = 0; return res; }
    double defense() { return armor_ + plate_bonus_; }
    void charge() { charge_bonus_ = 1; }
    protected:
    double charge_bonus_;
    static constexpr double sword_bonus_ = 2;
    static constexpr double plate_bonus_ = 3;
};
using Knight_ptr = std::unique_ptr<Knight>;

class Ogre : public Unit {
    public:
    using Unit::Unit;
    double attack() { return strength_ + club_penalty_; }
    double defense() { return armor_ + leather_penalty_; }
    protected:
    static constexpr double club_penalty_ = -1;
    static constexpr double leather_penalty_ = -1;
};

class Troll : public Unit {
    public:
    using Unit::Unit;
    double attack() { return strength_ + mace_bonus_; }
    double defense() { return armor_ + hide_bonus_; }
    protected:
    static constexpr double mace_bonus_ = 3;
    static constexpr double hide_bonus_ = 8;
};

template <typename To, typename From> static std::unique_ptr<To> move_cast(std::unique_ptr<From>& p) {
#ifndef NDEBUG
    auto p1 = std::unique_ptr<To>(dynamic_cast<To*>(p.release()));
    assert(p1);
    return p1;
#else
    return std::unique_ptr<To>(static_cast<To*>(p.release()));
#endif
}

template <typename U> class VeteranUnit : public U {
    public:
//    template <typename P> VeteranUnit(P&& p, double strength_bonus, double armor_bonus) :
//        U(std::move(*move_cast<U>(p))), strength_bonus_(strength_bonus), armor_bonus_(armor_bonus) {}
    VeteranUnit(U&& unit, double strength_bonus, double armor_bonus) : U(unit), strength_bonus_(strength_bonus), armor_bonus_(armor_bonus) {}
    double attack() { return U::attack() + strength_bonus_; }
    double defense() { return U::defense() + armor_bonus_; }
    private:
    double strength_bonus_;
    double armor_bonus_;
};

template <typename T, T v0> struct initialized_value {
    T v;
    initialized_value() : v(v0) {}
};

template <typename U> class DebugDecorator : public U {
    initialized_value<bool, true> decorated_;
    public:
    using U::U;
    template <typename Func, typename ... Args> auto operator()(Func func, Args&& ... args) {
        int status; char buf[1024]; size_t len = sizeof(buf);
        std::cout << "Invoking " << typeid(func).name() << " " << abi::__cxa_demangle(typeid(func).name(), buf, &len, &status) << std::endl;
        //auto res = (this->*func)(args ...); // Only if func() does not return void!
        using res_t = typename std::result_of<decltype(func)(U*, Args ...)>::type;
        report<res_t> rep(this, func, std::forward<Args>(args) ...);
        return rep();
    }
    template <typename Func, typename ... Args> auto invoke(const char* s, Func func, Args&& ... args) {
        std::cout << s << " ";
        using res_t = typename std::result_of<decltype(func)(U*, Args ...)>::type;
        report<res_t> rep(this, func, std::forward<Args>(args) ...);
        return rep();
    }
    //double attack() { return invoke("Attack", &U::attack); } // Infinite loop!
    double attack() { double res = U::attack(); std::cout << "Attack: " << res << "; "; return res; }
    double defense() { double res = U::defense(); std::cout << "Defense: " << res << "; "; return res; }
};
#endif // DECORATOR_H
