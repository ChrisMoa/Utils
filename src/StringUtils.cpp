#include "StringUtils.hpp"
#include <iterator>

namespace String
{

    ExtendedString::ExtendedString(std::string str) : container(str)
    {
    }

    ExtendedString::~ExtendedString()
    {
    }

    std::string ExtendedString::toString()
    {
        return container;
    }

    std::string ExtendedString::listToString(const std::vector<std::string> list, const std::string deLimiter)
    {
        std::string retString;
        for (auto &element : list)
        {
            retString += element + deLimiter;
        }
        return retString;
    }

    std::vector<std::string> ExtendedString::extractList(std::string serializedList, const std::string deLimiter)
    {
        std::vector<std::string> extractedlist;
        size_t pos = serializedList.find(deLimiter);
        while (pos < serializedList.size())
        {
            extractedlist.push_back(serializedList.substr(0, pos));
            serializedList.erase(0, pos + deLimiter.size());
            pos = serializedList.find(deLimiter);
        }
        // push last string élement if exists
        if (serializedList.size())
        {
            extractedlist.push_back(serializedList);
        }
        return extractedlist;
    }

}