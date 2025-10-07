#include "Assignment_1/Controller.h"

int main(int argc, char* argv[])
{
    std::unique_ptr<DataCollector> dataCollector = std::make_unique<DataCollector>();
    std::unique_ptr<std::unordered_map<time_t,float>> data = std::make_unique<std::unordered_map<time_t,float>>();
    std::unique_ptr<DataAnalyser>  analyser = std::make_unique<DataAnalyser>(std::move(data));
    auto controller = new Controller(std::move(analyser), std::move(dataCollector));
    controller->Run();
}
