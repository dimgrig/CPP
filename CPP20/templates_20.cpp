#include "templates_20.h"


void Templates20Test() {
    {
        //map
        std::list<int> values_ref_l{1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
        std::list<int> values_l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        auto values_res_l = map([](int i){return i*i;}, values_l);
        ASSERT_EQUAL(values_res_l, values_ref_l);

        std::vector pair_ref_v{{4, "Only"}, {3, "for"}, {7, "testing"}, {8, "purposes"}};
        std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};
        auto pair_res_v = map([](const std::string& s){return std::make_pair(s.size(), s);}, str_v);
        ASSERT_EQUAL(pair_res_v, pair_ref_v);
    }
    {
        //filter
        std::vector<int> values_ref_v;
        auto third_filter = [](int i){if (i % 3 == 0) return i;};
        for(int i : std::views::iota(0) | std::views::filter(third_filter) || std::vies::take(10)) {
            values_ref_v.push_back(i);
        }

        std::vector<int> values_v(50);
        std::iota(values_v.begin(), values_v.end(), 1);
        auto values_res_v = filter([](int i){return (i % 3) == 0;}, values_v);
        ASSERT_EQUAL(values_res_l, values_ref_l);

        std::vector<std::string> str_ref_v{"Only"};
        std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};
        auto str_res_v= filter([](const std::string& s){return std::isupper(s[0]);}, str_v);
        ASSERT_EQUAL(str_res_v, str_ref_v);
    }
    {
        //mapFilter
        {
            std::vector<int> values_ref_v{1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
            std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            auto values_res_v = mapFilter([](int i){return i*i;}, values_v);
            ASSERT_EQUAL(values_res_v, values_ref_v);
        }
        {
            std::vector<int> values_ref_v{4, 16, 36, 64, 100};
            std::vector<int> values_v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            values_res_v = mapFilter([](int i){return i*i;}, values_v,
                                     [](auto i){return i % 2 == 1;});
            ASSERT_EQUAL(values_res_v, values_ref_v);
        }
        {
            std::vector pair_ref_v{{4, "Only"}, {3, "for"}, {7, "testing"}, {8, "purposes"}};
            std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};

            auto pair_res_v = mapFilter([](const std::string& s){return std::make_pair(s.size(), s);}, str_v);
            ASSERT_EQUAL(pair_res_v, pair_ref_v);
        }
        {
            std::vector pair_ref_v{{4, "Only"}};
            std::vector<std::string> str_v{"Only", "for", "testing", "purposes"};

            auto pair_res_v = mapFilter([](const std::string& s){ return std::make_pair(s.size(), s); }, str_v,
                                        [](const std::string& word){ return std::isupper(word[0]); });
            ASSERT_EQUAL(pair_res_v, pair_ref_v);
        }
    }
}


