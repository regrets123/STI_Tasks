#pragma once
#include <array>
#include <string>
#include <unordered_map>

class DataCollector
{
    
public:

    DataCollector (std::shared_ptr<std::unordered_map<time_t ,float>> collection) : dataCollection(collection)
    {
        
    }
    std::shared_ptr<std::unordered_map<time_t ,float>> dataCollection;
    void Initialize();
    void AddData();
    void GetManualTime(int iterations);
    void GetAutoTime(int iterations);
    void GenerateRandomData();
    std::shared_ptr<std::unordered_map<time_t ,float>> GetData() {return dataCollection;}
    
private:
    std::array<std::string,4> prompts {"Enter the amount of data pairs of time <-> value you want to input:", "Enter value number:","Enter time <-> value pair number:","Generating random Dataset, insert size of Dataset: "};
    std::array<std::string,2> timeChoices {"Enter 0 to use currentTime:", "Enter 1 to input time manually as an integer counting number of seconds since 00:00, Jan 1 1970 UTC:"};

};
