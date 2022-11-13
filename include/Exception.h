//
// Created by chris-tab on 12.05.21.
//

#ifndef EXCEPTIONH
#define EXCEPTIONH

#include <exception>
#include <string>

#define THROW_EXCEPTION(MSG) throwE(MSG)

namespace Util
{

    class Exception : public std::exception
    {
    public:
        inline Exception(std::string msg)
        {
            this->msg = msg;
        }
        const char *what() const noexcept override
        {
            return msg.c_str();
        }
        inline std::string toString(void)
        {
            return msg;
        }

    private:
        std::string msg;
    };

    inline void throwE(std::string msg)
    {
        throw Exception(msg);
    }

} // namespace Util
#endif // PROJEKT003_EXCEPTION_H
