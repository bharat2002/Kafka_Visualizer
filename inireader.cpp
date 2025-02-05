#include "inireader.h"

IniReader::IniReader(const std::string& filename) {
    m_strConfigFile = filename;
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

short IniReader::ParseFile() {
    short lnReturn = -1;
    std::ifstream file(m_strConfigFile);
    std::string line, section, key, value;
    bool isFileEmpty = true;
    if(file.is_open())
    {
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
                isFileEmpty=false;
            }
        }
        lnReturn=0;
    }
    else
    {
        lnReturn = -1;
    }
    if(isFileEmpty)
    {
        lnReturn = -1;
    }
    return lnReturn;
}

short IniReader::SetValue(const std::string& section, const std::string& key, const std::string Value)
{
    short lnReturn = -1;
    if(data.end() == data.find(section))
    {
        data[section] = std::unordered_map<std::string, std::string>();
    }

    auto Iterator = data[section].find(key);
    if(data[section].end() != Iterator )
    {
        Iterator->second = Value;
        lnReturn = 0;
    }
    else
    {
        data[section][key] = Value;
        lnReturn = 0;
    }

    return lnReturn;
}
