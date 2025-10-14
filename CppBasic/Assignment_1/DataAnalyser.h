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
    template<typename Container> //used overloads earlier instead of template container, but managed to get this work, and its a more DRY approach.
    // Seems embedded doesn't like templates, even tho this is a pretty narrow case. 
    void CalculateData(const Container& dataCol) const; 
    void SortData();
    void LookupValue();
    void LookupDate();
    std::vector<std::pair<time_t, float>>& ByTimeDescending();
    std::vector<std::pair<time_t, float>>& ByValueAscending();
    std::vector<std::pair<time_t, float>>& ByValueDescending();
private:
    
    std::shared_ptr<std::map<time_t, float>> dataCollection;
    std::vector<std::pair<time_t, float>> sortBuffer;
    
    enum class SortType : uint8_t { none, earliest, oldest, hottest, coldest, maxNum };
    
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

    //This is apparently terrible practice in terms of memory overhead, while it saves compute, because cout has its own buffer.
    //However, if you have to support localisation, which most modern software do you need even more abstraction of the string data. 
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
    const char* findTempratureMsg = "Enter the temperature you want to look for in the data: ";
    const char* findDateMsg = "Enter the date you want to search for in the data: ";
    const char* cantFindMsg = "The data set does not contain the data you are looking for.";
    const char* findTodayMsg = "Enter 1 if you want to look for todays temperature, Enter 2 if you want to enter date on your own: ";
};
