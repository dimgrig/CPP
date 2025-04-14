#include "Adapter.h"

#include "TestRunner.h"

auto sort_much_less_lambda_it = [](auto first, auto last) {
    return std::sort(first, last, much_less());
};

auto sort_much_less_lambda_container = [](auto& container) { return std::sort(container.begin(), container.end(), much_less()); };

void AdapterTest() {
    const size_t N = 20;
    std::vector<int> v_ref{10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    {
        std::vector<int> v(N);
        for (size_t i = 0; i < N; ++i) {
            v[i] = (N - i);
        }
        sort_much_less(v.begin(), v.end());
        std::cout << v;
        std::cout << std::endl;
        ASSERT_EQUAL(v, v_ref);
    }
    {
        std::vector<int> v(N);
        for (size_t i = 0; i < N; ++i) {
            v[i] = (N - i);
        }
        sort_much_less(v);
        ASSERT_EQUAL(v, v_ref);
    }
    {
        std::vector<int> v(N);
        for (size_t i = 0; i < N; ++i) {
            v[i] = (N - i);
        }
        sort_much_less_lambda_it(v.begin(), v.end());
        ASSERT_EQUAL(v, v_ref);
    }
    {
        std::vector<int> v(N);
        for (size_t i = 0; i < N; ++i) {
            v[i] = (N - i);
        }
        sort_much_less_lambda_container(v);
        ASSERT_EQUAL(v, v_ref);
    }
    {
        //ambigous with template cout
//        const size_t N = 10;
//        Buffer<int> b(N);
//        //std::vector<int> v(N);      // Does not compile - 2 argument template
//        vector1<int> v1(N);
//        //std::array<int, N> a;       // Does not compile - 2 argument template
//        array1<int> a1;
//        for (size_t i = 0; i < N; ++i) {
//            a1[i] = v1[i] = b[i] = (N - i);
//        }
//        std::cout << b << std::endl;
//        std::cout << v1 << std::endl;
//        std::cout << a1 << std::endl;
    }
    {
        {
            using V = ValueAdapter<int>;
            V i, j(5), k(3);
            //i == j; // Not Comparable
        }
        {
            using V = Comparable<ValueAdapter<int>>;
            V i, j(5), k(3);
            ASSERT(!(i == j));
            ASSERT(i != j);
            ASSERT(k == 3);
            ASSERT(!(k != 3));
            //i < j; // Not Ordered
        }
        {
            using V = Ordered<Comparable<ValueAdapter<int>>>;
            V i, j(5), k(3);
            ASSERT(!(i == j));
            ASSERT(i != j);
            ASSERT(k == 3);
            ASSERT(!(k != 3));
            ASSERT(i < j);
            ASSERT(i <= j);
            ASSERT(k >= 3);
            ASSERT(6 > k);
        }
        {
            using V = Comparable<Ordered<ValueAdapter<int>>>;
            V i, j(5), k(3);
            ASSERT(!(i == j));
            ASSERT(i != j);
            ASSERT(k == 3);
            ASSERT(!(k != 3));
            ASSERT(i < j);
            ASSERT(i <= j);
            ASSERT(k >= 3);
            ASSERT(6 > k);
            //i + j; // Not Addable
        }
        {
            using V = Addable<Comparable<Ordered<ValueAdapter<int>>>>;
            V i, j(5), k(3);
            ASSERT((i + 3) == 3);
            ASSERT((i + j) == 5);
            ASSERT((3 + j) == 8);
            ASSERT((7 - k) == 4);
            ASSERT((i + j) > k);
            ASSERT((i - j) != k);
        }
        {
            using V = Comparable<Addable<Ordered<ValueAdapter<int>>>>;
            V i, j(5), k(3);
//            ASSERT((i + 3) == 3); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((i + j) == 5); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((3 + j) == 8); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((7 - k) == 4); // Order problem, i +- j is Addable not Comparable!
            ASSERT((i + j) > k);
            ASSERT((i - j) != k);
        }
        {
            using V = Comparable<Ordered<Addable<ValueAdapter<int>>>>;
            V i, j(5), k(3);
//            ASSERT((i + 3) == 3); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((i + j) == 5); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((3 + j) == 8); // Order problem, i +- j is Addable not Comparable!
//            ASSERT((7 - k) == 4); // Order problem, i +- j is Addable not Comparable!
            ASSERT((i + j) > k);
            ASSERT((i - j) != k);
            //i*j; // Not Multipliable
        }
        {
            using V = Multipliable<Addable<Comparable<Ordered<ValueAdapter<int>>>>>;
            V i, j(5), k(3);
            ASSERT((2 * j) == 10);
            ASSERT((k / 3) == 1);
            ASSERT((i * j) < k);
            ASSERT((i / j) != k);
            ASSERT(((i * j) + (k / 3)) == 1);
            //ASSERT(((i + j) * (k + 3)) == 30); // Order problem, i + j is Addable not Multipliable!
        }
        {
            using V = Addable<Multipliable<Comparable<Ordered<ValueAdapter<int>>>>>;
            V i, j(5), k(3);
            ASSERT((2 * j) == 10);
            ASSERT((k / 3) == 1);
            ASSERT((i * j) < k);
            ASSERT((i / j) != k);
            //ASSERT(((i * j) + (k / 3)) == 1); // Order problem, i + j is Multipliable not Addable!
            ASSERT(((i + j) * (k + 3)) == 30);
        }
    }
}
