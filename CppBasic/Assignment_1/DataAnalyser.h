#pragma once
#include <memory>
#include <string>
#include <unordered_map>

class DataAnalyser
{
public:
    DataAnalyser(const std::shared_ptr<std::unordered_map<time_t, float>>& dataCollection)
         : dataCollection(dataCollection)
    {}
    void CalculateData() const;
    void SortData();
    void LookupValue();
    void LookupDate();
private:
    struct Results  
    {
        float ValueCount = 0.0f;
        float TotalSum = 0.0f;
        float AverageValue = 0.0f;
        float Variance = 0.0f;
        float StdDeviation = 0.0f;
        std::pair<time_t, float> MaxValue{0, -FLT_MAX};
        std::pair<time_t, float> MinValue{0, FLT_MAX};
    };
    static void CalcMax(const std::pair<time_t, float>& toCalc, std::pair<time_t, float>& maxValue);
    static void CalcMin(const std::pair<time_t, float>& toCalc, std::pair<time_t, float>& minValue);
    void PrintData(const Results& result) const;
    
    std::string calcMsg = {"Data is calculated. Total number of Data Points are: "};
    std::string sumMsg = {"Total sum of all Data points are: "};
    std::string averageMsg = {"Average sum of all Data points are: "};
    std::string minMsg = {"The lowest value of the Data points are: "};
    std::string maxMsg = {"The highest value of the Data points are: "};
    std::string dateMsg = {"The date for this is :"};
    std::string varianceMsg = {"The variance of the Data points are: "};
    std::string deviationMsg = {"The standard deviation of the Data points are: "};
    std::shared_ptr<std::unordered_map<time_t, float>> dataCollection;
};
