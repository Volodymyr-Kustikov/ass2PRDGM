#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

class ConfigManager {
public:
    enum class ConfigType {
        STRING,
        INTEGER,
        BOOLEAN,
        DOUBLE,
        LIST
    };

    enum class ConfigResult {
        SUCCESS,
        KEY_NOT_FOUND,
        INVALID_TYPE,
        INVALID_VALUE,
        FILE_ERROR,
        PARSE_ERROR
    };

    struct ConfigValue {
        ConfigType type;
        std::string stringValue;
        int intValue;
        bool boolValue;
        double doubleValue;
        std::vector<std::string> listValue;

        ConfigValue() : type(ConfigType::STRING), intValue(0), boolValue(false), doubleValue(0.0) {}
    };

private:
    std::map<std::string, ConfigValue> configMap;
    std::string configFilePath;
    std::string configFileName;
    bool isDirty;
    bool autoSaveEnabled;

    // Default configurations
    std::map<std::string, ConfigValue> defaultConfigs;

public:
    // Constructors and Destructor
    ConfigManager();
    explicit ConfigManager(const std::string& configFile);
    ~ConfigManager();

    // Configuration File Operations
    ConfigResult loadConfig();
    ConfigResult saveConfig();
    ConfigResult loadFromFile(const std::string& filename);
    ConfigResult saveToFile(const std::string& filename);

    // String Configuration
    ConfigResult setString(const std::string& key, const std::string& value);
    ConfigResult getString(const std::string& key, std::string& value) const;
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;

    // Integer Configuration
    ConfigResult setInt(const std::string& key, int value);
    ConfigResult getInt(const std::string& key, int& value) const;
    int getInt(const std::string& key, int defaultValue = 0) const;

    // Boolean Configuration
    ConfigResult setBool(const std::string& key, bool value);
    ConfigResult getBool(const std::string& key, bool& value) const;
    bool getBool(const std::string& key, bool defaultValue = false) const;

    // Double Configuration
    ConfigResult setDouble(const std::string& key, double value);
    ConfigResult getDouble(const std::string& key, double& value) const;
    double getDouble(const std::string& key, double defaultValue = 0.0) const;

    // List Configuration
    ConfigResult setList(const std::string& key, const std::vector<std::string>& value);
    ConfigResult getList(const std::string& key, std::vector<std::string>& value) const;
    std::vector<std::string> getList(const std::string& key, const std::vector<std::string>& defaultValue = {}) const;

    // Generic Configuration
    ConfigResult setValue(const std::string& key, const ConfigValue& value);
    ConfigResult getValue(const std::string& key, ConfigValue& value) const;
    bool hasKey(const std::string& key) const;
    ConfigResult removeKey(const std::string& key);

    // Batch Operations
    ConfigResult setMultiple(const std::map<std::string, ConfigValue>& configs);
    std::map<std::string, ConfigValue> getAll() const;
    std::vector<std::string> getAllKeys() const;
    ConfigResult importConfig(const std::map<std::string, ConfigValue>& configs, bool overwrite = false);

    // Default Configuration Management
    void setDefaultString(const std::string& key, const std::string& value);
    void setDefaultInt(const std::string& key, int value);
    void setDefaultBool(const std::string& key, bool value);
    void setDefaultDouble(const std::string& key, double value);
    void setDefaultList(const std::string& key, const std::vector<std::string>& value);
    ConfigResult restoreDefaults();
    ConfigResult restoreDefault(const std::string& key);

    // Validation
    bool validateConfig() const;
    std::vector<std::string> getValidationErrors() const;
    ConfigResult validateKey(const std::string& key) const;
    ConfigResult validateValue(const std::string& key, const ConfigValue& value) const;

    // File Management
    std::string getConfigFilePath() const;
    ConfigResult setConfigFilePath(const std::string& path);
    bool configFileExists() const;
    ConfigResult createConfigFile();
    ConfigResult backupConfig(const std::string& backupPath = "") const;

    // Auto-save Management
    void setAutoSave(bool enabled);
    bool isAutoSaveEnabled() const;
    bool isDirtyConfig() const;
    void markClean();
    void markDirty();

    // Utility Functions
    void clear();
    size_t getConfigCount() const;
    std::string getConfigSummary() const;
    ConfigResult exportToJson(const std::string& filename) const;
    ConfigResult importFromJson(const std::string& filename);

    // Search and Filter
    std::vector<std::string> findKeys(const std::string& pattern) const;
    std::map<std::string, ConfigValue> getConfigsByPrefix(const std::string& prefix) const;
    std::map<std::string, ConfigValue> getConfigsByType(ConfigType type) const;

    // Configuration Sections
    ConfigResult createSection(const std::string& section);
    ConfigResult deleteSection(const std::string& section);
    std::vector<std::string> getSections() const;
    std::map<std::string, ConfigValue> getSection(const std::string& section) const;

    // Type Conversion Helpers
    static std::string configTypeToString(ConfigType type);
    static ConfigType stringToConfigType(const std::string& typeStr);
    static std::string configResultToString(ConfigResult result);

    // Operators
    ConfigValue& operator[](const std::string& key);
    const ConfigValue& operator[](const std::string& key) const;

private:
    // Internal File Operations
    ConfigResult parseConfigFile(const std::string& content);
    std::string generateConfigContent() const;
    ConfigResult parseJsonFile(const std::string& content);
    std::string generateJsonContent() const;

    // Internal Validation
    bool isValidKey(const std::string& key) const;
    bool isValidStringValue(const std::string& value) const;
    bool isValidIntValue(const std::string& value) const;
    bool isValidBoolValue(const std::string& value) const;
    bool isValidDoubleValue(const std::string& value) const;

    // Internal Utilities
    std::string trim(const std::string& str) const;
    std::vector<std::string> split(const std::string& str, char delimiter) const;
    std::string join(const std::vector<std::string>& list, const std::string& separator) const;
    std::string escapeString(const std::string& str) const;
    std::string unescapeString(const std::string& str) const;

    // Internal Conversion
    ConfigValue stringToConfigValue(const std::string& str, ConfigType type) const;
    std::string configValueToString(const ConfigValue& value) const;

    // Auto-save
    void autoSaveIfNeeded();
    void setupDefaultConfigs();

    // Error Handling
    void logError(const std::string& operation, const std::string& error) const;
    std::string getLastSystemError() const;
};

#endif // CONFIGMANAGER_H