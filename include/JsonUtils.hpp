#ifndef JSONUTILS_HPP
#define JSONUTILS_HPP

#include <json/json.h>

namespace Util
{
    class IJsonSerializable
    {
    public:
        virtual ~IJsonSerializable(void){};
        virtual void Serialize(Json::Value &root) = 0;
        virtual void Deserialize(Json::Value &root) = 0;
    };

    class CJsonSerializer
    {
    public:
        static bool Serialize(IJsonSerializable *pObj, std::string &output)
        {

            if (pObj == NULL)
                return false;

            Json::Value serializeRoot;
            pObj->Serialize(serializeRoot);

            Json::StyledWriter writer;
            output = writer.write(serializeRoot);
            return true;
        }
        static bool Deserialize(IJsonSerializable *pObj, std::string &input)
        {
            if (pObj == NULL)
                return false;

            Json::Value deserializeRoot;
            Json::Reader reader;

            if (!reader.parse(input, deserializeRoot))
                return false;

            pObj->Deserialize(deserializeRoot);

            return true;
        }

    private:
        CJsonSerializer(void){};
    };

}

#endif // JSONUTILS_HPP
