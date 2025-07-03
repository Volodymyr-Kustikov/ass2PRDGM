#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>

class TextBuffer;

class DocumentManager {
public:
    enum class LineType {
        TEXT,
        CONTACT,
        CHECKLIST
    };

    struct ContactInfo {
        std::string name;
        std::string surname;
        std::string email;

        ContactInfo() = default;
        ContactInfo(const std::string& n, const std::string& s, const std::string& e)
                : name(n), surname(s), email(e) {}
    };

    struct ChecklistItem {
        std::string info;
        bool checked;

        ChecklistItem() : checked(false) {}
        ChecklistItem(const std::string& i, bool c = false)
                : info(i), checked(c) {}
    };

    struct DocumentLine {
        LineType type;
        std::string content;
        ContactInfo contactData;
        ChecklistItem checklistData;

        DocumentLine(LineType t = LineType::TEXT) : type(t) {}
    };

private:
    std::vector<DocumentLine> lines;
    std::map<std::string, std::vector<size_t>> searchIndex;
    bool indexEnabled;
    std::string documentTitle;
    std::string documentMetadata;

public:
    // Constructors and Destructor
    DocumentManager();
    explicit DocumentManager(const std::string& title);
    ~DocumentManager() = default;

    // Line Management
    size_t addTextLine(const std::string& text);
    size_t addContactLine(const std::string& name, const std::string& surname, const std::string& email);
    size_t addChecklistLine(const std::string& info, bool checked = false);

    // Line Editing
    bool editTextLine(size_t index, const std::string& newText);
    bool editContactLine(size_t index, const std::string& name, const std::string& surname, const std::string& email);
    bool editChecklistLine(size_t index, const std::string& info, bool checked);

    // Line Operations
    bool toggleChecklistItem(size_t index);
    bool deleteLine(size_t index);
    bool moveLine(size_t from, size_t to);
    bool copyLine(size_t from, size_t to);

    // Document Properties
    size_t getLineCount() const;
    bool isEmpty() const;
    std::string getTitle() const;
    void setTitle(const std::string& title);
    std::string getMetadata() const;
    void setMetadata(const std::string& metadata);

    // Line Access
    const DocumentLine& getLine(size_t index) const;
    LineType getLineType(size_t index) const;
    std::string getLineContent(size_t index) const;
    std::vector<DocumentLine> getAllLines() const;

    // Search Operations
    std::vector<size_t> searchInDocument(const std::string& searchText) const;
    std::vector<size_t> searchByType(LineType type) const;
    std::vector<size_t> searchContacts(const std::string& searchText) const;
    std::vector<size_t> searchChecklists(const std::string& searchText, bool checkedOnly = false) const;

    // Filtering
    std::vector<DocumentLine> getLinesByType(LineType type) const;
    std::vector<ContactInfo> getAllContacts() const;
    std::vector<ChecklistItem> getAllChecklists() const;
    std::vector<ChecklistItem> getCompletedTasks() const;
    std::vector<ChecklistItem> getPendingTasks() const;

    // Serialization
    std::string serialize() const;
    bool deserialize(const std::string& data);
    std::vector<char> serializeToBuffer() const;
    bool deserializeFromBuffer(const std::vector<char>& data);

    // Export/Import
    std::string exportToText() const;
    std::string exportToMarkdown() const;
    std::string exportToHtml() const;
    bool importFromText(const std::string& text);

    // Statistics
    size_t getTextLineCount() const;
    size_t getContactCount() const;
    size_t getChecklistCount() const;
    size_t getCompletedTaskCount() const;
    double getTaskCompletionRate() const;

    // Validation
    bool validateLine(size_t index) const;
    bool validateContact(const ContactInfo& contact) const;
    std::vector<std::string> validateDocument() const;

    // Index Management
    void enableSearchIndex(bool enable = true);
    bool isIndexEnabled() const;
    void rebuildIndex();
    void clearIndex();

    // Utility
    void clear();
    DocumentManager clone() const;
    bool isValidIndex(size_t index) const;

    // Operators
    DocumentLine& operator[](size_t index);
    const DocumentLine& operator[](size_t index) const;

private:
    // Internal helpers
    void updateSearchIndex(size_t lineIndex, const std::string& content);
    void removeFromSearchIndex(size_t lineIndex, const std::string& content);
    std::string serializeLine(const DocumentLine& line) const;
    bool deserializeLine(const std::string& data, DocumentLine& line) const;

    // Validation helpers
    bool isValidEmail(const std::string& email) const;
    bool isValidContactName(const std::string& name) const;

    // Search helpers
    std::vector<size_t> performTextSearch(const std::string& searchText) const;
    std::vector<size_t> performIndexedSearch(const std::string& searchText) const;

    // Utility helpers
    std::string toLowerCase(const std::string& text) const;
    std::vector<std::string> tokenize(const std::string& text) const;
    std::string escapeHtml(const std::string& text) const;
};

#endif // DOCUMENTMANAGER_H