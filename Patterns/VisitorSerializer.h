#ifndef VISITORSERIALIZER_H
#define VISITORSERIALIZER_H

#include <iostream>
#include <sstream>
#include <exception>
#include <string.h>

void VisitorSerializerTest();

class Point {
    public:
    Point() = default;
    Point(double x, double y) : x_(x), y_(y) {}
    template <typename This, typename Visitor>
    static void accept(This& t, Visitor& v) {
        v(t.x_);
        v(t.y_);
    }
    private:
    double x_;
    double y_;

    friend bool operator==(const Point &lhs, const Point &rhs) {
        return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
    }
    friend std::ostream& operator<<(std::ostream &os, const Point &r) {
        os << r.x_ << r.y_;
        return os;
    }
};

class Circle {
    public:
    Circle() = default;
    Circle(Point c, double r) : c_(c), r_(r) {}
    template <typename This, typename Visitor>
    static void accept(This& t, Visitor& v) {
        v(t.c_);
        v(t.r_);
    }
    private:
    Point c_;
    double r_;

    friend bool operator==(const Circle &lhs, const Circle &rhs) {
        return (lhs.c_ == rhs.c_) && (lhs.r_ == rhs.r_);
    }
    friend std::ostream& operator<<(std::ostream &os, const Circle &r) {
        os << r.c_ << r.r_;
        return os;
    }
};

class Line {
    public:
    Line() = default;
    Line(Point p1, Point p2) : p1_(p1), p2_(p2) {}
    template <typename This, typename Visitor>
    static void accept(This& t, Visitor& v) {
        v(t.p1_);
        v(t.p2_);
    }
    private:
    Point p1_;
    Point p2_;

    friend bool operator==(const Line &lhs, const Line &rhs) {
        return (lhs.p1_ == rhs.p1_) && (lhs.p2_ == rhs.p2_);
    }
    friend std::ostream& operator<<(std::ostream &os, const Line &r) {
        os << r.p1_ << r.p2_;
        return os;
    }
};

template <typename G1, typename G2>
class Intersection {
    public:
    Intersection() = default;
    Intersection(G1 g1, G2 g2) : g1_(g1), g2_(g2) {}
    template <typename This, typename Visitor>
    static void accept(This& t, Visitor& v) {
        v(t.g1_);
        v(t.g2_);
    }
    private:
    G1 g1_;
    G2 g2_;

    friend bool operator==(const Intersection &lhs, const Intersection &rhs) {
        return (lhs.g1_ == rhs.g1_) && (lhs.g2_ == rhs.g2_);
    }
    friend std::ostream& operator<<(std::ostream &os, const Intersection &r) {
        os << r.g1_ << r.g2_;
        return os;
    }
};

class StreamVisitor {
    public:
    StreamVisitor(std::ostream& out) : out_(out), indent_(0) {}
    void operator()(double x) { indent(); out_ << x << std::endl; }
    template <typename T> void operator()(const T& t) {
        indent_ += 2;
        T::accept(t, *this);
        indent_ -= 2;
    }

    private:
    void indent() { for (int i = 0; i < indent_; ++i) out_ << " "; }
    std::ostream& out_;
    int indent_;
};

template <typename T>
void write(const T& t, std::ostream& out = std::cout) {
    StreamVisitor v(out);
    v(t);
}

class StringSerializeVisitor {
    public:
    void operator()(double x) { S << x << " "; }
    template <typename T> void operator()(const T& t) { T::accept(t, *this); }

    std::string str() const { return S.str(); }
    private:
    std::stringstream S;
};

template <typename T>
void serialize(const T& t, std::string& s) {
    StringSerializeVisitor v;
    v(t);
    s += v.str();
}

class StringDeserializeVisitor {
    public:
    StringDeserializeVisitor(const std::string& s) { S.str(s); }
    void operator()(double& x) { S >> x; }
    template <typename T> void operator()(T& t) { T::accept(t, *this); }
    private:
    std::stringstream S;
};

template <typename V, typename T>
void visitation(V& v, T& t) {
    v(t);
}
template <typename V, typename T, typename ... U>
void visitation(V& v, T& t, U& ... u) {
    v(t);
    visitation(v, u ...);
}
template <typename ... U>
void deserialize(const std::string& s, U& ... u) {
    StringDeserializeVisitor v(s);
    visitation(v, u ...);
}

class BinarySerializeVisitor {
    public:
    BinarySerializeVisitor(char* buffer, size_t size) : buf_(buffer), size_(size) {
    }
    void operator()(double x) {
        if (size_ < sizeof(x))
            throw std::runtime_error("Buffer overflow");
        memcpy(buf_, &x, sizeof(x));
        buf_ += sizeof(x);
        size_ -= sizeof(x);
    }
    template <typename T> void operator()(const T& t) { T::accept(t, *this); }

    private:
    char* buf_;
    size_t size_;
};

template <typename ... U>
void serialize(char* buffer, size_t size, U& ... u) {
    BinarySerializeVisitor v(buffer, size);
    visitation(v, u ...);
}


class BinaryDeserializeVisitor {
    public:
    BinaryDeserializeVisitor(const char* buffer, size_t size) : buf_(buffer), size_(size) {}
    void operator()(double& x) {
        if (size_ < sizeof(x))
            throw std::runtime_error("Buffer overflow");
        memcpy(&x, buf_, sizeof(x));
        buf_ += sizeof(x);
        size_ -= sizeof(x);
    }
    template <typename T> void operator()(T& t) { T::accept(t, *this); }
    private:
    const char* buf_;
    size_t size_;
};

template <typename ... U>
void deserialize(char* buffer, size_t size, U& ... u) {
    BinaryDeserializeVisitor v(buffer, size);
    visitation(v, u ...);
}

#endif // VISITORSERIALIZER_H
