#ifndef VALUE_H
#define VALUE_H

#include "enums.h"
#include "mixins.h"

#include "Logger.h"
#include "TestRunner.h"

#include "templates.h"

#include "Switches.h"

#include <memory>

void ValueTest();

class Value : public CopyMoveBase, public not_equal<Value>  {
public:
    Value();
    Value(std::string name, double value, std::string standardUnit, double tolerance);
    ~Value();

    void set_name(std::string name) {
        _name = name;
        //_signal = SignalName_from_text(_name.c_str());
    };
    void set_value(double value) {_value = value;};
    void set_value_absolute(double value);
    void set_value(std::string name, double value, std::string standardUnit, double tolerance) {
        _name = name; _value = value; _standardUnit = standardUnit; _tolerance = tolerance;
    };
    void set_su(std::string standardUnit) {_standardUnit = standardUnit;};
    void set_tolerance(double tolerance) {_tolerance = tolerance;};

    std::string get_name() const {return _name;};
    double get_tolerance() const {return _tolerance;};

    void from_string(std::string value_str);
    std::string get_string_fit_dimension(bool fixed = true, int precision = 3, std::string more_less_equal_sign = "=", bool name = true) const;
    std::string get_string_absolute(bool fixed = true, int precision = 3, std::string more_less_equal_sign = "=", bool name = true) const;
    std::string get_string_fit_su(std::string su_str, bool fixed = true, int precision = 3, std::string more_less_equal_sign = "=", bool name = true) const;

    double get_value() const {return _value;};
    std::string get_su() const {return _standardUnit;};
    double get_value_fit_dimension() const;
    std::string get_su_fit_dimension() const;
    double get_value_absolute() const;
    std::string get_su_absolute() const;
    double get_value_fit_su(std::string su_str) const;

    void set_signal(SignalName signal) {_signal = signal;};
    void set_range(int range) {_range = range;};
    void set_range_calculated(int range) {_range_calculated = range;};
    void set_channel(int channel) {_channel = channel;};
    void set_calibrator_channel_number(int calibrator_channel_number) {_calibrator_channel_number = calibrator_channel_number;};
    void set_switches(std::shared_ptr<Switches> switches) {_switches = switches;};
    void set_polynom_v(std::vector<double> polynom_v) {_polynom_v = polynom_v;};

    SignalName get_signal() const {return _signal;};
    int get_range() const {return _range;};
    int get_range_calculated() const {
        if (_range == 0) {
            return _range_calculated;
        } else {
            return _range;
        }};
    int get_channel() const {return _channel;};
    int get_calibrator_channel_number() const {return _calibrator_channel_number;};
    uint32_t get_switches() const {return _switches->get_switches();};
    std::shared_ptr<Switches> get_switches_ptr() const {return _switches;};
    std::vector<double> get_polynom_v() const {return _polynom_v;};

    Value abs() const;
    bool equal_unit(std::string standardUnit) const;

    friend inline bool operator>(const Value& lhs, const Value& rhs) {
        if (std::abs(lhs.scale_value() - rhs.scale_value()) < value_epsilon) {
            return false;
        }
        return lhs.scale_value() > rhs.scale_value();
    }
    friend inline bool operator<(const Value& lhs, const Value& rhs) {
        if (std::abs(lhs.scale_value() - rhs.scale_value()) < value_epsilon) {
            return false;
        }
        return !(lhs.scale_value() > rhs.scale_value());
    }
    friend inline bool operator>=(const Value& lhs, const Value& rhs) {
        if (std::abs(lhs.scale_value() - rhs.scale_value()) < value_epsilon) {
            return true;
        }
        return lhs.scale_value() >= rhs.scale_value();
    }
    friend inline bool operator<=(const Value& lhs, const Value& rhs) {
        if (std::abs(lhs.scale_value() - rhs.scale_value()) < value_epsilon) {
            return true;
        }
        return !(lhs.scale_value() >= rhs.scale_value());
    }

    friend QDebug operator<<(QDebug os, const Value& r);
    friend std::ostream& operator<<(std::ostream &os, const Value &r);
    friend bool operator==(const Value &lhs, const Value &rhs);
private:

    double scale_value() const;
    void scale_value_clear_dimension();
    //double get_scaled_value() const {return scale_value();};
    void fit_dimension();

    std::string get_string(bool fixed = true, int precision = 3, std::string more_less_equal_sign = "=", bool name = true) const;

    std::string _name;
    double _value = 0.0;
    std::string _standardUnit;
    double _tolerance = 0.0;

    SignalName _signal = Signal_Undefined;
    int _range = 0;
    int _range_calculated = 0;
    int _channel = 0; //1 - baza  //2 - collector
    int _calibrator_channel_number = 0;
    std::shared_ptr<Switches> _switches = std::make_shared<Switches>(Switches());
    std::vector<double> _polynom_v;
};

Q_DECLARE_METATYPE(Value);

struct less_than_for_value
{
    inline bool operator() (const Value& v1, const Value& v2)
    {
        //return (l1.get_norma() < l2.get_norma());
        return v1 < v2;
    }
};

#endif // VALUE_H
