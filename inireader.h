#ifndef INI_READER_H
#define INI_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

class IniReader {
public:
    IniReader(const std::string& filename);
    std::string GetValue(const std::string& section, const std::string& key, const std::string& defaultValue = "") const;

    short ParseFile();

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    std::string m_strConfigFile;
};

#endif // INI_READER_H
