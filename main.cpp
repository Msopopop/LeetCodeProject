#ifdef _MSC_VER
#include <iostream>
#else
#include <bits/stdc++.h>
#endif // _MSC_VER

// for memory leak detection on debug mode
#if (defined _MSC_VER) && (defined _DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib> 
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif // defined (_MSC_VER && _DEBUG)

#include <chrono>
#include <cmath>
#include <iomanip>
#include <functional>
#include <random>

namespace with_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n > 0) [[likely]]
            return x * pow(x, n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr long long fact(long long n) noexcept {
        if (n > 1) [[likely]]
            return n * fact(n - 1);
        else [[unlikely]]
            return 1;
    }
    constexpr double cos(double x) noexcept {
        constexpr long long precision{ 16LL };
        double y{};
        for (auto n{ 0LL }; n < precision; n += 2LL) {
            [[likely]] y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
        }
        return y;
    }
}  // namespace with_attributes

namespace no_attributes {
    constexpr double pow(double x, long long n) noexcept {
        if (n > 0)
            return x * pow(x, n - 1);
        else
            return 1;
    }
    constexpr long long fact(long long n) noexcept {
        if (n > 1)
            return n * fact(n - 1);
        else
            return 1;
    }
    constexpr double cos(double x) noexcept {
        constexpr long long precision{ 16LL };
        double y{};
        for (auto n{ 0LL }; n < precision; n += 2LL) {
            y += pow(x, n) / (n & 2LL ? -fact(n) : fact(n));
        }
        return y;
    }
}  // namespace no_attributes

double gen_random()  {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0, 1.0);
    return dis(gen);
}

volatile double sink{}; // ensures a side effect

int main()
{
#if (defined _INC_CRTDBG) && (defined _DEBUG)
	_CrtDumpMemoryLeaks();
#endif 
    const auto benchmark = [](auto fun, auto rem) {
        const auto start = std::chrono::high_resolution_clock::now();
        for (auto size{ 1ULL }; size != 1000'000'000ULL; ++size) {
            sink = fun(gen_random());
        }
        const std::chrono::duration<double> diff =
            std::chrono::high_resolution_clock::now() - start;
        std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
            << " sec " << rem << std::endl;
    };

    benchmark(with_attributes::cos, "(with attributes)");
    benchmark(no_attributes::cos, "(without attributes)");
    const auto start = std::chrono::high_resolution_clock::now();
    for (auto size{ 1ULL }; size != 100'000'000ULL; ++size) {
        sink = cos(gen_random());
    }
    const std::chrono::duration<double> diff =
        std::chrono::high_resolution_clock::now() - start;
    std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
        << " sec " << "std::cos" << std::endl;
    return 0;
}
