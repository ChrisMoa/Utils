/**
 * @file FileEncryption.hpp
 * @brief overwrites assertion function
 * @date 2023-01-05
 *
 */
#pragma once

#include "cryptopp/aes.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include <string>

namespace Crypto {
/**
 * @brief defines the interface for the base encrpytion module
 */
class IEncryptionModule {
  public:
    virtual ~IEncryptionModule() {
        ;
    }

    /**
     * @brief encrypts the given string
     * @param plainText the plain text which should be encrpyted
     * @return the encrpyted text
     */
    virtual std::string encryptString(std::string plainText) = 0;

    /**
     * @brief encrypts the given file and save it to the cipherFileName
     * @param plainFileName the file which should be encrypted
     * @param cipherFileName the file in which the encrpyted text should be written
     * @note if cipherFile is empty the file itself will be overwritten
     * @return void
     */
    virtual void encryptFile(const std::string plainFileName, const std::string cipherFileName = "") = 0;

    /**
     * @brief decrypts the given string
     * @param cipherText the cipher text which should be decrpyted
     * @return the decrypted, plain text
     */
    virtual std::string decryptString(std::string cipherText) = 0;

    /**
     * @brief decrypts the given file and save it to the plainFileName
     * @param cipherFileName the encrypted file
     * @param plainFileName the decrypted, plain file
     * @note if plainFileName is empty the file itself will be overwritten
     * @return void
     */
    virtual void decryptFile(const std::string cipherFileName, const std::string plainFileName = "") = 0;

    /**
     * @brief reads the decrypted file and save it to the textBuffer
     * @param cipherFileName the encrypted file
     * @return the buffer in which the encrypted text will be written
     */
    virtual std::string readDecryptedFile(const std::string cipherFileName) = 0;
};

/**
 * @brief the encryption module where base functions are given
 * @note uses only 1-step AES encryption
 */
class BaseAESEncryptionModule : public IEncryptionModule {
  public:
    BaseAESEncryptionModule();
    ~BaseAESEncryptionModule();

    /**
     * @brief reads the key from the given file
     * @param filename the path and filename in which the key is stored
     * @return void
     */
    void readKey(const std::string filename);

    /**
     * @brief reads Initialization vector from the given file
     * @param filename the path and filename in which the Initialization vector is stored
     * @return void
     */
    void readIV(const std::string filename);

    /**
     * @brief generates the key and save it to the given filename
     * @param filename the path and filename in which the key is stored
     * @return void
     */
    static void generateKeyAndStore(const std::string filename);

    /**
     * @brief generates the Initialization vector and save it to the given filename
     * @param filename the path and filename in which the Initialization vector is stored
     * @return void
     */
    static void generateIVAndStore(const std::string filename);

    /**
     * @brief encrypts the given string
     * @param plainText the plain text which should be encrpyted
     * @return the encrpyted text
     */
    std::string encryptString(std::string plainText) override;

    /**
     * @brief encrypts the given file and save it to the cipherFileName
     * @param plainFileName the file which should be encrypted
     * @param cipherFileName the file in which the encrpyted text should be written
     * @note if cipherFile is empty the file itself will be overwritten
     * @return void
     */
    void encryptFile(const std::string plainFileName, std::string cipherFileName = "") override;

    /**
     * @brief decrypts the given string
     * @param cipherText the cipher text which should be decrpyted
     * @return the decrypted, plain text
     */
    std::string decryptString(std::string cipherText) override;

    /**
     * @brief decrypts the given file and save it to the plainFileName
     * @param cipherFileName the encrypted file
     * @param plainFileName the decrypted, plain file
     * @note if plainFileName is empty the file itself will be overwritten
     * @return void
     */
    void decryptFile(const std::string cipherFileName, std::string plainFileName = "") override;

    /**
     * @brief reads the decrypted file and save it to the textBuffer
     * @param cipherFileName the encrypted file
     * @return the buffer in which the encrypted text will be written
     */
    std::string readDecryptedFile(const std::string cipherFileName) override;

    /**
     * @brief set the applied aes key
     * @param key the aes key
     * @return void
     */
    void setKey(std::string key);
    /**
     * @brief get the applied aes key as hex string
     * @return the aes key
     */
    std::string getKey();

    /**
     * @brief sets the applied Initialization vector
     * @param iv the applied Initialization vector
     * @return void
     */
    void setIV(std::string iv);
    /**
     * @brief gets the applied Initialization vector
     * @return the applied Initialization vector
     */
    std::string getIV();

  private:
    inline bool EndOfFile(const CryptoPP::FileSource& file);

    inline CryptoPP::lword FileSize(const CryptoPP::FileSource& file);

  private:
    CryptoPP::byte key[CryptoPP::AES::MAX_KEYLENGTH];  //! the encrpytion key
    CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];  //! the Initialization vector for AES encrpytion
};

}  // namespace Crypto
