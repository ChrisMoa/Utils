/**
 * @file FileEncryption.hpp
 * @author qtdesktop
 * @brief overwrites assertion function
 * @version 0.1
 * @date 2023-01-05
 *
 */
#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#include "Logging.hpp"
#include "cryptopp/aes.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"

namespace Crypto {

using namespace CryptoPP;

void test() {
  using namespace std;
  AutoSeededRandomPool prng;

  CryptoPP::byte key[AES::DEFAULT_KEYLENGTH];
  prng.GenerateBlock(key, sizeof(key));

  string plain = "ECB Mode Test";
  string cipher, encoded, recovered;

  /*********************************\
  \*********************************/

  // Pretty print key
  encoded.clear();
  StringSource(key, sizeof(key), true,
               new HexEncoder(new StringSink(encoded)) // HexEncoder
  );                                                   // StringSource
  cout << "key: " << encoded << endl;

  /*********************************\
  \*********************************/

  try {
    cout << "plain text: " << plain << endl;

    ECB_Mode<AES>::Encryption e;
    e.SetKey(key, sizeof(key));

    // The StreamTransformationFilter adds padding
    //  as required. ECB and CBC Mode must be padded
    //  to the block size of the cipher.
    StringSource(plain, true,
                 new StreamTransformationFilter(
                     e,
                     new StringSink(cipher)) // StreamTransformationFilter
    );                                       // StringSource
  } catch (const CryptoPP::Exception &e) {
    cerr << e.what() << endl;
    exit(1);
  }

  /*********************************\
  \*********************************/

  // Pretty print
  encoded.clear();
  StringSource(cipher, true,
               new HexEncoder(new StringSink(encoded)) // HexEncoder
  );                                                   // StringSource
  cout << "cipher text: " << encoded << endl;

  /*********************************\
  \*********************************/

  try {
    ECB_Mode<AES>::Decryption d;
    d.SetKey(key, sizeof(key));

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource s(cipher, true,
                   new StreamTransformationFilter(
                       d,
                       new StringSink(recovered)) // StreamTransformationFilter
    );                                            // StringSource

    cout << "recovered text: " << recovered << endl;
  } catch (const CryptoPP::Exception &e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

std::string encryptString(std::string plain, byte key[], int sizeKey, byte iv[],
                          int sizeIV) {
  std::string cipher;
  try {
    CTR_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, sizeKey, iv, sizeIV);

    StringSource s(plain, true,
                   new StreamTransformationFilter(e, new StringSink(cipher)));
    return cipher;
  } catch (const CryptoPP::Exception &e) {
    LWARNING("encryptString: {}", e.what());
    return NULL;
  }
}

char *encryptFile(const char *plainText, byte key[], int sizeKey, byte iv[],
                  int sizeIV, long len) {
  try {
    std::string ss(plainText, len);
    long lengSS = ss.length();

    std::string cipher = encryptString(ss, key, sizeKey, iv, sizeIV);
    len = cipher.size();
    char *writable = new char[len];
    std::copy(cipher.begin(), cipher.end(), writable);
    writable[len] = '\0';
    LINFO("encrypted: {}", writable);
    return writable;
  } catch (const Exception &e) {
    LWARNING("encryptFile: {}", e.what());
    return NULL;
  }
}

std::string decryptString(std::string cipher, byte key[], int sizeKey,
                          byte iv[], int sizeIV) {
  std::string reco;
  try {
    CTR_Mode<AES>::Decryption d;
    d.SetKeyWithIV(key, sizeKey, iv, sizeIV);

    StringSource s(cipher, true,
                   new StreamTransformationFilter(d, new StringSink(reco)));
    return reco;
  } catch (const CryptoPP::Exception &e) {
    LWARNING("decryptString: {}", e.what());
    return reco;
  }
}

char *decryptFile(const char *cipher, byte key[], int sizeKey, byte iv[],
                  int sizeIV, long len) {
  std::string ss(cipher, len);
  long lengSS = ss.length();
  std::string recovered = decryptString(ss, key, sizeKey, iv, sizeIV);
  char *writable = new char[recovered.size()];
  std::copy(recovered.begin(), recovered.end(), writable);
  writable[recovered.size()] = '\0';
  LINFO("decryped: {}", writable);
  return writable;
}

} // namespace Crypto
