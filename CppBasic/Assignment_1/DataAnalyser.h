#pragma once
#include <memory>
#include <unordered_map>

class DataAnalyser
{
public:
    DataAnalyser(std::unordered_map<time_t, float>* dataCollection)
        : dataCollection(dataCollection)
    {
    }
    void CalculateData();
    void SortData();
    void LookupValue();
    void LookupDate();
private:
    std::unordered_map<time_t ,float>* dataCollection;
};
