#include "BaseEncryption.hpp"
#include "Logging.hpp"
#include <cstdlib>
#include <fstream>

#include "FileSystemUtils.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"

#include <iostream>

namespace Crypto {

using namespace CryptoPP;

BaseAESEncryptionModule::BaseAESEncryptionModule() {
}

BaseAESEncryptionModule::~BaseAESEncryptionModule() {
}

void BaseAESEncryptionModule::readKey(const std::string filename) {
    try {
        FileSource file(filename.c_str(), false);
        int keySize = (int)FileSize(file);
        if (keySize != AES::MAX_KEYLENGTH) {
            LWARNING("key size {} doesnt match correct size", keySize);
            return;
        }

        file.Attach(new ArraySink(key, keySize));
        file.Pump(keySize);
    } catch (const CryptoPP::Exception& e) {
        LWARNING("readKey: {}", e.what());
    }
}

void BaseAESEncryptionModule::readIV(const std::string filename) {
    try {
        FileSource file(filename.c_str(), false);
        int ivSize = (int)FileSize(file);
        if (ivSize != AES::BLOCKSIZE) {
            LWARNING("iv size {} exceeds the typical block size", ivSize);
            return;
        }
        file.Attach(new ArraySink(iv, ivSize));
        file.Pump(ivSize);
    } catch (const CryptoPP::Exception& e) {
        LWARNING("readIV: {}", e.what());
    }
}

void BaseAESEncryptionModule::generateKeyAndStore(const std::string filename) {
    try {
        AutoSeededRandomPool prng;
        CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH];
        prng.GenerateBlock(key, sizeof(key));
        ArraySource as(key, sizeof(key), true, new FileSink(filename.c_str()));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("generateKeyAndStore: {}", e.what());
    }
    return;
}

void BaseAESEncryptionModule::generateIVAndStore(const std::string filename) {
    try {
        AutoSeededRandomPool prng;
        byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        ArraySource as(iv, sizeof(iv), true, new FileSink(filename.c_str()));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("generateIVAndStore: {}", e.what());
    }
    return;
}

std::string BaseAESEncryptionModule::encryptString(std::string plainText) {
    std::string cipher;
    try {
        CTR_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

        StringSource s(plainText, true, new StreamTransformationFilter(e, new StringSink(cipher)));
        return cipher;
    } catch (const CryptoPP::Exception& e) {
        LWARNING("encryptString: {}", e.what());
        return NULL;
    }
}

void BaseAESEncryptionModule::encryptFile(const std::string plainFileName, std::string cipherFileName) {
    LTRACE("enters encryptFile");
    try {
        CTR_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

        MeterFilter meter;
        StreamTransformationFilter filter(e);

        FileSource source(plainFileName.c_str(), false);
        std::string tmpFileName = cipherFileName;
        if (tmpFileName == "") {
            tmpFileName = plainFileName + ".tmp";
        }
        FileSink sink(std::string(tmpFileName).c_str());

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
        filter.MessageEnd();
        if (cipherFileName == "") {
            Util::renameFile(tmpFileName, plainFileName);
        }
    } catch (const CryptoPP::Exception& e) {
        LWARNING("encryptFile: {}", e.what());
    }

    LTRACE("leave encryptFile");
}

std::string BaseAESEncryptionModule::decryptString(std::string cipherText) {
    try {
        std::string plainText;
        CTR_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

        StringSource s(cipherText, true, new StreamTransformationFilter(d, new StringSink(plainText)));
        return plainText;
    } catch (const CryptoPP::Exception& e) {
        LWARNING("failed to decrpyt string: ", e.what());
    }
    return std::string();
}

void BaseAESEncryptionModule::decryptFile(const std::string cipherFileName, std::string plainFileName) {
    LTRACE("enters decryptFile");
    try {
        CTR_Mode< AES >::Encryption d;
        d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

        if (plainFileName == "") {
            plainFileName = cipherFileName;
        }

        FileSource source(cipherFileName.c_str(), false, new StreamTransformationFilter(d, new FileSink(plainFileName.c_str(), false)));

        const word64 BLOCK_SIZE = 4096;
        word64 processed = 0;

        while (!EndOfFile(source) && !source.SourceExhausted()) {
            source.Pump(BLOCK_SIZE);
            processed += BLOCK_SIZE;
        }
    } catch (const CryptoPP::Exception& e) {
        LWARNING("decryptFile: {}", e.what());
    }

    LTRACE("leave decryptFile");
}

std::string BaseAESEncryptionModule::readDecryptedFile(const std::string cipherFileName) {
    LTRACE("enters decryptFile");
    std::string buffer;
    try {
        CTR_Mode< AES >::Encryption d;
        d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

        FileSource source(cipherFileName.c_str(), false, new StreamTransformationFilter(d, new StringSink(buffer)));

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
    return buffer;
}

void BaseAESEncryptionModule::setKey(std::string key) {
    try {
        if (key.size() != AES::MAX_KEYLENGTH * 2) {  // keystring has the raw hex values as char -> 2 keystringchars are 1 key value
            LWARNING("keysize {} doesnt match", key.size());
            return;
        }
        StringSource ss(key, true, new HexDecoder(new ArraySink(this->key, sizeof(this->key))));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("setKey: {}", e.what());
    }
}

std::string BaseAESEncryptionModule::getKey() {
    std::string key;
    try {
        ArraySource as(this->key, sizeof(this->key), true, new HexEncoder(new StringSink(key)));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("getKey: {}", e.what());
    }
    return key;
}

void BaseAESEncryptionModule::setIV(std::string iv) {
    try {
        if (iv.size() != AES::BLOCKSIZE * 2) {  // keystring has the raw hex values as char -> 2 keystringchars are 1 key value
            LWARNING("ivsize {} doesnt match", iv.size());
            return;
        }
        StringSource ss(iv, true, new HexDecoder(new ArraySink(this->iv, sizeof(this->iv))));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("setIV: {}", e.what());
    }
}

std::string BaseAESEncryptionModule::getIV() {
    std::string iv;
    try {
        ArraySource as(this->iv, sizeof(this->iv), true, new HexEncoder(new StringSink(iv)));
    } catch (const CryptoPP::Exception& e) {
        LWARNING("getIV: {}", e.what());
    }
    return iv;
}

inline bool BaseAESEncryptionModule::EndOfFile(const FileSource& file) {
    std::istream* stream = const_cast< FileSource& >(file).GetStream();
    return stream->eof();
}

inline lword BaseAESEncryptionModule::FileSize(const FileSource& file) {
    std::istream* stream = const_cast< FileSource& >(file).GetStream();

    std::ifstream::pos_type old = stream->tellg();
    std::ifstream::pos_type end = stream->seekg(0, std::ios_base::end).tellg();
    stream->seekg(old);

    return static_cast< lword >(end);
}

}  // namespace Crypto