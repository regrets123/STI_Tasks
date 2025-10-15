#pragma once
#include <map>

class DataCollector
{
    
public:

    DataCollector (std::shared_ptr<std::map<time_t ,float>> collection) : dataCollection(collection)
    {
        
    }
    std::shared_ptr<std::map<time_t ,float>> dataCollection;
    void Initialize();
    void AddData();
    void GetManualTime(int iterations);
    void GetAutoTime(int iterations);
    void GenerateRandomData();
    std::shared_ptr<std::map<time_t ,float>> GetData() {return dataCollection;}
    
private:
    const char* amountMsg = "Enter the amount of data pairs of time <-> value you want to input:";
    const char* valueMsg = "Enter value number:";
    const char* pairMsg = "Enter time <-> value pair number:";
    const char* genDataMsg = "Generating random Dataset, insert size of Dataset: ";
    const char* currentTimeMsg = "Enter 0 to use currentTime:";
    const char* manualTimeMsg =  "Enter 1 to input time manually after Jan 1 1970 UTC:";

};
