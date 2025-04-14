#include "templates_20.h"


void Templates20Test() {
    {
        //filter
        std::vector<int> values_ref_v;
        auto third_filter = [](int i){return (i % 3) == 0;};
        for(int i : std::views::iota(0) | std::views::take(30) | std::views::filter(third_filter) ) {
            values_ref_v.push_back(i);
        }

        std::vector<int> values_v(30);
        std::iota(values_v.begin(), values_v.end(), 0);
        auto values_res_v = filter([](int i){return (i % 3) == 0;}, values_v);
//        qCDebug(logDebug) << values_res_v;
//        qCDebug(logDebug) << values_ref_v;
        ASSERT_EQUAL(values_res_v, values_ref_v);

        std::vector<std::string> str_ref_v{"Only"};
        std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};
        auto str_res_v = filter([](const std::string& s){return std::isupper(s[0]);}, str_v);
//        qCDebug(logDebug) << str_res_v;
//        qCDebug(logDebug) << str_ref_v;
        ASSERT_EQUAL(str_res_v, str_ref_v);
    }
    {
        //map
        std::vector<int> values_ref_v{1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
        std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto values_res_v = map([](int i){return i*i;}, values_v);
//        qCDebug(logDebug) << values_res_v;
//        qCDebug(logDebug) << values_ref_v;
        ASSERT_EQUAL(values_res_v, values_ref_v);

        std::vector<std::pair<unsigned long int, std::string>> pair_ref_v{{4, "Only"}, {3, "for"}, {7, "testing"}, {8, "purposes"}};
        std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};
        auto pair_res_v = map([](const std::string& s){return std::make_pair(s.size(), s);}, str_v);
//        qCDebug(logDebug) << pair_res_v;
//        qCDebug(logDebug) << pair_ref_v;
        ASSERT_EQUAL(pair_res_v, pair_ref_v);
    }
    {
        //map_filter
        {
            std::vector<int> values_ref_v{1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
            std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            auto values_res_v = map_filter([](int i){return i*i;}, values_v);
//            qCDebug(logDebug) << values_res_v;
//            qCDebug(logDebug) << values_ref_v;
            ASSERT_EQUAL(values_res_v, values_ref_v);
        }
        {
            std::vector<int> values_ref_v{4, 16, 36, 64, 100};
            std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            auto values_res_v = map_filter([](int i){return i*i;}, values_v,
                                     [](auto i){return (i % 2) == 0;});
//            qCDebug(logDebug) << values_res_v;
//            qCDebug(logDebug) << values_ref_v;
            ASSERT_EQUAL(values_res_v, values_ref_v);
        }
        {
            std::vector<std::pair<unsigned long int, std::string>> pair_ref_v{{4, "Only"}, {3, "for"}, {7, "testing"}, {8, "purposes"}};
            std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};

            auto pair_res_v = map_filter([](const std::string& s){return std::make_pair(s.size(), s);}, str_v);
//            qCDebug(logDebug) << pair_res_v;
//            qCDebug(logDebug) << pair_ref_v;
            ASSERT_EQUAL(pair_res_v, pair_ref_v);
        }
        {
            std::vector<std::pair<unsigned long int, std::string>> pair_ref_v{{4, "Only"}};
            std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};

            auto pair_res_v = map_filter([](const std::string& s){ return std::make_pair(s.size(), s); }, str_v,
                                        [](const std::string& word){ return std::isupper(word[0]); });
//            qCDebug(logDebug) << pair_res_v;
//            qCDebug(logDebug) << pair_ref_v;
            ASSERT_EQUAL(pair_res_v, pair_ref_v);
        }
    }
    {
        //ContainerView
        {
            std::vector<int> values_ref_v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
            std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            ContainerView container_view = ContainerView(values_v);
            ContainerView values_res_v = std::views::reverse(container_view);
//            qCDebug(logDebug) << values_res_v;
//            qCDebug(logDebug) << values_ref_v;
            ASSERT_EQUAL(values_res_v.to_vector(), values_ref_v);
        }
        {
            std::string str = "Only for testing purpose";
            std::string str_ref = str;
            std::reverse(str_ref.begin(), str_ref.end());
            ContainerView container_view = ContainerView(str);
            ContainerView str_res = std::views::reverse(container_view);
//            qCDebug(logDebug) << str_res;
//            qCDebug(logDebug) << str_ref;
            ASSERT_EQUAL(str_res.to_string(), str_ref);
        }
    }
    {
        //c++ 17 returne type resolver
        int n_int = from_string("123");
        float n_float = from_string("123,111"); //or 123.111 - locale
        ASSERT_EQUAL(n_int, 123);
        //ASSERT_EQUAL(n_float, 123.111);
        ASSERT(std::abs(n_float - 123.111) < std::numeric_limits<float>::epsilon());
    }
}


