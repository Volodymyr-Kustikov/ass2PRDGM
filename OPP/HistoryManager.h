#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <deque>
#include <chrono>

class TextBuffer;

class HistoryManager {
public:
    struct HistoryState {
        std::string content;
        std::string operation;
        std::chrono::system_clock::time_point timestamp;
        size_t cursorPosition;

        HistoryState() : cursorPosition(0) {}
        HistoryState(const std::string& c, const std::string& op, size_t pos = 0)
                : content(c), operation(op), cursorPosition(pos),
                  timestamp(std::chrono::system_clock::now()) {}
    };

    enum class ClipboardType {
        TEXT,
        FORMATTED,
        BINARY
    };

private:
    std::deque<HistoryState> undoStack;
    std::deque<HistoryState> redoStack;
    size_t maxHistorySize;
    size_t currentPosition;

    // Clipboard data
    std::string clipboardText;
    std::vector<char> clipboardBinary;
    ClipboardType clipboardType;
    bool clipboardEmpty;

    // Configuration
    bool autoSaveEnabled;
    size_t autoSaveInterval; // in operations
    size_t operationCounter;

public:
    // Constructors and Destructor
    HistoryManager();
    explicit HistoryManager(size_t maxHistorySize);
    ~HistoryManager() = default;

    // Disable copy constructor and assignment operator
    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;

    // State Management
    void saveState(const TextBuffer& buffer, const std::string& operation = "");
    bool undo(TextBuffer& buffer);
    bool redo(TextBuffer& buffer);
    void clearHistory();

    // History Information
    size_t getUndoCount() const;
    size_t getRedoCount() const;
    bool canUndo() const;
    bool canRedo() const;
    size_t getMaxHistorySize() const;
    void setMaxHistorySize(size_t size);

    // History Navigation
    std::vector<std::string> getUndoOperations() const;
    std::vector<std::string> getRedoOperations() const;
    const HistoryState& getCurrentState() const;
    bool goToState(size_t stateIndex, TextBuffer& buffer);

    // Clipboard Operations
    void copyToClipboard(const std::string& text);
    void copyToClipboard(const std::vector<char>& data);
    void copyFromBuffer(const TextBuffer& buffer);
    void copyFromBuffer(const TextBuffer& buffer, size_t start, size_t length);

    bool pasteFromClipboard(TextBuffer& buffer);
    bool pasteFromClipboard(TextBuffer& buffer, size_t position);

    void cutFromBuffer(TextBuffer& buffer, size_t start, size_t length);
    void cutFromBuffer(TextBuffer& buffer); // Cut all

    // Clipboard Information
    bool isClipboardEmpty() const;
    ClipboardType getClipboardType() const;
    std::string getClipboardText() const;
    std::vector<char> getClipboardBinary() const;
    size_t getClipboardSize() const;
    void clearClipboard();

    // Advanced Operations
    bool insertWithReplacement(TextBuffer& buffer, size_t position, size_t length, const std::string& newText);
    bool replaceAll(TextBuffer& buffer, const std::string& searchText, const std::string& replaceText);
    bool replaceSelection(TextBuffer& buffer, size_t start, size_t length, const std::string& newText);

    // Batch Operations
    void beginBatchOperation();
    void endBatchOperation(const std::string& batchName = "Batch Operation");
    bool isBatchMode() const;

    // Auto-save Configuration
    void setAutoSave(bool enabled, size_t interval = 10);
    bool isAutoSaveEnabled() const;
    size_t getAutoSaveInterval() const;

    // State Compression
    void compressHistory();
    size_t getHistoryMemoryUsage() const;

    // Export/Import History
    std::string exportHistory() const;
    bool importHistory(const std::string& data);

    // Utility Functions
    std::string getOperationSummary() const;
    std::vector<std::chrono::system_clock::time_point> getOperationTimestamps() const;
    size_t getOperationCount() const;

    // Debugging
    void printHistory() const;
    bool validateHistoryIntegrity() const;

private:
    // Internal state management
    void addToUndoStack(const HistoryState& state);
    void clearRedoStack();
    void enforceHistoryLimit();

    // Batch operation state
    bool batchMode;
    std::vector<HistoryState> batchStates;

    // Helper methods
    bool isValidState(const HistoryState& state) const;
    std::string compressContent(const std::string& content) const;
    std::string decompressContent(const std::string& compressed) const;

    // Auto-save helpers
    void checkAutoSave(const TextBuffer& buffer);

    // Memory management
    void optimizeMemoryUsage();
    size_t calculateStateSize(const HistoryState& state) const;

    // Utility
    std::string generateOperationId() const;
    std::string formatTimestamp(const std::chrono::system_clock::time_point& timestamp) const;
};

#endif // HISTORYMANAGER_H