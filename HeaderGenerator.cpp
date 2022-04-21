#include "HeaderGenerator.h"

HeaderGenerator& HeaderGenerator::getHeaderGenerator()
{
    static HeaderGenerator headerGenerator;
    return headerGenerator;
}

int HeaderGenerator::generateSoftwareId()
{
    if (generatedSoftwareId == 255)
        generatedSoftwareId = 0;
    else
        generatedSoftwareId++;
    softwareSequenceIdMap[generatedSoftwareId] = 0;
    return generatedSoftwareId;
}

int HeaderGenerator::generateSequenceId(const int& softwareId)
{
    if (softwareId > 255)
        return 0;
    auto currentSequenceId = softwareSequenceIdMap[softwareId];
    if (currentSequenceId == 65535)
        currentSequenceId = 0;
    else
        currentSequenceId++;
    softwareSequenceIdMap[softwareId] = currentSequenceId;
    return currentSequenceId;
}
