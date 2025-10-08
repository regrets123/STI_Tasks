#include "DataAnalyser.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

#include "Controller.h"

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
    std::cout << earlySortMsg << '\n' << oldSortMsg << '\n' << coldSortMsg << '\n' << hotSortMsg << '\n';
    SortType choice = static_cast<SortType>(Controller::GetValidNumber());
    switch (choice)
    {
    case SortType::Earliest:
        {
            break; 
        }
    case SortType::Oldest:
        {
            break;        
        }
    case SortType::Hottest:
        {
            break;            
        }
    case SortType::Coldest:
        {
            break;            
        }
    default:
        std::cout << Controller::ErrorMsg << '\n';
    }
}

const std::vector<std::pair<time_t, float>>& DataAnalyser::ByValueAscending() const
{
    sortBuffer.assign(dataCollection->begin(), dataCollection->end());
    std::sort(sortBuffer.begin(), sortBuffer.end(), 
        [](const auto& a, const auto& b) { return a.second < b.second; });
    return sortBuffer;
}

const std::vector<std::pair<time_t, float>>& DataAnalyser::ByValueDescending() const
{
    sortBuffer.assign(dataCollection->begin(), dataCollection->end());
    std::sort(sortBuffer.begin(), sortBuffer.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    return sortBuffer;
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
        std::cout << dateMsg << std::put_time(&timeInfo, formatArg) << '\n';
    }
    std::cout << minMsg << result.MinValue.second <<'\n';
    if (localtime_s(&timeInfo, &result.MinValue.first) == 0)
    {
        std::cout << dateMsg << std::put_time(&timeInfo, formatArg) << '\n';
    }
    std::cout << varianceMsg << result.Variance << '\n';
    std::cout << deviationMsg << result.StdDeviation <<'\n';
}
