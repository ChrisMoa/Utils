#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <vector>
#include <map>

namespace String
{
    /**
     * @brief Interface class for printable structs and classes
     *
     */
    class IString
    {
    public:
        /**
         * @brief interface for printing the object
         * @param void
         * @return the printed string
         */
        virtual std::string toString() = 0;
    };

    class ExtendedString : public std::string, public IString
    {
    public:
        ExtendedString(std::string str = "");
        ~ExtendedString();

        /**
         * @brief convertes the extended string to std::string
         * @return the converted string
         */
        std::string toString() override;

        /**
         * @brief converts a list to a listString
         * @param list the list which should be serialized to a string
         * @param deLimiter the delimiter string
         * @return the serialized list
         */
        static std::string listToString(const std::vector<std::string> list, const std::string deLimiter = ";");

        /**
         * @brief saves a serialiszed list to a vector of strings
         * @param serializedList the serialized list string
         * @param deLimiter the delimiter string
         * @return the created list
         */
        static std::vector<std::string> extractList(std::string serializedList, const std::string deLimiter = ";");

    private:
        std::string container = ""; //! the additional container in which the std::string will be stored
    };
} // namespace String

#endif // endif STRINGUTILSHPP