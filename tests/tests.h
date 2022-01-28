#pragma once

#include "wordle_solver.h"

#include <vector>
#include <string>

namespace assertx
{
    bool is_true(bool expr, const std::string& msg = "test failed")
    {
        if (!expr)
        {
            std::cout << msg << std::endl;
            return false;
        }

        return true;
    }

    bool are_equal(const std::string& a, const std::string& b, const std::string& msg = "test failed")
    {
        return assertx::is_true(a == b);
    }
}

namespace tests
{
    namespace
    {
        static std::vector<std::string> sample_words
        {
            "knife", "later", "arose"
        };
    }

    void test_filterByPattern_emptyPattern()
    {
        auto filtered_values = wordle_solver_ns::filter_by_pattern(sample_words, "#####");

        assertx::is_true(filtered_values.size() == 3, "test_filterByPattern_emptyPattern failed");
    }

    void test_filterByPattern_partialPattern()
    {
        auto filtered_values = wordle_solver_ns::filter_by_pattern(sample_words, "kn###");

        assertx::is_true(filtered_values.size() == 1, "test_filterByPattern_partialPattern is_true failed");
        assertx::are_equal("knife", filtered_values.at(0), "test_filterByPattern_partialPattern are_equal failed");
    }

    void test_filterByPattern_fullPattern()
    {
        auto filtered_values = wordle_solver_ns::filter_by_pattern(sample_words, "knife");

        assertx::is_true(filtered_values.size() == 1, "test_filterByPattern_fullPattern is_true failed");
        assertx::are_equal("knife", filtered_values.at(0), "test_filterByPattern_fullPattern are_equal failed");
    }


    void test_filterByConfirmed_emptyConfirms()
    {
        auto filtered_values = wordle_solver_ns::filter_by_confirmed(sample_words, "");

        assertx::is_true(filtered_values.size() == 3, "test_filterByConfirmed_emptyConfirms is_true failed");
    }

    void test_filterByConfirmed_singleConfirms()
    {
        auto filtered_values = wordle_solver_ns::filter_by_confirmed(sample_words, "k");

        assertx::is_true(filtered_values.size() == 1, "test_filterByConfirmed_singleConfirms is_true failed");
        assertx::are_equal("knife", filtered_values.at(0), "test_filterByConfirmed_singleConfirms are_equal failed");
    }

    void test_filterByConfirmed_joinedConfirms()
    {
        auto filtered_values = wordle_solver_ns::filter_by_confirmed(sample_words, "kn");

        assertx::is_true(filtered_values.size() == 1, "test_filterByConfirmed_joinedConfirms is_true failed");
        assertx::are_equal("knife", filtered_values.at(0), "test_filterByConfirmed_joinedConfirms are_equal failed");
    }

    void test_filterByConfirmed_splitConfirms()
    {
        auto filtered_values = wordle_solver_ns::filter_by_confirmed(sample_words, "ar");

        assertx::is_true(filtered_values.size() == 2, "test_filterByConfirmed_splitConfirms is_true failed");
        assertx::are_equal("later", filtered_values.at(0), "test_filterByConfirmed_splitConfirms are_equal failed");
        assertx::are_equal("arose", filtered_values.at(1), "test_filterByConfirmed_splitConfirms are_equal failed");
    }

    void test_filterByConfirmed_splitAndJoinedConfirms()
    {
        auto filtered_values = wordle_solver_ns::filter_by_confirmed(sample_words, "are");

        assertx::is_true(filtered_values.size() == 2, "test_filterByConfirmed_splitAndJoinedConfirms is_true failed");
        assertx::are_equal("later", filtered_values.at(0), "test_filterByConfirmed_splitAndJoinedConfirms are_equal failed");
        assertx::are_equal("arose", filtered_values.at(1), "test_filterByConfirmed_splitAndJoinedConfirms are_equal failed");
    }

    void test_filterByRejectedLetters_emptyPatternEmptyConfirmedEmptyAttempted()
    {
        std::vector<std::string> attempted {};
        auto filtered_values = wordle_solver_ns::filter_by_rejected_letters(sample_words, "#####", "", attempted);

        assertx::is_true(filtered_values.size() == 3, "test_filterByRejectedLetters_emptyPatternEmptyConfirmedEmptyAttempted is_true failed");
    }

    
    void test_filterByRejectedLetters_emptyPatternEmptyConfirmedSingleAttempted()
    {
        std::vector<std::string> attempted {"knife"};
        auto filtered_values = wordle_solver_ns::filter_by_rejected_letters(sample_words, "#####", "", attempted);

        assertx::is_true(filtered_values.size() == 0, "test_filterByRejectedLetters_emptyPatternEmptyConfirmedSingleAttempted is_true failed");
    }

    void test_filterByRejectedLetters_emptyPatternSingleConfirmedSingleAttempted()
    {
        std::vector<std::string> attempted {"knife"};
        auto filtered_values = wordle_solver_ns::filter_by_rejected_letters(sample_words, "#####", "e", attempted);

        assertx::is_true(filtered_values.size() == 2, "test_filterByRejectedLetters_emptyPatternSingleConfirmedSingleAttempted is_true failed");
        assertx::are_equal("later", filtered_values.at(0), "test_filterByRejectedLetters_emptyPatternSingleConfirmedSingleAttempted are_equal failed");
        assertx::are_equal("arose", filtered_values.at(1), "test_filterByRejectedLetters_emptyPatternSingleConfirmedSingleAttempted are_equal failed");
    }

    void test_filterByRejectedLetters_singlePatternSingleConfirmedSingleAttempted()
    {
        std::vector<std::string> attempted {"knife"};
        auto filtered_values = wordle_solver_ns::filter_by_rejected_letters(sample_words, "###e#", "e", attempted);
        assertx::is_true(filtered_values.size() == 2, "test_filterByRejectedLetters_singlePatternSingleConfirmedSingleAttempted is_true failed");
        assertx::are_equal("later", filtered_values.at(0), "test_filterByRejectedLetters_singlePatternSingleConfirmedSingleAttempted are_equal failed");
        assertx::are_equal("arose", filtered_values.at(1), "test_filterByRejectedLetters_singlePatternSingleConfirmedSingleAttempted are_equal failed");
    }

    void run_tests()
    {
        test_filterByPattern_emptyPattern();
        test_filterByPattern_partialPattern();
        test_filterByPattern_fullPattern();

        test_filterByConfirmed_emptyConfirms();
        test_filterByConfirmed_singleConfirms();
        test_filterByConfirmed_joinedConfirms();
        test_filterByConfirmed_splitConfirms();
        test_filterByConfirmed_splitAndJoinedConfirms();

        test_filterByRejectedLetters_emptyPatternEmptyConfirmedEmptyAttempted();
        test_filterByRejectedLetters_emptyPatternEmptyConfirmedSingleAttempted();
        test_filterByRejectedLetters_emptyPatternSingleConfirmedSingleAttempted();
        test_filterByRejectedLetters_singlePatternSingleConfirmedSingleAttempted();
    }
}
