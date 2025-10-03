#pragma once
#include <memory>
#include <unordered_map>

class DataAnalyser
{
public:
    void Initialize(std::unordered_map<time_t ,float>* dataPtr);
    void CalculateData();
    void SortData();
    void LookupValue();
    void LookupDate();
    bool IsInitialized() const
    { return isInitialized; }
private:
    bool isInitialized;
    std::unique_ptr<std::unordered_map<time_t ,float>> dataCollection;
};
