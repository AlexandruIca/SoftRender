#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP
#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

using void_func_t = void (*)();

int g_main_exit_value = EXIT_SUCCESS;

auto get_tests() noexcept -> std::vector<void_func_t>&
{
    static std::vector<void_func_t> tests;
    return tests;
}

#define CAT2(a, b) a##b
#define CAT1(a, b) CAT2(a, b)
#define CAT(a, b) CAT1(a, b)
#define R(name) CAT(name, __LINE__)

#define TEST(name)                                                             \
    auto R(new_test)()->void;                                                  \
    auto R(wrapper)()->int                                                     \
    {                                                                          \
        get_tests().push_back(R(new_test));                                    \
        return 0;                                                              \
    }                                                                          \
    [[maybe_unused]] int const R(tmp_val) = R(wrapper)();                      \
    auto R(new_test)()->void

#define ASSERT(...)                                                            \
    if(!(__VA_ARGS__)) {                                                       \
        std::cout << "Error at line: " << __LINE__ << ", file: " << __FILE__;  \
        std::cout << "\n\t" << #__VA_ARGS__ << std::endl;                      \
        g_main_exit_value = EXIT_FAILURE;                                      \
        return;                                                                \
    }                                                                          \
    (void)0

#ifdef SOFTRENDER_DEBUG
#define ASSERT_THROWS(...)                                                     \
    bool R(has_thrown){ false };                                               \
    try {                                                                      \
        __VA_ARGS__;                                                           \
    }                                                                          \
    catch(...) {                                                               \
        R(has_thrown) = true;                                                  \
    }                                                                          \
    if(!R(has_thrown)) {                                                       \
        std::cout << "Error at line: " << __LINE__ << ", file: " << __FILE__;  \
        std::cout << "\n\tException should have been thrown!" << std::endl;    \
        std::cout << "\tExpansion: " << #__VA_ARGS__ << std::endl;             \
        g_main_exit_value = EXIT_FAILURE;                                      \
        return;                                                                \
    }                                                                          \
    (void)0
#else
#define ASSERT_THROWS(...) (void)0
#endif

#define CHECK(...)                                                             \
    if(!(__VA_ARGS__)) {                                                       \
        std::cout << "Warning at line: " << __LINE__                           \
                  << ", file: " << __FILE__;                                   \
        std::cout << "\n\t" << #__VA_ARGS__ << std::endl;                      \
        g_main_exit_value = EXIT_FAILURE;                                      \
    }                                                                          \
    (void)0

auto main(int const, char const* const[]) noexcept -> int
{
    for(auto& test : get_tests()) {
        test();
    }

    if(g_main_exit_value == EXIT_SUCCESS) {
        std::cout << "All tests passed!" << std::endl;
    }

    return g_main_exit_value;
}

#endif // !TEST_HELPER_HPP
