/**
 * @file Settings.hpp
 * @author bodmaier
 * @brief contains a base structure where class parameter can be written and serialized
 * @version 0.1
 * @date 2022-02-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <vector>
#include <map>

namespace Util
{
    using namespace std;
    /**
     * @brief contains a base structure where class parameter can be written and serialized
     *
     */
    class Settings
    {
    public:
        /**
         * @brief Construct a new Settings object
         *
         * @param name the name which represents the Settings name
         */
        Settings(string name);
        Settings();
        ~Settings();

        void set(const string key, const string value);
        void get(const string key, string &value);

        void set(const string key, const int value);
        void get(const string key, int &value);
        void set(const string key, const double value);
        void get(const string key, double &value);

        void set(const string key, const std::vector<string> value);
        void get(const string key, std::vector<string> &value);

        /**
         * @brief converts the Settings class to a string
         *
         * @return string serializes setting
         */
        string toString();

        /**
         * @brief loads Settings from the string
         *
         * @param values contains the setting string
         */
        void fromString(const string values);

        /**
         * @brief check if Settings has the given parameter
         *
         * @param key the key to write
         */
        bool hasValue(const string key);

        /**
         * @brief Get the Keys object
         *
         * @return vector<string>
         */
        vector<string> getKeys();

    protected:
        map<string, string> _parameters;

    private:
        /* data */
        string _name;
    };

}

#endif // SETTINGS_HPP
