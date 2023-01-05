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

using namespace CryptoPP;
int main() {
  Log::initLogger();
  LWARNING("Begin");
  Json::Value val;
  val["Test"] = 10;

  byte key[AES::DEFAULT_KEYLENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8',
                                      '1', '2', '3', '4', '5', '6', '7', '8'};
  byte iv[AES::BLOCKSIZE] = {'8', '7', '6', '5', '4', '3', '2', '1',
                             '8', '7', '6', '5', '4', '3', '2', '1'};

  /*********************************\
  \*********************************/
  std::string pdata = "CTR encrypt mode 1234567890";
  auto result1 = Crypto::encryptFile(pdata.c_str(), key, sizeof(key), iv,
                                     sizeof(iv), pdata.size());

  auto result2 = Crypto::decryptFile(result1, key, sizeof(key), iv, sizeof(iv),
                                     pdata.size());

  LINFO("Test: {}", val.toStyledString());
  fmt::report_system_error(0, "main()");
  return 0;
}