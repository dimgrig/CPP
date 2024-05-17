#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <memory>

void VisitorTest();

// ---------------------------------
// Generic visitor base
template <typename ... Types>
class Visitor;

template <typename T>
class Visitor<T> {
    public:
    virtual void visit(T* t) = 0;
};

template <typename T, typename ... Types>
class Visitor<T, Types ...> : public Visitor<Types ...> {
    public:
    using Visitor<Types ...>::visit;
    virtual void visit(T* t) = 0;
};
//
// ---------------------------------

using PetVisitor = Visitor<class Cat, class Dog>;

// ----------------------------------------------
//
template <typename Base, typename ... >
class LambdaVisitor;

template <typename Base, typename T1, typename F1>
class LambdaVisitor<Base, Visitor<T1>, F1> : private F1, public Base {
    public:
    LambdaVisitor(F1&& f1) : F1(std::move(f1)) {}
    LambdaVisitor(const F1& f1) : F1(f1) {}
    void visit(T1* t) override { return F1::operator()(t); }
};

template <typename Base, typename T1, typename ... T, typename F1, typename ... F>
class LambdaVisitor<Base, Visitor<T1, T ...>, F1, F ...> : private F1, public LambdaVisitor<Base, Visitor<T ...>, F ...> {
    public:
    LambdaVisitor(F1&& f1, F&& ... f) : F1(std::move(f1)), LambdaVisitor<Base, Visitor<T ...>, F ...>(std::forward<F>(f) ...) {}
    LambdaVisitor(const F1& f1, F&& ... f) : F1(f1), LambdaVisitor<Base, Visitor<T ...>, F ...>(std::forward<F>(f) ...) {}
    void visit(T1* t) override { return F1::operator()(t); }
};

template <typename Base, typename ... F>
auto lambda_visitor(F&& ... f) {
    return LambdaVisitor<Base, Base, F ...>(std::forward<F>(f) ...);
}
//
// ----------------------------------------------

class Pet {
    public:
    virtual ~Pet() {}
    Pet(const std::string& color) : color_(color) {}
    const std::string& color() const { return color_; }
    virtual void accept(PetVisitor& v) = 0;
    private:
    std::string color_;
};

template <typename Derived>
class Visitable : public Pet {
    public:
    using Pet::Pet; //using super class methods in derived class
    void accept(PetVisitor& v) override {
        v.visit(static_cast<Derived*>(this));
    }
};

class Cat : public Visitable<Cat> {
    using Visitable<Cat>::Visitable; //using super class methods in derived class
};

class Dog : public Visitable<Dog> {
    using Visitable<Dog>::Visitable; //using super class methods in derived class
};

class FeedingVisitor : public PetVisitor {
    public:
    void visit(Cat* c) override { std::cout << "Feed tuna to the " << c->color() << " cat" << std::endl; }
    void visit(Dog* d) override { std::cout << "Feed steak to the " << d->color() << " dog" << std::endl; }
};

class PlayingVisitor : public PetVisitor {
    public:
    void visit(Cat* c) override { std::cout << "Play with feather with the " << c->color() << " cat" << std::endl; }
    void visit(Dog* d) override { std::cout << "Play fetch with the " << d->color() << " dog" << std::endl; }
};

#endif // VISITOR_H
