#pragma once
#include <tuple>

class DataAnalyser
{
public:
    void CalculateData();
    void SortData();
    void LookupValue();
    void LookupDate();
    bool IsInitialized() const
    { return isInitialized; }
private:
    bool isInitialized;
};
