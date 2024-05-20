#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <cstdlib>
#include <cassert>
#include <utility>
#include <iostream>
#include <type_traits>

#include "TestRunner.h"

void SmartPtrTest();

template <typename T>
struct DeleteByOperator {
    void operator()(T* p) const {
        delete p;
    }
};

template <typename T>
struct DeleteByFree {
    void operator()(T* p) const {
        p->~T();
        free(p);
    }
};

template <typename T>
struct DeleteDestructorOnly {
    void operator()(T* p) const {
        p->~T();
    }
};

class SmallHeap {
    public:
    SmallHeap() {}
    ~SmallHeap() {}
    void* allocate(size_t s) {
        assert(s <= size_);
        return mem_;
    }
    void deallocate(void* p) {
        assert(p == mem_);
    }
    private:
    static constexpr size_t size_ = 1024;
    char mem_[size_];
    SmallHeap(const SmallHeap&) = delete;
    SmallHeap& operator=(const SmallHeap&) = delete;
};

void* operator new(size_t s, SmallHeap* h);

template <typename T>
struct DeleteSmallHeap {
    explicit DeleteSmallHeap(SmallHeap& heap)
        : heap_(&heap) {}
    void operator()(T* p) const {
        p->~T();
        heap_->deallocate(p);
    }
    DeleteSmallHeap(DeleteSmallHeap&& other)
        : heap_(other.heap_)
    {
        other.heap_ = nullptr;
    }
    private:
    SmallHeap* heap_;
    DeleteSmallHeap(const DeleteSmallHeap&) = delete;
    DeleteSmallHeap& operator=(const DeleteSmallHeap&) = delete;
};

class NoMoveNoCopy {
    protected:
    NoMoveNoCopy() = default;
    NoMoveNoCopy(NoMoveNoCopy&&) = delete;
    NoMoveNoCopy(const NoMoveNoCopy&) = delete;
    constexpr bool must_delete() const { return true; }
};

class MoveNoCopy {
    protected:
    MoveNoCopy() = default;
    MoveNoCopy(MoveNoCopy&&) = default;
    MoveNoCopy(const MoveNoCopy&) = delete;
    constexpr bool must_delete() const { return true; }
};

class CopyRefCounted {
    protected:
    CopyRefCounted() : count_(new size_t(1)) {}
    CopyRefCounted(const CopyRefCounted& other)
        : count_(other.count_)
    {
        ++(*count_);
    }
    ~CopyRefCounted() {
        --(*count_);
        if (*count_ == 0) {
            delete count_;
        }
    }
    bool must_delete() const { return *count_ == 1; }
    private:
    size_t* count_;
};

struct NoDebug {
    template <typename P, typename T> static void construct(const P* ptr, const T* p) {}
    template <typename P, typename T> static void move(const P* ptr, const P* from, const T* p) {}
    template <typename P, typename T> static void copy(const P* ptr, const P* from, const T* p) {}
    template <typename P, typename T> static void destroy(const P* ptr, const T* p, bool must_delete) {}
};

struct Debug {
    template <typename P, typename T> static void construct(const P* ptr, const T* p) {
        std::cout << "Constructed SmartPtr at " << ptr << ", object " << static_cast<const void*>(p) << std::endl;
    }
    template <typename P, typename T> static void move(const P* ptr, const P* from, const T* p) {
        std::cout << "Moved SmartPtr at " << ptr << " from " << from << ", object " << static_cast<const void*>(p) << std::endl;
    }
    template <typename P, typename T> static void copy(const P* ptr, const P* from, const T* p) {
        std::cout << "Copied SmartPtr at " << ptr << " from " << from << ", object " << static_cast<const void*>(p) << std::endl;
    }
    template <typename P, typename T> static void destroy(const P* ptr, const T* p, bool must_delete) {
        std::cout << "Destroyed SmartPtr at " << ptr << ", object " << static_cast<const void*>(p) << (must_delete ? " is" : " is not") << " deleted" << std::endl;
    }
};

template <typename P, typename T>
struct NoRaw {
};

template <typename P, typename T>
struct ExplicitRaw {
    explicit operator T*() { return static_cast<P*>(this)->p_; }
    explicit operator const T*() const { return static_cast<const P*>(this)->p_; }
};

template <typename P, typename T>
struct ImplicitRaw {
    operator T*() { return static_cast<P*>(this)->p_; }
    operator const T*() const { return static_cast<const P*>(this)->p_; }
};

struct WithArrow {
    static constexpr bool have_arrow = true;
};

struct WithoutArrow {
    static constexpr bool have_arrow = false;
};

template <typename T,
          typename DeletionPolicy = DeleteByOperator<T>,
          typename CopyMovePolicy = NoMoveNoCopy,
          typename DebugPolicy = NoDebug,
          typename ArrowPolicy = WithArrow,
          template <typename, typename> class ConversionPolicy = ExplicitRaw
         >
class SmartPtr : private DeletionPolicy,
                 public CopyMovePolicy,
                 public ConversionPolicy<SmartPtr<T, DeletionPolicy, CopyMovePolicy, DebugPolicy, ArrowPolicy, ConversionPolicy>, T>
{
    public:
    explicit SmartPtr(T* p = nullptr,
                      DeletionPolicy&& deletion_policy = DeletionPolicy()
        ) : DeletionPolicy(std::move(deletion_policy)),
            p_(p)
    {
        DebugPolicy::construct(this, p);
    }
    SmartPtr(SmartPtr&& other)
        : DeletionPolicy(std::move(other)),
          CopyMovePolicy(std::move(other)),
          p_(other.p_)
    {
        DebugPolicy::move(this, &other, p_);
        other.release();
    }
    SmartPtr(const SmartPtr& other)
        : DeletionPolicy(other),
          CopyMovePolicy(other),
          p_(other.p_)
    {
        DebugPolicy::copy(this, &other, p_);
    }
    ~SmartPtr() {
        DebugPolicy::destroy(this, p_, CopyMovePolicy::must_delete());
        if (CopyMovePolicy::must_delete()) DeletionPolicy::operator()(p_);
    }
    void release() { p_ = NULL; }
    template <typename U = T> typename std::enable_if<ArrowPolicy::have_arrow, U*>::type operator->() { return p_; }
    template <typename U = T> typename std::enable_if<ArrowPolicy::have_arrow, const U*>::type operator->() const { return p_; }
    T& operator*() { return *p_; }
    const T& operator*() const { return *p_; }
    private:
    // Either way works.
    //friend class ConversionPolicy<SmartPtr<T, DeletionPolicy, CopyMovePolicy, ConversionPolicy>, T>;
    template<typename, typename> friend class ConversionPolicy;
    T* p_;
};

template <typename T,
          typename DebugPolicy = NoDebug
         >
using SmartPtrAdapter = SmartPtr<T, DeleteByOperator<T>, CopyRefCounted, DebugPolicy>;

#endif // SMARTPTR_H
