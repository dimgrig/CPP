#include "Visitor.h"

void walk(Pet& p) {
    auto v(lambda_visitor<PetVisitor>(
             [](Cat* c) { std::cout << "Walk Let the " << c->color() << " cat out" << std::endl; },
             [](Dog* d) { std::cout << "Walk Take the " << d->color() << " dog for a walk" << std::endl; }
    ));
    p.accept(v);
}

void VisitorTest() {
    std::unique_ptr<Pet> c(new Cat("orange"));
    std::unique_ptr<Pet> d(new Dog("brown"));

    FeedingVisitor fv;
    c->accept(fv);
    d->accept(fv);

    PlayingVisitor pv;
    c->accept(pv);
    d->accept(pv);

    walk(*c);
    walk(*d);
}
