/**
 * @file assert.hpp
 * @author bodmaier
 * @brief overwrites assertion function
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <exception>
#include <string>

#define ASSERT_EXCEPTION(assertion, msg) Util::assert_exception(assertion, msg)

namespace Util
{
    using namespace std;

    /**
     * @brief checks if assertion is true
     *
     * @param assertion the assertion: {false, throw exception}, {true, nothing happens}
     * @param ex exception which will be thrown if assertion is false
     */
    static void assert_exception(bool assertion, const exception &ex)
    {
        if (!assertion)
        {
            throw ex;
        }
    }

    /**
     * @brief checks if assertion is true and throw runtime error per default
     *
     * @param assertion the assertion: {false, throw exception}, {true, nothing happens}
     * @param ex the exception msg which will be thrown if assertion is false
     */
    static void assert_exception(bool assertion, const string &ex)
    {
        if (!assertion)
        {
            throw runtime_error(ex);
        }
    }
}
