#include "SmartPtr.h"

void* operator new(size_t s, SmallHeap* h) {
    return h->allocate(s);
}

struct S0 {};
struct S1 {
    int i;
    explicit S1(int i) : i(i) {}
};

void SmartPtrTest() {
    {
        //debug policy
        {
            SmartPtrAdapter<int, Debug> p{new int(42)};
            ASSERT_EQUAL(*p, 42);
            auto p1(p);
            ASSERT_EQUAL(*p1, 42);
            {
                auto p2(p);
                ASSERT_EQUAL(*p2, 42);
            }
            ASSERT_EQUAL(*p, 42);
            ASSERT_EQUAL(*p1, 42);
        }
    }
    {
        //enable if arrow policy
        {
            SmartPtr<S1> p(new S1(42));
            ASSERT_EQUAL(p->i, 42);
            //auto p1(std::move(p)); // Does not compile
        }
        {
            SmartPtr<S1, DeleteByOperator<S1>, CopyRefCounted, NoDebug, WithoutArrow> p{new S1(42)};
            //std::cout << p->i << std::endl; // Does not compile
            auto p1(std::move(p));
            ASSERT_EQUAL((*p1).i, 42);
        }
    }
    {
        //operator *
        {
            SmartPtr<int> p(new int(42));
            ASSERT_EQUAL(*p, 42);
            int* p1(p);
            ASSERT_EQUAL(*p1, 42);
            //int* p2 = p; // Does not compile
        }
        {
            SmartPtr<int, DeleteByOperator<int>, NoMoveNoCopy, NoDebug, WithoutArrow, ImplicitRaw> p(new int(42));
            ASSERT_EQUAL(*p, 42);
            int* p1(p);
            ASSERT_EQUAL(*p1, 42);
            //int* p2 = p; // Does not compile
        }
        {
            SmartPtr<int, DeleteByOperator<int>, NoMoveNoCopy, NoDebug, WithoutArrow, NoRaw> p(new int(42));
            ASSERT_EQUAL(*p, 42);
            //int* p1(p); // Does not compile
            //int* p2 = p; // Does not compile
        }
    }
}
