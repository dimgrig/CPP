#include "functions.h"

#include "enums.h"

//bool string_replace(std::string& str, const std::string& from, const std::string& to) {
//    size_t start_pos = str.find(from);
//    if(start_pos == std::string::npos)
//        return false;
//    str.replace(start_pos, from.length(), to);
//    return true;
//}

std::string to_string_exact(double x, bool fixed, int precision) {
    std::ostringstream os;
    if (fixed) {
        os << std::fixed;
    }
    os << std::setprecision(precision);
    os << x; //std::setprecision(std::numeric_limits<double>::max_digits10)
    return os.str();
}

bool string_replace(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return false;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return true;
}

int round_up_to_value(int value, int value_to_round) {
    return ((value + value_to_round - 1) / value_to_round) * value_to_round;
}

int round_down_to_value(int value, int value_to_round) {
    if (value_to_round != 0) {
        return (value / value_to_round) * value_to_round;
    } else {
        return 0;
    }
}

std::string TRANSLATION_EN_RU(std::string EN) {
    std::string res;
    auto result = std::find_if(
              translations_RU_EN.begin(),
              translations_RU_EN.end(),
              [EN](const auto& mo) {return mo.second == EN; });

    if(result != translations_RU_EN.end())
        res = result->first;

    return res;
}

bool startsWith(std::string mainStr, std::string toMatch)
{
    // std::string::find returns 0 if toMatch is found at starting
    if(mainStr.find(toMatch) == 0)
        return true;
    else
        return false;
}

void buf_to_chunks(std::vector<char> rx_ba) {
    int PACKET_MAX_LENGTH = 5;
    char buffer_rx[3][5] = {{0}};
    for (size_t j = 0; j < (rx_ba.size()/PACKET_MAX_LENGTH) + 1; ++j) {
        //if (rx_ba.size() < PACKET_MAX_LENGTH) {
        size_t chunk_size = 0;
        if (j == rx_ba.size()/PACKET_MAX_LENGTH) {
            chunk_size = rx_ba.size() % PACKET_MAX_LENGTH;
        } else {
            chunk_size = PACKET_MAX_LENGTH;
        }
        for (size_t i = 0; i < chunk_size; ++i) {
            buffer_rx[j][i] = rx_ba.at(i + j*PACKET_MAX_LENGTH);
        }
    }
    Q_UNUSED(buffer_rx);
//    for (int j = 0; j < 3; ++j) {
//        for (int i = 0; i < 5; ++i) {
//            LOG((int)buffer_rx[j][i]);
//        }
//        LOG("---");
//    }
}

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

double extract_double(QString str) {
    str = str.split("errlmt").front();
    QRegularExpression rx("[+-]?([0-9]+([(,|.)][0-9]*)?|[(,|.)][0-9]+)");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        //qCDebug(logDebug()) << res;
    }
    char separator_comma = ',';
    char separator_point = '.';
    return res.replace(separator_comma, separator_point).toDouble();
}

double extract_double_scientific(QString str) {
    str = str.split("errlmt").front();
    QRegularExpression rx("[+-]?([0-9]+([(,|.)][0-9]*)?|[(,|.)][0-9]+)((e|E)?([+-]?)[0-9]+)");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        //qCDebug(logDebug()) << res;
    }
    char separator_comma = ',';
    char separator_point = '.';
    return res.replace(separator_comma, separator_point).toDouble();
}



unsigned int extract_id(const QString str) {
    QRegularExpression rx("[0-9]+");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        //qCDebug(logDebug()) << res;
    }
    return res.toInt();
}

unsigned int extract_outcome_id(const QString str) {
    QRegularExpression rx("[o][0-9]+");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        res.remove(0, 1);
        //qCDebug(logDebug()) << res;
    }
    return res.toInt();
}

////|-Uзи ут||Uзи ут|Uзи изм|Uзи|-Iз изм|Iз изм|Uпр|Iпр|Uобр|Iобр|Iс изм|Iс max огр|Iс инд огр|Iс max|Iс инд|Iс|Rси|S|Uси изм|Uси|Uис
//|Uзи ут|Uзи изм|Uзи|Iз изм|Uпр|Iпр|Uобр|Iобр|Iс изм|Iс max|Iс инд|Iс|Rси|S|Uси изм|Uси|Uис
QString extract_name(const QString str) {
//    QStringList sn_sl_re;
//    for (auto s : SignalName_sl_re()) {
//        s.replace("|", "[|]");
//        sn_sl_re.push_back(s);
//    }
//    //qCDebug(logDebug) << sn_sl_re;
    QString signal_names = SignalName_sl_re.join("|");
    QRegularExpression rx("(" + signal_names + ")");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        //qCDebug(logDebug()) << res;
    }
    return res;
}

QString extract_signal_type(const QString str) {
    QRegularExpression rx("(U|I|R|S)");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match_su = i.next();
        res = match_su.captured(0);
        //qCDebug(logDebug()) << res;
    }
    return res;
}

QString extract_testType(const QString str) {
    QString test_types = TestTypes_re.join("|");
    QRegularExpression rx("(" + test_types + ")"); //Контактирование|Обратный ток|Прямое напряжение //Импульсный ток стока Iс(и) max
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        //qCDebug(logDebug()) << res;
    }
    return res;
}

QString extract_standardUnit(const QString str) {
    QRegularExpression rx("([0-9][ ])(нс|мкс|мс|с|"
                                        "нА|мкА|мА|А|кА|МА|ГА|"
                                        "нВ|мкВ|мВ|В|кВ|МА|ГА|"
                                        "нОм|мкОм|мОм|Ом|кОм|МОм|ГОм|"
                                        "нСм|мкСм|мСм|См|кСм|МСм|ГСм|"
                                        "ns|us|ms|s|"                                        
                                        "nA|uA|mA|A|kA|MA|GA|"
                                        "nV|uV|mV|V|kV|MV|GV|"
                                        "nOhm|uOhm|mOhm|Ohm|kOhm|MOhm|GOhm|"
                                        "nS|uS|mS|kS|MS|GS|S)");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QRegularExpression rx_su("(нс|мкс|мс|с|"
                                    "нА|мкА|мА|А|кА|МА|ГА|"
                                    "нВ|мкВ|мВ|В|кВ|МА|ГА|"
                                    "нОм|мкОм|мОм|Ом|кОм|МОм|ГОм|"
                                    "нСм|мкСм|мСм|См|кСм|МСм|ГСм|"
                                    "ns|us|ms|s|"
                                    "nA|uA|mA|A|kA|MA|GA|"
                                    "nV|uV|mV|V|kV|MV|GV|"
                                    "nOhm|uOhm|mOhm|Ohm|kOhm|MOhm|GOhm|"
                                    "nS|uS|mS|kS|MS|GS|S)");
        QRegularExpressionMatchIterator j = rx_su.globalMatch(match.captured(0));
        if (j.hasNext()) {
            QRegularExpressionMatch match_su = j.next();
            res = match_su.captured(0);
            //qCDebug(logDebug()) << res;
        }
    }
    return res;
}


QString extract_dimension(const QString str) {
    QRegularExpression rx("(с|А|В|Ом|См|c|A|V|Ohm|S)");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match_su = i.next();
        res = match_su.captured(0);
        //qCDebug(logDebug()) << res;
    }
    return res;
}

unsigned int extract_connectorPin(const QString str) {
    QRegularExpression rx("(A1|A2|G|D|S)"); //|C
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        res.remove(0, 1);
        //qCDebug(logDebug()) << res;
    }
    return res.toInt();
}

double extract_tolerance(const QString str) {
    QRegularExpression rx("[+-][ ]([0-9]+([(,|.)][0-9]*)?|[(,|.)][0-9]+)[%]");
    QString res = "";
    QRegularExpressionMatchIterator i = rx.globalMatch(str);
    if (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        res = match.captured(0);
        if (res.size() > 3)
            res.remove(0, 2);
        if (res.size() > 0)
            res.remove(res.size() - 1, 1);
    }
    char separator_comma = ',';
    char separator_point = '.';
    return res.replace(separator_comma, separator_point).toDouble();
}

std::string su_from_name(const std::string name) {
    std::string su;
//    if ((name == "Iпр") || (name == "Iобр")) {
//        su = "А";
//    } else if ((name == "Uпр") || (name == "Uобр")) {
//        su = "В";
//    }
    if (name.find("I") != std::string::npos) {
        su = "А";
    } else if (name.find("U") != std::string::npos) {
        su = "В";
    } else if (name.find("R") != std::string::npos) {
        su = "Ом";
    } else if (name.find("S") != std::string::npos) {
        su = "См";
    }
    return su;
}

double extract_scale_factor(const std::string su) {
    double scale_factor = 1.0;
    for (const auto &dimension : dimension_v) {
        if (startsWith(su, dimension)) {
            if (dimension_m.count(dimension) > 0) {
                scale_factor = dimension_m.at(dimension).first / dimension_m.at(dimension).second;
            }
            break;
        }
    }
    return scale_factor;
}


void FunctionsTest() {
    {
        {
            int res_ref = 0;
            int res = round_up_to_value(0, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 1024;
            int res = round_up_to_value(750, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 1024;
            int res = round_up_to_value(1, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 1024;
            int res = round_up_to_value(1024, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 2048;
            int res = round_up_to_value(1025, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 2048;
            int res = round_up_to_value(2000, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 4096;
            int res = round_up_to_value(4000, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            int res_ref = 10240;
            int res = round_up_to_value(10200, 1024);
            ASSERT_EQUAL(res, res_ref);
        }
    }
    {
        {
            std::string res_ref = "A";
            std::string str = "А";
            std::string res = TRANSLATION_RU_EN(str);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            std::string res_ref = "us";
            std::string str = "мкс";
            std::string res = TRANSLATION_RU_EN(str);
        }
        {
            std::string res_ref = "мА";
            std::string str = "mA";
            std::string res = TRANSLATION_EN_RU(str);
            ASSERT_EQUAL(res, res_ref);
        }
        {
            std::string res_ref = "мСм";
            std::string str = "mS";
            std::string res = TRANSLATION_EN_RU(str);
        }
        {
            std::string res_ref = "S";
            std::string str = "См";
            std::string res = TRANSLATION_RU_EN(str);
        }
    }
    {
        {
            double d_ref = 123.456;
            QString str = "ABC 123,456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = -123.456;
            QString str = "ABC -123,456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = 0.456;
            QString str = "ABC 0,456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = -0.456;
            QString str = "ABC -0,456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = 456;
            QString str = "ABC 456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = -123;
            QString str = "ABC -123 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = 0;
            QString str = "ABC 0 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
        {
            double d_ref = 123.456;
            QString str = "ABC = 123,456 DEG";
            double d = extract_double(str);
            ASSERT_EQUAL(d, d_ref);
        }
    }
    {
        {
            int id_ref = 1;
            QString str = "test1";
            int id = extract_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 1;
            QString str = "test 1";
            int id = extract_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 123;
            QString str = "test123";
            int id = extract_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 123;
            QString str = "test123asf";
            int id = extract_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
    }
    {
        {
            int id_ref = 1;
            QString str = "o1";
            int id = extract_outcome_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 10;
            QString str = "o10";
            int id = extract_outcome_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 123;
            QString str = "test123o123";
            int id = extract_outcome_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
        {
            int id_ref = 123;
            QString str = "test123asfo123asfas";
            int id = extract_outcome_id(str);
            ASSERT_EQUAL(id, id_ref);
        }
    }
    {
        {
            QString name_ref = "Uпр";
            QString str = "Uпр1";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iпр";
            QString str = "Iпрasf";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Uобр";
            QString str = "Uобр2";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iобр";
            QString str = "Iобр2";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }


        {
            QString name_ref = "Iс";
            QString str = "Iс = 10 А";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iс изм";
            QString str = "Iс изм = 10 А";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iс max";
            QString str = "Iс max = 10 А";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iс инд";
            QString str = "Iс инд = 10 А";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Rси";
            QString str = "Rси = 1 Ом";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "S";
            QString str = "S = 10 См";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Uси изм";
            QString str = "Uси изм = 10 В";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Uси";
            QString str = "Uси = 10 В";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Uзи изм";
            QString str = "Uзи изм = 10 В";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Uзи";
            QString str = "Uзи = 10 В";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
        {
            QString name_ref = "Iз изм";
            QString str = "Iз изм = 10 А";
            QString name = extract_name(str);
            ASSERT_EQUAL(name, name_ref);
        }
    }
    {
        {
            QString su_ref = "мкс";
            QString str = "5000 мкс";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мкс";
            QString str = "5000 мкс errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мкс";
            QString str = "aasd 5000 мкс 6000 А";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мкс";
            QString str = "aasd 500,0 мкс 6000 А";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мкс";
            QString str = "aasd 500.0 мкс 6000 А";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мкс";
            QString str = "aasd 500.99 мкс 6000 А";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "";
            QString str = "aasd 5000мкс asf";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мА";
            QString str = "500 мА errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мВ";
            QString str = "100 мВ errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "А";
            QString str = "500 А errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "В";
            QString str = "100 В errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }        
        {
            QString su_ref = "мСм";
            QString str = "100 мСм errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "mS";
            QString str = "100 mS errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "мСм";
            QString str = "S = 100 мСм errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
        {
            QString su_ref = "mS";
            QString str = "S = 100 mS errlimit";
            QString su = extract_standardUnit(str);
            ASSERT_EQUAL(su, su_ref);
        }
    }
    {
        {
            double tolerance_ref = 2;
            QString str = "100 В errlimit +- 2%";
            double tolerance = extract_tolerance(str);
            ASSERT_EQUAL(tolerance, tolerance_ref);
        }
        {
            double tolerance_ref = 2;
            QString str = "100 В errlimit +- 2.0%";
            double tolerance = extract_tolerance(str);
            ASSERT_EQUAL(tolerance, tolerance_ref);
        }
    }
    {
        {
            QString test_name = "Импульсный ток стока Iс(и) max1";
            TestType test_type_ref = Test_I_DM;
            TestType test_type = TestType_from_text(extract_testType(test_name).toStdString().c_str());
            ASSERT_EQUAL(test_type, test_type_ref);
        }
    }
    {
        {
            std::string su_ref("А");
            std::string su = su_from_name("Iпр");
            ASSERT_EQUAL(su, su_ref);
        }
        {
            std::string su_ref("В");
            std::string su = su_from_name("Uзи");
            ASSERT_EQUAL(su, su_ref);
        }
        {
            std::string su_ref("Ом");
            std::string su = su_from_name("Rси");
            ASSERT_EQUAL(su, su_ref);
        }
        {
            std::string su_ref("См");
            std::string su = su_from_name("S");
            ASSERT_EQUAL(su, su_ref);
        }
    }
//    {
//        LOG("1_____");
//        std::vector<char> rx_ba = {};
//        buf_to_chunks(rx_ba);
//    }
//    {
//        LOG("2_____");
//        std::vector<char> rx_ba = {1,2,3};
//        buf_to_chunks(rx_ba);
//    }
//    {
//        LOG("3_____");
//        std::vector<char> rx_ba = {1,2,3,4,5};
//        buf_to_chunks(rx_ba);
//    }
//    {
//        LOG("4_____");
//        std::vector<char> rx_ba = {1,2,3,4,5,6,7};
//        buf_to_chunks(rx_ba);
//    }
//    {
//        LOG("5_____");
//        std::vector<char> rx_ba = {1,2,3,4,5,6,7,8,9,10};
//        buf_to_chunks(rx_ba);
//    }
//    {
//        LOG("6_____");
//        std::vector<char> rx_ba = {1,2,3,4,5,6,7,8,9,10,11,12};
//        buf_to_chunks(rx_ba);
//    }
}
