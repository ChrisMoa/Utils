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
#include <fstream>
#include <iostream>
#include <string>

#include "Logging.hpp"
#include "cryptopp/aes.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"

namespace Crypto {

using namespace CryptoPP;

char* getKey(int& size) {
    CryptoPP::byte keyByte[] = { 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61 };
    // std::stringstream ss;
    // ss << keyByte;
    // LINFO("keyString: {} | size: {}", ss.str(), ss.str().size());
    size = sizeof(keyByte);
    return (char*)keyByte;
}

char* getIV(int& size) {
    CryptoPP::byte ivByte[] = { 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63 };
    // std::stringstream ss;
    // ss << std::hex << ivByte;
    // LINFO("IvString: {} | size: {}", ss.str(), ss.str().size());
    size = sizeof(ivByte);
    return (char*)ivByte;
}

std::string encryptString(std::string plain, const char* key, int sizeKey, const char* iv, int sizeIV) {
    std::string cipher;
    try {
        CTR_Mode< AES >::Encryption e;
        e.SetKeyWithIV((byte*)key, sizeKey, (byte*)iv, sizeIV);

        StringSource s(plain, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        return cipher;
    } catch (const CryptoPP::Exception& e) {
        LWARNING("encryptString: {}", e.what());
        return NULL;
    }
}

inline bool EndOfFile(const FileSource& file) {
    std::istream* stream = const_cast< FileSource& >(file).GetStream();
    return stream->eof();
}

void encryptFile(const char* key, int keySize, const char* iv, int ivSize, std::string filename) {
    LTRACE("enters encryptFile");
    try {
        CTR_Mode< AES >::Encryption e;
        e.SetKeyWithIV((byte*)key, keySize, (byte*)iv, ivSize);

        MeterFilter meter;
        StreamTransformationFilter filter(e);

        FileSource source(filename.c_str(), false);
        FileSink sink(std::string(filename + ".enc").c_str());

        source.Attach(new Redirector(filter));
        filter.Attach(new Redirector(meter));
        meter.Attach(new Redirector(sink));

        const word64 BLOCK_SIZE = 4096;
        word64 processed = 0;

        while (!EndOfFile(source) && !source.SourceExhausted()) {
            source.Pump(BLOCK_SIZE);
            filter.Flush(false);

            processed += BLOCK_SIZE;
        }

        // Signal there is no more data to process.
        // The dtor's will do this automatically.
        filter.MessageEnd();
    } catch (const CryptoPP::Exception& e) {
        LWARNING("encryptFile: {}", e.what());
    }

    LTRACE("leave encryptFile");
}

std::string decryptString(std::string cipherText, const char* key, int keySize, const char* iv, int ivSize) {
    try {
        std::string plainText;
        CTR_Mode< AES >::Decryption d;
        d.SetKeyWithIV((byte*)key, keySize, (byte*)iv, ivSize);

        StringSource s(cipherText, true, new StreamTransformationFilter(d, new StringSink(plainText)));
        return plainText;
    } catch (const CryptoPP::Exception& e) {
        LWARNING("failed to decrpyt string: ", e.what());
    }
}

void decryptFile(const char* key, int keySize, const char* iv, int ivSize, std::string filename, std::string& buffer) {
    LTRACE("enters decryptFile");
    try {
        CTR_Mode< AES >::Encryption d;
        d.SetKeyWithIV((byte*)key, keySize, (byte*)iv, ivSize);

        FileSource source(std::string(filename + ".enc").c_str(), false, new StreamTransformationFilter(d, new StringSink(buffer)));

        const word64 BLOCK_SIZE = 4096;
        word64 processed = 0;

        while (!EndOfFile(source) && !source.SourceExhausted()) {
            source.Pump(BLOCK_SIZE);
            processed += BLOCK_SIZE;
        }
    } catch (const CryptoPP::Exception& e) {
        LWARNING("decryptFile: {}", e.what());
    }

    // remove appening '\n' which comes from encryption
    while (*(buffer.end() - 1) == '\n') {
        buffer.erase(buffer.size() - 1);
    }

    LTRACE("leave decryptFile");
}

}  // namespace Crypto
