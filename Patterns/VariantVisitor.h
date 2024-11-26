#ifndef VARIANTVISITOR_H
#define VARIANTVISITOR_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

#include <QtCore>
#include <QMetaType>

#include "Value.h"

void VariantVisitorTest();

//https://stackoverflow.com/questions/38071414/qvariants-visitor-pattern-without-manual-type-testing-and-casting


struct Foo {
    int a;
    Foo() = default;
    ~Foo() = default;
    Foo(const Foo &) = default;
    Foo &operator=(const Foo &) = default;

    explicit Foo(int a) : a(a) {};

    friend QDebug operator<<(QDebug debug, const Foo & f) {
        return debug << f.a;
    }
    friend std::ostream& operator<<(std::ostream &os, const Foo & f) {
        return os << f.a;
    }
};

Q_DECLARE_METATYPE(Foo)

struct VariantVisitor
{
   Q_GADGET
   Q_INVOKABLE void visit(int i) { std::cout << "got int " << i << std::endl; }
   Q_INVOKABLE void visit(const QString & s) { std::cout << "got string " << s.toStdString() << std::endl; }
   Q_INVOKABLE void visit(const Foo & f) { std::cout << "got foo " << f << std::endl; }
};

template <typename V>
bool visit(const QVariant & variant, const V & visitor) {
   auto & metaObject = V::staticMetaObject;
   for (int i = 0; i < metaObject.methodCount(); ++i) {
        auto method = metaObject.method(i);
        if (method.parameterCount() != 1)
            continue;
        auto arg0Type = method.parameterType(0);
        if (variant.type() != (QVariant::Type)arg0Type)
            continue;
        QGenericArgument arg0{variant.typeName(), variant.constData()};
        if (method.invokeOnGadget((void*)&visitor, arg0))
            return true;
   }
   return false;
}



template <typename T>
struct func_traits : public func_traits<decltype(&T::operator())> {};

template <typename C, typename Ret, typename... Args>
struct func_traits<Ret(C::*)(Args...) const> {
   using result_type = Ret;
   template <std::size_t i>
   struct arg {
      using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
   };
};

template <typename F> bool withConversion(const QVariant & val, F && fun) {
   using traits = func_traits<typename std::decay<F>::type>;
   using arg0_t = typename std::decay<typename traits::template arg<0>::type>::type;
   //std::cout << val.type() << "   " << val.userType() << "   " << (QVariant::Type)qMetaTypeId<arg0_t>() << std::endl;
   if (val.userType() == (QVariant::Type)qMetaTypeId<arg0_t>()) {
      fun(val.value<arg0_t>());
      return true;
   }
   return false;
}

void VariantVisitorNI(const QVariant & val);

#endif // VARIANTVISITOR_H
