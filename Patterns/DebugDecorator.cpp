#include "DebugDecorator.h"

struct R {
    int value() const { return rand(); }
};

void DebugDecoratorTest() {
    std::mutex m;

//    auto incr = decorate_debug([](int& x) { ++x; }, "++x");
//    int i = 0;
//    incr(i);

//    R r;
//    auto f0 = decorate_lock([&]() { return r.value(); }, m);
//    f0(); f0();

//    auto f1 = decorate_lock(decorate_debug([](int i) { return i; }, "i->i"), m);
//    f1(5);

//    auto f2 = decorate_debug(decorate_lock([](int i, int j) { return i + j; }, m), "i+j");
//    f2(5, 3);


}
