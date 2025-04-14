#ifndef DEBUGDECORATOR_H
#define DEBUGDECORATOR_H

#include <iostream>
#include <string>
#include <mutex>

using std::cout;
using std::endl;

void DebugDecoratorTest();

template <typename Res> struct report {
    Res res;
    template <typename P, typename Func, typename ... Args>
        report(P p, Func func, Args&& ... args) :
            res((p->*func)(std::forward<Args>(args) ...)) {
                std::cout << "Result: " << res << std::endl;
            }
    Res operator()() { return res; }
};

template <> struct report<void> {
    template <typename P, typename Func, typename ... Args>
        report(P p, Func func, Args&& ... args) {
            (p->*func)(std::forward<Args>(args) ...);
            std::cout << "Done" << std::endl;
        }
    void operator()() {}
};

template <typename Callable> class CallableDebugDecorator {
    public:
    CallableDebugDecorator(const Callable& c, const char* s) : c_(c), s_(s) {}
    template <typename ... Args> auto operator()(Args&& ... args) const {
        cout << "Invoking " << s_ << endl;
        using res_t = typename std::result_of<Callable(Args ...)>::type;
        report<res_t> res(c_, std::forward<Args>(args) ...);
        return res();
    }

    private:
    const Callable& c_;
    const std::string s_;
};

template <typename Callable>
auto decorate_debug(const Callable& c, const char* s) {
    return CallableDebugDecorator<Callable>(c, s);
}

template <typename Callable> class LockDecorator {
    public:
    LockDecorator(const Callable& c, std::mutex& m) : c_(c), m_(m) {}
    template <typename ... Args> auto operator()(Args&& ... args) const {
        std::lock_guard<std::mutex> l(m_);
        return c_(std::forward<Args>(args) ...);
    }

    private:
    const Callable& c_;
    std::mutex& m_;
};

template <typename Callable>
auto decorate_lock(const Callable& c, std::mutex& m) {
    return LockDecorator<Callable>(c, m);
}

#endif // DEBUGDECORATOR_H
