#ifndef TEMPLATETRICKS_H
#define TEMPLATETRICKS_H

#include "Logger.h"

void TemplateTricksTest();

template <typename T>
class ClassWithPrivateMembers {
public:
    ClassWithPrivateMembers() {};

    friend T; // не friend class T
private:
    int private_int = 123456789;
};


class TemplateFriend {
public:
    void print(const ClassWithPrivateMembers<TemplateFriend>& c) {
        qCDebug(logDebug) << "ClassWithPrivateMembers access success" << c.private_int; // TemplateFriend is friend of A
    }
};

template <typename T>
class TemplateClassWithStaticMember
{
public:
    static int size() {
        return sz;
    }
    static int sz;
    T value;
};

template <typename T>
int TemplateClassWithStaticMember<T>::sz = 0; // дефолтное значение для всех экземпляров шаблонов


#endif // TEMPLATETRICKS_H
