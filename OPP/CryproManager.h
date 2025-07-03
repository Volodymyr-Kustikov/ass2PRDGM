#ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

class TextBuffer;

class CryptoManager {
public:
    enum class CryptoResult {
        SUCCESS,
        INVALID_KEY,
        EMPTY_DATA,
        LIBRARY_ERROR,
        UNKNOWN_ERROR
    };

    enum class CipherType {
        CAESAR,
        // Future extension: ROT13, VIGENERE, etc.
    };

private:
    // Dynamic library handling
    void* libraryHandle;
    bool libraryLoaded;
    std::string lastErrorMessage;

    // Function pointers for library functions
    typedef void (*EncryptFunction)(const char* input, char* output, int key, int length);
    typedef void (*DecryptFunction)(const char* input, char* output, int key, int length);

    EncryptFunction encryptFunc;
    DecryptFunction decryptFunc;

public:
    // Constructors and Destructor
    CryptoManager();
    explicit CryptoManager(const std::string& libraryPath);
    ~CryptoManager();

    // Disable copy constructor and assignment operator
    CryptoManager(const CryptoManager&) = delete;
    CryptoManager& operator=(const CryptoManager&) = delete;

    // Library Management
    bool loadCryptoLibrary(const std::string& libraryPath = "");
    void unloadLibrary();
    bool isLibraryLoaded() const;

    // Text Encryption/Decryption
    CryptoResult encrypt(const std::string& plaintext, std::string& ciphertext, int key, CipherType type = CipherType::CAESAR);
    CryptoResult decrypt(const std::string& ciphertext, std::string& plaintext, int key, CipherType type = CipherType::CAESAR);

    // Buffer Encryption/Decryption
    CryptoResult encryptBuffer(TextBuffer& buffer, int key, CipherType type = CipherType::CAESAR);
    CryptoResult decryptBuffer(TextBuffer& buffer, int key, CipherType type = CipherType::CAESAR);

    // Raw Data Encryption/Decryption
    CryptoResult encryptData(const std::vector<char>& input, std::vector<char>& output, int key, CipherType type = CipherType::CAESAR);
    CryptoResult decryptData(const std::vector<char>& input, std::vector<char>& output, int key, CipherType type = CipherType::CAESAR);

    // File Encryption/Decryption (works with FileManager)
    CryptoResult encryptFile(const std::string& inputPath, const std::string& outputPath, int key, CipherType type = CipherType::CAESAR);
    CryptoResult decryptFile(const std::string& inputPath, const std::string& outputPath, int key, CipherType type = CipherType::CAESAR);

    // Key Management
    bool isValidKey(int key, CipherType type = CipherType::CAESAR) const;
    int normalizeKey(int key, CipherType type = CipherType::CAESAR) const;
    std::vector<int> suggestKeys(CipherType type = CipherType::CAESAR) const;

    // Utility Functions
    std::string getLastError() const;
    void clearError();
    static std::string resultToString(CryptoResult result);

    // Cryptanalysis Helper Methods
    std::vector<std::string> bruteForceDecrypt(const std::string& ciphertext, CipherType type = CipherType::CAESAR);
    double calculateIC(const std::string& text) const; // Index of Coincidence

private:
    // Internal crypto operations
    CryptoResult caesarEncrypt(const std::vector<char>& input, std::vector<char>& output, int key);
    CryptoResult caesarDecrypt(const std::vector<char>& input, std::vector<char>& output, int key);

    // Library loading helpers
    bool loadLibraryFunctions();
    std::vector<std::string> getLibraryPaths() const;

    // Error handling
    void setError(const std::string& error);
    CryptoResult handleCryptoError(const std::string& operation);

    // Utility
    bool validateInput(const std::vector<char>& data, int key, CipherType type) const;
    char encryptChar(char c, int key) const;
    char decryptChar(char c, int key) const;
};

#endif // CRYPTOMANAGER_H