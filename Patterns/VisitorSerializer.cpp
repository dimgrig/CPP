#include "VisitorSerializer.h"

#include "TestRunner.h"

void VisitorSerializerTest() {
    Line l(Point(1, 2), Point(5, 2));
    Circle c(Point(1, 2), 3);
    Intersection<Circle, Circle> x(Circle(Point(1, 2), 3), Circle(Point(2, 1), 2));
    double y(11);

//    std::cout << "Line l:\n"; write(l);
//    std::cout << "Circle c:\n"; write(c);
//    std::cout << "Intersection x:\n"; write(x);
//    std::cout << "y:\n"; write(y);

    {
        std::string s;
        serialize(l, s);
        serialize(c, s);
        serialize(x, s);
        serialize(y, s);

        Line l1;
        Circle c1;
        Intersection<Circle, Circle> x1;
        double y1(0);
        deserialize(s, l1, c1, x1, y1);
//        std::cout << "Line l1:\n"; write(l1);
//        std::cout << "Circle c1:\n"; write(c1);
//        std::cout << "Intersection x1:\n"; write(x1);
//        std::cout << "y1:\n"; write(y1);

        ASSERT_EQUAL(l1, l);
        ASSERT_EQUAL(c1, c);
        ASSERT_EQUAL(x1, x);
        ASSERT_EQUAL(y1, y);
    }
    {
        char buffer[1024];
        serialize(buffer, sizeof(buffer), l, c, x, y);

        Line l2;
        Circle c2;
        Intersection<Circle, Circle> x2;
        double y2(0);
        deserialize(buffer, sizeof(buffer), l2, c2, x2, y2);
//        std::cout << "Line l2:\n"; write(l2);
//        std::cout << "Circle c2:\n"; write(c2);
//        std::cout << "Intersection x2:\n"; write(x2);
//        std::cout << "y2:\n"; write(y2);

        ASSERT_EQUAL(l2, l);
        ASSERT_EQUAL(c2, c);
        ASSERT_EQUAL(x2, x);
        ASSERT_EQUAL(y2, y);
    }
}
