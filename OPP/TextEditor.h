#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <iostream>

// Forward declarations
class TextBuffer;
class FileManager;
class CryptoManager;
class DocumentManager;
class HistoryManager;

class TextEditor {
public:
    enum class EditorMode {
        SIMPLE_TEXT,
        STRUCTURED_DOCUMENT,
        ENCRYPTED_TEXT
    };

    enum class MenuResult {
        CONTINUE,
        EXIT,
        ERROR
    };

private:
    // Core components
    std::unique_ptr<TextBuffer> textBuffer;
    std::unique_ptr<FileManager> fileManager;
    std::unique_ptr<CryptoManager> cryptoManager;
    std::unique_ptr<DocumentManager> documentManager;
    std::unique_ptr<HistoryManager> historyManager;

    // Editor state
    EditorMode currentMode;
    bool isRunning;
    std::string currentFileName;
    bool hasUnsavedChanges;

    // Menu system
    std::map<int, std::function<MenuResult()>> menuHandlers;
    std::map<EditorMode, std::vector<std::pair<int, std::string>>> modeMenus;

    // Configuration
    bool autoSaveEnabled;
    size_t autoSaveInterval;
    bool encryptionEnabled;
    std::string workingDirectory;

public:
    // Constructors and Destructor
    TextEditor();
    explicit TextEditor(const std::string& workingDir);
    ~TextEditor();

    // Disable copy constructor and assignment operator
    TextEditor(const TextEditor&) = delete;
    TextEditor& operator=(const TextEditor&) = delete;

    // Main Application Interface
    int run();
    void initialize();
    void shutdown();

    // Mode Management
    void setMode(EditorMode mode);
    EditorMode getMode() const;
    std::string getModeString() const;

    // File Operations
    bool newDocument();
    bool openDocument(const std::string& filename = "");
    bool saveDocument(const std::string& filename = "");
    bool saveDocumentAs();
    bool closeDocument();

    // Configuration
    void setAutoSave(bool enabled, size_t interval = 300); // 5 minutes
    void setEncryption(bool enabled);
    void setWorkingDirectory(const std::string& directory);

    // Status Information
    bool hasUnsavedChanges() const;
    std::string getCurrentFileName() const;
    std::string getStatusString() const;
    size_t getDocumentSize() const;

    // Utility
    void showHelp() const;
    void showAbout() const;
    void showStatistics() const;

private:
    // Menu System
    void setupMenuHandlers();
    void setupModeMenus();
    void displayMenu() const;
    int getUserChoice() const;
    MenuResult processUserChoice(int choice);

    // Simple Text Mode Handlers
    MenuResult handleAppendText();
    MenuResult handleAddNewLine();
    MenuResult handleInsertText();
    MenuResult handleDeleteText();
    MenuResult handleSearchText();
    MenuResult handlePrintText();

    // File Operation Handlers
    MenuResult handleSaveFile();
    MenuResult handleLoadFile();
    MenuResult handleSaveAs();
    MenuResult handleNewFile();

    // Edit Operation Handlers
    MenuResult handleUndo();
    MenuResult handleRedo();
    MenuResult handleCopy();
    MenuResult handlePaste();
    MenuResult handleCut();
    MenuResult handleReplaceText();

    // Encryption Handlers
    MenuResult handleEncryptText();
    MenuResult handleDecryptText();
    MenuResult handleEncryptFile();
    MenuResult handleDecryptFile();
    MenuResult handleSaveEncrypted();
    MenuResult handleLoadEncrypted();

    // Document Mode Handlers
    MenuResult handleAddContactLine();
    MenuResult handleAddChecklistLine();
    MenuResult handleEditContactLine();
    MenuResult handleEditChecklistLine();
    MenuResult handleToggleChecklistItem();
    MenuResult handleSearchContacts();
    MenuResult handleSearchChecklists();
    MenuResult handleExportDocument();
    MenuResult handleImportDocument();

    // Utility Handlers
    MenuResult handleShowStatistics();
    MenuResult handleShowHelp();
    MenuResult handleChangeMode();
    MenuResult handleClearConsole();
    MenuResult handleExit();

    // Internal Operations
    void markAsModified();
    void markAsSaved();
    bool confirmUnsavedChanges();
    void updateWindowTitle();
    void refreshDisplay();

    // Input Validation
    bool validateInput(const std::string& input) const;
    std::string sanitizeInput(const std::string& input) const;
    int getValidatedIntInput(const std::string& prompt, int min, int max) const;
    std::string getValidatedStringInput(const std::string& prompt, size_t maxLength) const;

    // Error Handling
    void handleError(const std::string& operation, const std::string& error);
    void showErrorMessage(const std::string& message) const;
    void showSuccessMessage(const std::string& message) const;

    // Console Management
    void clearConsole() const;
    void pauseForInput() const;
    void displayHeader() const;
    void displayFooter() const;

    // Auto-save
    void performAutoSave();
    bool shouldAutoSave() const;
    void scheduleAutoSave();
};

#endif // TEXTEDITOR_H