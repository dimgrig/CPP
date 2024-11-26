#include "Value.h"

#include "functions.h"

//extern std::map<SignalName, Switches> switches_m;

Value::Value() {

}

Value::Value(std::string name, double value, std::string standardUnit, double tolerance) :
    _name(name),
    _value(value),
    _standardUnit(standardUnit),
    _tolerance(tolerance)
{
    _signal = SignalName_from_text(_name.c_str());
    //must be for default switches!!!
//    if (switches_m.count(_signal) > 0) {
//        _switches = std::make_shared<Switches>(switches_m.at(_signal));
//    }
}

Value::~Value() {

}

void Value::set_value_absolute(double value) {
    this->_value = value;
    this->_standardUnit = this->get_su_absolute();
}

double Value::get_value_fit_dimension() const {
    Value value_fit = *this;
    value_fit.fit_dimension();
    return value_fit.get_value();
}

std::string Value::get_su_fit_dimension() const {
    Value value_fit = *this;
    value_fit.fit_dimension();
    return value_fit.get_su();
}


double Value::get_value_absolute() const {
    return scale_value();
}

std::string Value::get_su_absolute() const {
    return extract_dimension(this->get_su().c_str()).toStdString();
}

double Value::get_value_fit_su(std::string su_str) const {
    Value value_fit_su = *this;
    QString su = su_str.c_str();
    QString dimension = extract_dimension(su);
    QString scale_factor_str = su.remove(QRegularExpression(dimension));
    //double scale_factor = 1.0;
    double res = value_fit_su.get_value_absolute();
    if (dimension_m.count(scale_factor_str.toStdString()) > 0) {
        //scale_factor = dimension_m.at(scale_factor_str.toStdString());
        //scale_factor = dimension_m.at(scale_factor_str.toStdString()).first / dimension_m.at(scale_factor_str.toStdString()).second;
        res = res / dimension_m.at(scale_factor_str.toStdString()).first * dimension_m.at(scale_factor_str.toStdString()).second;
    }
    //return value_fit_su.get_value_absolute() / scale_factor;
    return res;
}

double Value::scale_value() const {
    //double scale_factor = 1.0;

    double res = _value;
//    int index = 0;
//    std::string dimension_su;

    if (!_standardUnit.empty()) {
        for (const auto &dimension : dimension_v) {
            if (startsWith(_standardUnit, dimension)) {
                if (dimension_m.count(dimension) > 0) {
                    //scale_factor = dimension_m.at(dimension).first / dimension_m.at(dimension).second;
                    //dimension_su = dimension;
                    //index = 1;
                    res = res * dimension_m.at(dimension).first / dimension_m.at(dimension).second;
                }
                break;
            }
        }
    }

    //return _value * scale_factor;
    return res;
}

void Value::scale_value_clear_dimension() {
    //double scale_factor = 1.0;

    if (!_standardUnit.empty()) {
        for (const auto &dimension : dimension_v) {
            if (startsWith(_standardUnit, dimension)) {
                if (dimension_m.count(dimension) > 0) {
                    //scale_factor = dimension_m.at(dimension);
                    _value = _value * dimension_m.at(dimension).first / dimension_m.at(dimension).second; // * scale_factor
                    size_t dimension_size = dimension.size();
                    _standardUnit = _standardUnit.erase(0, dimension_size);
                }
                break;
            }
        }
    }
}

void Value::fit_dimension() {
    scale_value_clear_dimension();

    //double scale_factor = 1.0;

    if (std::abs(_value) < 1.0) {
        for (const auto &dimension : dimension_down) {
            //scale_factor = dimension_m.at(dimension);
            //scale_factor = dimension_m.at(dimension).first / dimension_m.at(dimension).second;
            if (std::abs(_value / dimension_m.at(dimension).first * dimension_m.at(dimension).second) >= 1) { // /scale_factor
                _value = _value / dimension_m.at(dimension).first * dimension_m.at(dimension).second; // /scale_factor
                _standardUnit = dimension + _standardUnit;
                break;
            }
        }
        if (std::abs(_value) < 1.0) { //fix lowest dimension
            for (const auto &dimension : dimension_down) {
                //scale_factor = dimension_m.at(dimension);
                //scale_factor = dimension_m.at(dimension).first / dimension_m.at(dimension).second;
                if (std::abs(_value / dimension_m.at(dimension).first * dimension_m.at(dimension).second) >= 0.001) {
                    _value = _value * dimension_m.at(dimension).first / dimension_m.at(dimension).second; // /scale_factor
                    _standardUnit = dimension + _standardUnit;
                    break;
                }
            }

        }
    } else if (std::abs(_value) >= 1000.0) {
        for (const auto &dimension : dimension_up) {
            //scale_factor = dimension_m.at(dimension);
            //scale_factor = dimension_m.at(dimension).first / dimension_m.at(dimension).second;
            if (std::abs(_value / dimension_m.at(dimension).first * dimension_m.at(dimension).second) < 1000) { // /scale_factor
                _value = _value / dimension_m.at(dimension).first * dimension_m.at(dimension).second; // /scale_factor
                _standardUnit = dimension + _standardUnit;
                break;
            }
        }
    } else {
        //no need to fit - 1..1000
    }
}

void Value::from_string(std::string value_str) {
    _name = extract_name(value_str.c_str()).toStdString();
    _value = extract_double(value_str.c_str());
    _standardUnit = extract_standardUnit(value_str.c_str()).toStdString();

    _signal = SignalName_from_text(_name.c_str());
    //must be for default switches!!!
//    if (switches_m.count(_signal) > 0) {
//        _switches = std::make_shared<Switches>(switches_m.at(_signal));
//    }
}

std::string Value::get_string(bool fixed, int precision, std::string more_less_equal_sign, bool name) const {
    std::string res;
    std::string space = " ";
    if (name) {
        if (!_name.empty()) {
            res += _name;
            res += space;
            res += more_less_equal_sign;
            res += space;
        }
    }

    res += to_string_exact(_value, fixed, precision);
    res.erase(res.find_last_not_of('0') + 1, std::string::npos);
    if ((res.back() == '.') || (res.back() == ',')) {
        //res += "000";
        res.erase(res.size() - 1, std::string::npos);
    }
    string_replace(res, ".", ",");

    if (!_standardUnit.empty()) {
        res += space;
        res += _standardUnit;
    }

    return res;
}

std::string Value::get_string_fit_dimension(bool fixed, int precision, std::string more_less_equal_sign, bool name) const {
    Value value_fit = *this;
    value_fit.fit_dimension();
    return value_fit.get_string(fixed, precision, more_less_equal_sign, name);
}

std::string Value::get_string_absolute(bool fixed, int precision, std::string more_less_equal_sign, bool name) const {
    Value value_absolute = *this;
    value_absolute.set_value(value_absolute.get_value_absolute());
    value_absolute.set_su(value_absolute.get_su_absolute());
    return value_absolute.get_string(fixed, precision, more_less_equal_sign, name);
}

std::string Value::get_string_fit_su(std::string su_str, bool fixed, int precision, std::string more_less_equal_sign, bool name) const {
    Value value_fit_su = *this;
    QString su = su_str.c_str();
    QString dimension = extract_dimension(su);
    QString scale_factor_str = su.remove(QRegularExpression(dimension));
    //double scale_factor = 1.0;
    if (dimension_m.count(scale_factor_str.toStdString()) > 0) {
        //scale_factor = dimension_m.at(scale_factor_str.toStdString());
        //scale_factor = dimension_m.at(scale_factor_str.toStdString()).first / dimension_m.at(scale_factor_str.toStdString()).second;
        value_fit_su.set_value(value_fit_su.get_value_absolute() / dimension_m.at(scale_factor_str.toStdString()).first * dimension_m.at(scale_factor_str.toStdString()).second);
    }
    if (scale_factor_str == "") { //fix bug with test result
        value_fit_su.set_value(value_fit_su.get_value_absolute());
    }
    //value_fit_su.set_value(value_fit_su.get_value_absolute() / scale_factor); // /scale_factor
    value_fit_su.set_su(su_str);
    if (std::abs(value_fit_su.get_value()) < 0.001) {
        //zero for fit su
        return value_fit_su.get_string_fit_dimension(fixed, precision, more_less_equal_sign, name);
    } else {
        return value_fit_su.get_string(fixed, precision, more_less_equal_sign, name);
    }
}

Value Value::abs() const {
    Value res = *this;
    res.set_value(std::abs(res.get_value()));
    return res;
}

bool Value::equal_unit(std::string standardUnit) const {
    std::string _unit = this->get_su_absolute();

    return (standardUnit == _unit);
}

QDebug operator<<(QDebug os, const Value& r) {
    os << r._name << " = " << r._value << r._standardUnit << r._tolerance;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Value &r) {
    os << r._name << " = " << r._value << r._standardUnit << r._tolerance;
    return os;
}

bool operator==(const Value &lhs, const Value &rhs) {
    if (std::abs(lhs.get_value_absolute() - rhs.get_value_absolute()) > value_epsilon) {
        return false;
    }
    return ((lhs._name == rhs._name) &&
            //(lhs.get_value_absolute() == rhs.get_value_absolute()) &&
            (lhs.get_su_absolute() == rhs.get_su_absolute()) &&
            (lhs._tolerance == rhs._tolerance) &&
            (lhs._signal == rhs._signal) &&
            (lhs._range == rhs._range) &&
            (lhs._range_calculated == rhs._range_calculated) &&
            (lhs._channel == rhs._channel) &&
            (lhs._calibrator_channel_number == rhs._calibrator_channel_number) &&
            (lhs._switches->get_switches() == rhs._switches->get_switches())
            );
};

void ValueTest() {
//    {
//        Value value = Value("", 100.123125125125125214, "mV", 0);
//        std::string str = value.get_string_fit_dimension();
//        qCDebug(logDebug()) << str;
//    }
    {
        Value value = Value("", 100, "mV", 0);
        double scaled_value = value.get_value_absolute();
        ASSERT_EQUAL(scaled_value, 0.1);
    }

    {
        Value value_mA = Value("", 100, "мА", 0);
        Value value_uA = Value("", 100, "мкА", 0);

        Value value_kA = Value("", 100, "кА", 0);
        Value value_MA = Value("", 100, "МА", 0);

        {
            Value value = Value("", 0.100, "А", 0);
            ASSERT_EQUAL(value, value_mA);
            ASSERT_EQUAL(value.get_su_absolute(), value_mA.get_su_absolute());
        }
        {
            Value value = Value("", 0.0001, "А", 0);
            ASSERT_EQUAL(value, value_uA);
            ASSERT_EQUAL(value.get_su_absolute(), value_uA.get_su_absolute());
        }
        {
            Value value = Value("", 100000, "А", 0);
            ASSERT_EQUAL(value, value_kA);
            ASSERT_EQUAL(value.get_su_absolute(), value_kA.get_su_absolute());
        }
        {
            Value value = Value("", 100000000, "А", 0);
            ASSERT_EQUAL(value, value_MA);
            ASSERT_EQUAL(value.get_su_absolute(), value_MA.get_su_absolute());
        }
    }

//    {
//        Value value_mA = Value("", -100, "мА", 0);
//        Value value_uA = Value("", -100, "мкА", 0);

//        Value value_kA = Value("", -100, "кА", 0);
//        Value value_MA = Value("", -100, "МА", 0);

//        {
//            Value value = Value("", -0.100, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_mA, true);
//            ASSERT_EQUAL(value.get_su(), value_mA.get_su());
//        }
//        {
//            Value value = Value("", -0.000100, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_uA, true);
//            ASSERT_EQUAL(value.get_su(), value_uA.get_su());
//        }
//        {
//            Value value = Value("", -100000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_kA, true);
//            ASSERT_EQUAL(value.get_su(), value_kA.get_su());
//        }
//        {
//            Value value = Value("", -100000000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_MA, true);
//            ASSERT_EQUAL(value.get_su(), value_MA.get_su());
//        }
//    }

//    {
//        Value value_A = Value("", 1, "А", 0);
//        Value value_mA = Value("", 1, "мА", 0);
//        Value value_uA = Value("", 1, "мкА", 0);

//        Value value_kA = Value("", 1, "кА", 0);
//        Value value_MA = Value("", 1, "МА", 0);

//        {
//            Value value = Value("", 1.000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_A, true);
//            ASSERT_EQUAL(value.get_su(), value_A.get_su());
//        }
//        {
//            Value value = Value("", 0.001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_mA, true);
//            ASSERT_EQUAL(value.get_su(), value_mA.get_su());
//        }
//        {
//            Value value = Value("", 0.000001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_uA, true);
//            ASSERT_EQUAL(value.get_su(), value_uA.get_su());
//        }
//        {
//            Value value = Value("", 1000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_kA, true);
//            ASSERT_EQUAL(value.get_su(), value_kA.get_su());
//        }
//        {
//            Value value = Value("", 1000000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_MA, true);
//            ASSERT_EQUAL(value.get_su(), value_MA.get_su());
//        }
//    }

//    {
//        Value value_A = Value("", 1.001, "А", 0);
//        Value value_mA = Value("", 1.001, "мА", 0);
//        Value value_uA = Value("", 1.001, "мкА", 0);

//        Value value_kA = Value("", 1.001, "кА", 0);
//        Value value_MA = Value("", 1.001, "МА", 0);

//        {
//            Value value = Value("", 1.001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_A, true);
//            ASSERT_EQUAL(value.get_su(), value_A.get_su());
//        }
//        {
//            Value value = Value("", 0.001001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_mA, true);
//            ASSERT_EQUAL(value.get_su(), value_mA.get_su());
//        }
//        {
//            Value value = Value("", 0.000001001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_uA, true);
//            ASSERT_EQUAL(value.get_su(), value_uA.get_su());
//        }
//        {
//            Value value = Value("", 1001, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_kA, true);
//            ASSERT_EQUAL(value.get_su(), value_kA.get_su());
//        }
//        {
//            Value value = Value("", 1001000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_MA, true);
//            ASSERT_EQUAL(value.get_su(), value_MA.get_su());
//        }
//    }

//    {
//        Value value_A = Value("", 999.9, "А", 0);
//        Value value_mA = Value("", 999.9, "мА", 0);
//        Value value_uA = Value("", 999.9, "мкА", 0);

//        Value value_kA = Value("", 999.9, "кА", 0);
//        Value value_MA = Value("", 999.9, "МА", 0);

//        {
//            Value value = Value("", 999.9, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_A, true);
//            ASSERT_EQUAL(value.get_su(), value_A.get_su());
//        }
//        {
//            Value value = Value("", 0.9999, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_mA, true);
//            ASSERT_EQUAL(value.get_su(), value_mA.get_su());
//        }
//        {
//            Value value = Value("", 0.0009999, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_uA, true);
//            ASSERT_EQUAL(value.get_su(), value_uA.get_su());
//        }
//        {
//            Value value = Value("", 999900, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_kA, true);
//            ASSERT_EQUAL(value.get_su(), value_kA.get_su());
//        }
//        {
//            Value value = Value("", 999900000, "А", 0);
//            value.fit_dimension();
//            ASSERT_EQUAL(value == value_MA, true);
//            ASSERT_EQUAL(value.get_su(), value_MA.get_su());
//        }
//    }

//    {
//        {
//            QString value_str_ref = "Iпр = 10 А";
//            Value value;
//            value.from_string(value_str_ref.toStdString());
//            QString value_str = value.get_string().c_str();
//            ASSERT_EQUAL(value_str, value_str_ref);
//        }
//        {
//            QString value_str_ref = "Iпр = 0 А";
//            Value value;
//            value.from_string(value_str_ref.toStdString());
//            QString value_str = value.get_string().c_str();
//            ASSERT_EQUAL(value_str, value_str_ref);
//        }
//        {
//            QString value_str_ref = "Uобр = 123,456 В";
//            Value value;
//            value.from_string(value_str_ref.toStdString());
//            QString value_str = value.get_string().c_str();
//            ASSERT_EQUAL(value_str, value_str_ref);
//        }
//        {
//            QString value_str_ref = "Uобр = -123,456 В";
//            Value value;
//            value.from_string(value_str_ref.toStdString());
//            QString value_str = value.get_string().c_str();
//            ASSERT_EQUAL(value_str, value_str_ref);
//        }
//        {
//            QString value_str_ref = "Iобр = 123,456 нА";
//            Value value;
//            value.from_string(value_str_ref.toStdString());
//            QString value_str = value.get_string().c_str();
//            value.scale_value_clear_dimension();
//            qCDebug(logDebug()) << value;
//            ASSERT_EQUAL(value_str, value_str_ref);
//        }
//    }
    {

        {
            QString value_str_ref = "Iобр = 0,951 А";
            QString value_str_fit_dim_ref = "Iобр = 951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("А").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iобр = 0,951 мА";
            QString value_str_fit_dim_ref = "Iобр = 951 мкА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iобр = 0,951 кА";
            QString value_str_fit_dim_ref = "Iобр = 951 А";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("кА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }

        {
            QString value_str_ref = "Iс изм = 0,951 А";
            QString value_str_fit_dim_ref = "Iс изм = 951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("А").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iс max = 0,951 мА";
            QString value_str_fit_dim_ref = "Iс max = 951 мкА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iс инд = 0,951 А";
            QString value_str_fit_dim_ref = "Iс инд = 951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("А").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iс = 0,951 мА";
            QString value_str_fit_dim_ref = "Iс = 951 мкА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iз изм = 123,951 мА";
            QString value_str_fit_dim_ref = "Iз изм = 123,951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Uси изм = 123,951 В";
            QString value_str_fit_dim_ref = "Uси изм = 123,951 В";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("В").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Uси = 123,951 мВ";
            QString value_str_fit_dim_ref = "Uси = 123,951 мВ";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мВ").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Uзи изм = 123,951 В";
            QString value_str_fit_dim_ref = "Uзи изм = 123,951 В";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("В").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Uзи = 123,951 мВ";
            QString value_str_fit_dim_ref = "Uзи = 123,951 мВ";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мВ").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Rси = 123,951 Ом";
            QString value_str_fit_dim_ref = "Rси = 123,951 Ом";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("Ом").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "S = 123,951 См";
            QString value_str_fit_dim_ref = "S = 123,951 См";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("См").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_ref = "Iз изм = 123,951 мА";
            QString value_str_fit_dim_ref = "Iз изм = 123,951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            QString value_str_fit_su = value.get_string_fit_su("мА").c_str();

            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
            ASSERT_EQUAL(value_str_fit_su, value_str_ref);
        }
        {
            QString value_str_fit_su_ref = "Rси = 0,123 Ом";
            Value value = Value("Rси", 123, "мОм", 2);
            QString value_str_fit_su = value.get_string_fit_su("Ом").c_str();

            ASSERT_EQUAL(value_str_fit_su, value_str_fit_su_ref);
        }
    }
    {

        {
            QString value_str_ref = "Iс = -0,951 А";
            QString value_str_fit_dim_ref = "Iс = 951 мА";
            Value value;
            value.from_string(value_str_ref.toStdString());
            value = value.abs();
            QString value_str_fit_dim = value.get_string_fit_dimension().c_str();
            ASSERT_EQUAL(value_str_fit_dim, value_str_fit_dim_ref);
        }
    }
}
