#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>

class TextBuffer;

class FileManager {
public:
    enum class FileMode {
        TEXT,
        BINARY
    };

    enum class FileResult {
        SUCCESS,
        FILE_NOT_FOUND,
        PERMISSION_DENIED,
        INVALID_PATH,
        WRITE_ERROR,
        READ_ERROR,
        UNKNOWN_ERROR
    };

private:
    std::string lastErrorMessage;
    std::string currentWorkingDirectory;

public:
    // Constructors
    FileManager();
    explicit FileManager(const std::string& workingDirectory);
    ~FileManager() = default;

    // Text File Operations
    FileResult saveTextFile(const std::string& filename, const TextBuffer& buffer);
    FileResult loadTextFile(const std::string& filename, TextBuffer& buffer);

    // Binary File Operations
    FileResult saveBinaryFile(const std::string& filename, const std::vector<char>& data);
    FileResult loadBinaryFile(const std::string& filename, std::vector<char>& data);

    // File Information
    bool fileExists(const std::string& filename) const;
    size_t getFileSize(const std::string& filename) const;
    bool isReadable(const std::string& filename) const;
    bool isWritable(const std::string& filename) const;

    // Path Operations
    std::string getFullPath(const std::string& filename) const;
    std::string getWorkingDirectory() const;
    bool setWorkingDirectory(const std::string& directory);

    // Utility Functions
    std::vector<std::string> listFiles(const std::string& directory = "") const;
    bool createDirectory(const std::string& path) const;
    bool deleteFile(const std::string& filename);

    // Error Handling
    std::string getLastError() const;
    void clearError();

    // Static Utility Methods
    static std::string getFileExtension(const std::string& filename);
    static std::string getBaseName(const std::string& filename);
    static std::string getDirectoryPath(const std::string& filename);
    static bool isValidFilename(const std::string& filename);

private:
    void setError(const std::string& error);
    FileResult handleFileError(const std::ios& stream, const std::string& filename, const std::string& operation);
    std::string sanitizePath(const std::string& path) const;
    bool validatePath(const std::string& path) const;
};

#endif // FILEMANAGER_H