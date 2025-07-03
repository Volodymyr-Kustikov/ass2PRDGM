#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <string>
#include <vector>
#include <memory>

class TextBuffer {
private:
    std::vector<char> buffer;
    size_t currentSize;
    static const size_t INITIAL_CAPACITY = 1024;
    static const size_t GROWTH_FACTOR = 2;

public:
    // Constructors and Destructor
    TextBuffer();
    TextBuffer(const std::string& initialText);
    TextBuffer(const TextBuffer& other);
    TextBuffer& operator=(const TextBuffer& other);
    ~TextBuffer() = default;

    // Basic Operations
    void append(const std::string& text);
    void insert(size_t position, const std::string& text);
    void remove(size_t position, size_t length);
    void clear();

    // Content Access
    std::string getText() const;
    std::string getSubstring(size_t start, size_t length) const;
    char getCharAt(size_t position) const;

    // Properties
    size_t getSize() const;
    size_t getCapacity() const;
    bool isEmpty() const;

    // Search Operations
    std::vector<size_t> findAll(const std::string& searchText) const;
    size_t findFirst(const std::string& searchText, size_t startPos = 0) const;

    // Line Operations
    void addNewLine();
    size_t getLineCount() const;
    std::string getLine(size_t lineNumber) const;
    std::pair<size_t, size_t> getLinePosition(size_t lineNumber) const;

    // Utility
    void reserve(size_t newCapacity);
    std::vector<char> getRawData() const;
    void setFromRawData(const std::vector<char>& data);

    // Operators
    TextBuffer& operator+=(const std::string& text);
    bool operator==(const TextBuffer& other) const;
    bool operator!=(const TextBuffer& other) const;

private:
    void ensureCapacity(size_t requiredCapacity);
    void resize(size_t newSize);
    bool isValidPosition(size_t position) const;
};

#endif // TEXTBUFFER_H