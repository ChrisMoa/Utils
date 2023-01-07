#include <fmt/format.h>

#include "Assert.hpp"
#include "FileEncryption.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

#include <JsonUtils.hpp>
#include <Logging.hpp>
#include <json/json.h>
#include <rapidcsv.h>

#include <Poco/Data/Session.h>

#include <CThread.h>
#include <ExecutionThread.hpp>

#include "cryptopp/aes.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"

#include <sstream>

using namespace CryptoPP;

int main() {
    Log::initLogger();
    LWARNING("Begin");

    std::string pdata = "CTR encrypt mode 1234567890";

    int keySize;
    auto key = Crypto::getKey(keySize);
    int ivSize;
    auto iv = Crypto::getIV(ivSize);

    Crypto::encryptFile(key, keySize, iv, ivSize, "Testdokument.txt");
    std::string text;

    Crypto::decryptFile(key, keySize, iv, ivSize, "Testdokument.txt", text);

    LERROR("text: {}", text);

    // LINFO("plain before enc: {}", pdata);
    // auto cipher = Crypto::encryptString(pdata, key, keySize, iv, ivSize);
    // auto plain = Crypto::decryptString(cipher, key, keySize, iv, ivSize);
    // LINFO("plain after enc: {}", plain);

    /*********************************\
    \*********************************/
    // auto result1 = Crypto::encryptFile(pdata.c_str(), key, sizeof(key), iv,
    //                                    sizeof(iv), pdata.size());

    // auto result2 = Crypto::decryptFile(result1, key, sizeof(key), iv,
    // sizeof(iv),
    //                                    pdata.size());

    fmt::report_system_error(0, "main()");
    return 0;
}