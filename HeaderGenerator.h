#pragma once
#include <map>

// Singelton
class HeaderGenerator
{
    int generatedSoftwareId;
    std::map<int, int> softwareSequenceIdMap;
    HeaderGenerator() = default;

public:
    HeaderGenerator(const HeaderGenerator&) = delete;
    HeaderGenerator& operator=(HeaderGenerator&) = delete;

    static HeaderGenerator& getHeaderGenerator();
    int generateSoftwareId();
    int generateSequenceId(const int& softwareId);
};
