#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>


class DataAnalyser
{
public:
    DataAnalyser(const std::shared_ptr<std::map<time_t, float>>& dataCollection)
         : dataCollection(dataCollection)
    {}
    void CalculateData() const;
    void SortData();
    void LookupValue();
    void LookupDate();
    const std::vector<std::pair<time_t, float>>& ByValueAscending() const;
    const std::vector<std::pair<time_t, float>>& ByValueDescending() const;
private:
    
    std::shared_ptr<std::map<time_t, float>> dataCollection;
    mutable std::vector<std::pair<time_t, float>> sortBuffer; 
    enum class SortType   {None,Earliest,Oldest,Hottest,Coldest ,MaxNum};
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
    
    const char* calcMsg = "Data is calculated. Total number of Data Points are: ";
    const char* sumMsg = "Total sum of all Data points are: ";
    const char* averageMsg = "Average sum of all Data points are: ";
    const char* minMsg = "The lowest value of the Data points are: ";
    const char* maxMsg = "The highest value of the Data points are: ";
    const char* dateMsg = "The date for this is :";
    const char* varianceMsg = "The variance of the Data points are: ";
    const char* deviationMsg = "The standard deviation of the Data points are: ";
    const char* formatArg = "%Y-%m-%d %H:%M:%S";
    const char* earlySortMsg = "Enter 1 if you want to sort by recent date: ";
    const char* oldSortMsg = "Enter 2 if you want to sort data by oldest date: ";
    const char* hotSortMsg = "Enter 3 if you want to sort data by hottest temperature: ";
    const char* coldSortMsg = "Enter 4 if you want to sort data by coldest temperature: ";
};
