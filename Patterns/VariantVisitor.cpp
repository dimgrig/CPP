#include "VariantVisitor.h"

void VariantVisitorNI(const QVariant & val) {
    withConversion(val, [](int v){
        std::cout << "got int " << v << std::endl;
    })
    || withConversion(val, [](const QString & s){
        std::cout << "got string " << s.toStdString() << std::endl;
    })
    || withConversion(val, [](const Foo & f){
        std::cout << "got Foo " << f << std::endl;
    })
    || withConversion(val, [](const Value & v){
        std::cout << "got Value " << v << std::endl;
    });;
}

QString VariantVisitorToString(const QVariant & variant) {
    QString res;
    withConversion(variant, [&](int v){
        res = QString::number(v);
    })
    || withConversion(variant, [&](const QString & s){
        res = s;
    })
    || withConversion(variant, [&](const Foo & f){
        res = QString::number(f.a);
    })
    || withConversion(variant, [&](const Value & v){
        res = QString(v.get_string_fit_dimension().c_str());
    });;
    return res;
}

bool VariantVisitor_compare(const QVariant & variant) {
    bool res = false;
    withConversion(variant, [&](int v){
        res = (v == 1);
    })
    || withConversion(variant, [&](const QString & s){
        res = (s == "foo");
    })
    || withConversion(variant, [&](const Foo & f){
        res = (f.a == 10);
    })
    || withConversion(variant, [&](const Value & v){
        res = (v == Value("Uси", 10, "В", 0));
    });;
    return res;
}

void VariantVisitorTest() {
    std::cout << "qMetaTypeId Foo " << qMetaTypeId<Foo>() << std::endl;
    std::cout << "qMetaTypeId Value " << qMetaTypeId<Value>() << std::endl;
    //std::cout << "qRegisterMetaType" << qRegisterMetaType<Foo>("Foo") << std::endl;
    {
        visit(QVariant{1}, VariantVisitor{});
        visit(QVariant{QStringLiteral("foo")}, VariantVisitor{});
        visit(QVariant::fromValue(Foo{10}), VariantVisitor{});
    }
    {
        VariantVisitorNI(QVariant{1});
        VariantVisitorNI(QVariant{QStringLiteral("foo")});
        VariantVisitorNI(QVariant::fromValue(Foo{10}));
        VariantVisitorNI(QVariant::fromValue(Value{"Uси", 10, "В", 0}));
    }
    {
        {
            QString str = VariantVisitorToString(QVariant{1});
            std::cout << str.toStdString() << std::endl;
        }
        {
            QString str = VariantVisitorToString(QVariant{QStringLiteral("foo")});
            std::cout << str.toStdString() << std::endl;
        }
        {
            QString str = VariantVisitorToString(QVariant::fromValue(Foo{10}));
            std::cout << str.toStdString() << std::endl;
        }
        {
            QString str = VariantVisitorToString(QVariant::fromValue(Value{"Uси", 10, "В", 0}));
            std::cout << str.toStdString() << std::endl;
        }
    }
    {
        {
            bool res = VariantVisitor_compare(QVariant{1});
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant{QStringLiteral("foo")});
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant::fromValue(Foo{10}));
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant::fromValue(Value{"Uси", 10, "В", 0}));
            std::cout << res << std::endl;
        }
    }
    {
        {
            bool res = VariantVisitor_compare(QVariant{100});
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant{QStringLiteral("bar")});
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant::fromValue(Foo{1000}));
            std::cout << res << std::endl;
        }
        {
            bool res = VariantVisitor_compare(QVariant::fromValue(Value{"Iс", 0, "А", 0}));
            std::cout << res << std::endl;
        }
    }
}
