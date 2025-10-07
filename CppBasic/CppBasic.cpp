#include "Assignment_1/Controller.h"

int main(int argc, char* argv[])
{
    auto data = std::make_shared<std::unordered_map<time_t, float>>();
    auto dataCollector = std::make_unique<DataCollector>(data);
    auto analyser = std::make_unique<DataAnalyser>(data);
    auto controller = std::make_unique<Controller>(std::move(analyser), std::move(dataCollector));
    controller->Run();
}
