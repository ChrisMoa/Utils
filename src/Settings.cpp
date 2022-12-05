/**
 * @file Settings.cpp
 * @author bodmaier
 * @brief contains a base structure where class parameter can be written and serialized
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <Settings.hpp>
#include <iostream>
#include <sstream>
#include <Assert.hpp>
#include <iomanip>

#define checkKey() \
    ;              \
    assert_exception(hasValue(key), invalid_argument(_name + "contains no key \"" + key + "\""));

namespace Util
{
    using namespace std;
    Settings::Settings(string name) : _name(name)
    {
    }
    Settings::Settings() : _name("default")
    {
    }

    Settings::~Settings()
    {
    }

    void Settings::set(const string key, const string value)
    {
        _parameters[key] = "\"" + value + "\"";
    }
    void Settings::get(const string key, string &value)
    {
        checkKey();
        value = _parameters[key];
    }

    void Settings::set(const string key, const int value)
    {
        _parameters[key] = to_string(value);
    }
    void Settings::get(const string key, int &value)
    {
        checkKey();
        stringstream ss;
        ss << _parameters[key];
        ss >> value;
    }

    void Settings::set(const string key, const size_t value)
    {
        _parameters[key] = to_string(value);
    }
    void Settings::get(const string key, size_t &value)
    {
        checkKey();
        stringstream ss;
        ss << _parameters[key];
        ss >> value;
    }

    void Settings::set(const string key, const double value)
    {
        _parameters[key] = to_string(value);
    }
    void Settings::get(const string key, double &value)
    {
        checkKey();
        stringstream ss;
        ss << _parameters[key];
        ss >> value;
    }

    void Settings::set(const string key, const vector<string> value)
    {
        string val("[");
        for (auto parameter : value)
        {
            val += "\"" + parameter + "\",";
        }
        val.erase(val.end() - 1);
        val += "]";
        _parameters[key] = val;
    }

    void Settings::get(const string key, vector<string> &value)
    {
        checkKey();
        string val = _parameters[key];
        size_t len = val.length();
        if (len < 3)
        {
            return;
        }
        value.clear();
        size_t lastPos = 1;
        for (int i = lastPos; i < len - 3; i++)
        {
            if (val.at(i) == ',')
            {
                value.push_back(val.substr(lastPos + 1, i - 3 - lastPos)); // ["...","..."];
                lastPos = i;
            }
        }
        value.push_back(val.substr(lastPos + 1, lastPos - len - 3)); // ["...","..."];
    }

    string Settings::toString()
    {
        string retVal;
        for (auto parameter : _parameters)
        {
            retVal += parameter.first + "=" + parameter.second + ";";
        }
        return retVal;
    }

    void Settings::fromString(const string values)
    {
    }

    bool Settings::hasValue(const string key)
    {
        auto iter = _parameters.find(key);
        return iter != _parameters.end();
    }

    vector<string> Settings::getKeys()
    {
        vector<string> keys;
        for (auto key : _parameters)
        {
            keys.push_back(key.first);
        }
        return keys;
    }

}