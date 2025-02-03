#include "inireader.h"

IniReader::IniReader(const std::string& filename) {
    ParseFile(filename);
}

std::string IniReader::GetValue(const std::string& section, const std::string& key, const std::string& defaultValue) const {
    auto itSection = data.find(section);
    if (itSection != data.end()) {
        auto itKey = itSection->second.find(key);
        if (itKey != itSection->second.end()) {
            return itKey->second;
        }
    }
    return defaultValue;
}

void IniReader::ParseFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, section, key, value;

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t\r\n")); // Trim leading whitespace
        if (line.empty() || line[0] == ';') {
            continue; // Skip empty lines and comments
        }

        if (line[0] == '[') {
            section = line.substr(1, line.find(']') - 1);
        } else {
            std::size_t pos = line.find('=');
            if (pos != std::string::npos) {
                key = line.substr(0, pos);
                value = line.substr(pos + 1);
                data[section][key] = value;
            }
        }
    }
}
