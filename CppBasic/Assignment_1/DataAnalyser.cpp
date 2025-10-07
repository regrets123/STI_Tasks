#include "DataAnalyser.h"
#include <iomanip>
#include <iostream>

void DataAnalyser::CalculateData() const
{
    Results data;
    data.ValueCount = static_cast<float>(dataCollection->size()); 
    for (const auto& dataSet : *dataCollection)
    {
        data.TotalSum += dataSet.second;
        CalcMin(dataSet,data.MinValue);
        CalcMax(dataSet,data.MaxValue);
     
    }
    data.AverageValue = data.TotalSum / data.ValueCount;
    for (const auto& dataSet : *dataCollection)
    {
        float diff = dataSet.second - data.AverageValue;
        data.Variance += diff * diff;
    }
    data.Variance /= data.ValueCount; 
    data.StdDeviation = std::sqrt(data.Variance);
    PrintData(data);
    
}
void DataAnalyser::SortData()
{
    //newest, oldest, specific value both date and temperature, biggest first, smallest first
}
void DataAnalyser::LookupValue()
{
    
}
void DataAnalyser::LookupDate()
{
    
}
void DataAnalyser::CalcMax(const std::pair<time_t, float>& toCalc, std::pair<time_t, float>& maxValue)
{
    if (toCalc.second > maxValue.second) {
        maxValue.first = toCalc.first;  
        maxValue.second = toCalc.second;
    }
}

void DataAnalyser::CalcMin(const std::pair<time_t, float>& toCalc, std::pair<time_t, float>& minValue)
{
    if (toCalc.second < minValue.second) {
        minValue.first = toCalc.first;
        minValue.second = toCalc.second;
    }
}
void DataAnalyser::PrintData(const Results& result) const
{
    std::tm timeInfo;
    std::cout << calcMsg << result.ValueCount << '\n';
    std::cout << sumMsg << result.TotalSum <<'\n';
    std::cout << averageMsg << result.AverageValue <<'\n';
    std::cout << maxMsg << result.MaxValue.second <<'\n';
    if (localtime_s(&timeInfo, &result.MaxValue.first) == 0) {
        std::cout << dateMsg << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << '\n';
    }
    std::cout << minMsg << result.MinValue.second <<'\n';
    if (localtime_s(&timeInfo, &result.MinValue.first) == 0)
    {
        std::cout << dateMsg << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << '\n';
    }
    std::cout << varianceMsg << result.Variance << '\n';
    std::cout << deviationMsg << result.StdDeviation <<'\n';
}
