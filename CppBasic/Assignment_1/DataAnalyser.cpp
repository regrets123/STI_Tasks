#include "DataAnalyser.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Controller.h"

template<typename Container>
void DataAnalyser::CalculateData(const Container& dataCol) const
{
    Results data;
    data.ValueCount = static_cast<float>(dataCol.size()); 
    for (const auto& dataSet : dataCol)
    {
        data.TotalSum += dataSet.second;
        CalcMin(dataSet, data.MinValue);
        CalcMax(dataSet, data.MaxValue);
    }
    data.AverageValue = data.TotalSum / data.ValueCount;
    for (const auto& dataSet : dataCol)
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
    case SortType::earliest:
        {
            //already sorted by this.
            CalculateData(*dataCollection);
            break; 
        }
    case SortType::oldest:
        {
            CalculateData(ByValueAscending());
            break;        
        }
    case SortType::hottest:
        {
            CalculateData(ByValueDescending());
            break;            
        }
    case SortType::coldest:
        {
            CalculateData(ByValueAscending());
            break;            
        }
    default:
        std::cout << Controller::ErrorMsg << '\n';
    }
}

std::vector<std::pair<time_t, float>>& DataAnalyser::ByValueAscending()
{
    sortBuffer.assign(dataCollection->begin(), dataCollection->end());
    std::sort(sortBuffer.begin(), sortBuffer.end(), 
        [](const auto& a, const auto& b) { return a.second < b.second; });
    return sortBuffer;
}

std::vector<std::pair<time_t, float>>& DataAnalyser::ByValueDescending()
{
    sortBuffer.assign(dataCollection->begin(), dataCollection->end());
    std::sort(sortBuffer.begin(), sortBuffer.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    return sortBuffer;
}
    
void DataAnalyser::LookupValue()
{
    std::cout << findTempratureMsg << '\n';
    float valueToFind = static_cast<float>(Controller::GetValidNumber());
    bool found = false;
    const float accuarcy = 0.001f;
    for (const auto& pair : *dataCollection) {

        if (std::abs(pair.second - valueToFind) < accuarcy )
        {
            found = true;
            std::cout << "Found value at date: " <<pair.first << "with the temp: " <<pair.second << '\n';
        }
    }
    if (!found)
    {
        std::cout << cantFindMsg << '\n';
    }
}

void DataAnalyser::LookupDate()
{
    std::tm startTm = Controller::InputDate();
    // Convert to time_t
    time_t startTime = std::mktime(&startTm);
    time_t endTime = startTime + (24 * 60 * 60); // Add 24 hours
    
    if (startTime == -1) {
        std::cout << "Invalid date" << '\n';
        return;
    }
    
    bool found = false;
    for (const auto& pair : *dataCollection) {
        if (pair.first >= startTime && pair.first < endTime) {
            // Convert time_t back to readable format for display
            std::tm* localTime = std::localtime(&pair.first);
            std::cout <<"This data was found at the date: " << std::put_time(localTime, formatArg) 
                      << " Value: " << pair.second << '\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No data found for this date" << std::endl;
    }
}

std::vector<std::pair<time_t, float>>& DataAnalyser::ByTimeDescending()
{
    sortBuffer.assign(dataCollection->rbegin(), dataCollection->rend());
    return sortBuffer;
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
