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
        std::tm localTime;
        localtime_s(&localTime, &dataSet.first);
        std::cout << std::put_time(&localTime, formatArg) << " " << dataSet.second << '\n';
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

//since we only have two data types in this solution i can explicitly define these two, other syntax solution would be to put the entire actual method in the header instead. Templates feels kinda messy to work with tbh.
template void DataAnalyser::CalculateData(const std::map<time_t, float>&) const;
template void DataAnalyser::CalculateData(const std::vector<std::pair<time_t, float>>&) const;

void DataAnalyser::SortData()
{
    std::cout << earlySortMsg << '\n' << oldSortMsg << '\n' << hotSortMsg << '\n' << coldSortMsg << '\n';
    SortType choice = static_cast<SortType>(Controller::GetValidNumber());
    switch (choice)
    {
    case SortType::earliest:
        {
            CalculateData(ByTimeDescending());
            break; 
        }
    case SortType::oldest:
        {
            //already sorted by this.
            CalculateData(*dataCollection);
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
    std::cout << findTemperatureMsg << '\n';
    float accuarcy = static_cast<float>(Controller::GetValidNumber());
    float valueToFind = static_cast<float>(Controller::GetValidNumber());
    bool found = false;
    for (const auto& pair : *dataCollection) {

        if (std::abs(pair.second - valueToFind) < accuarcy )
        {
            found = true;
            std::tm localTime;
            localtime_s(&localTime, &pair.first);
            std::cout << "Found value at date: " <<std::put_time(&localTime, formatArg) << " with the temp: " <<pair.second << '\n';
        }
    }
    if (!found)
    {
        std::cout << cantFindMsg << '\n';
    }
}

void DataAnalyser::LookupDate()
{
    std::cout << findDateMsg << '\n';
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
            std::tm localTime;
            localtime_s(&localTime, &pair.first);
            std::cout <<"This data was found at the date: " << std::put_time(&localTime, formatArg) 
                      << " Value: " << pair.second << '\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No data found for this date" << '\n';
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
