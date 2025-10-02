#include "Assignment_1/Controller.h"

int main(int argc, char* argv[])
{
    auto dataCollector = new DataCollector();
    auto dataAnalyser = new DataAnalyser();

    auto controller = new Controller(true, dataCollector, dataAnalyser);
    controller->Run();
}
