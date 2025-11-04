
#ifndef STI_TASKS_UTILS_H
#define STI_TASKS_UTILS_H
#include <string>
#include <vector>

class Utils {
public:
    static float calculateMean(const std::vector<float>& values);
    static float calculateStdDev(const std::vector<float>& values, float mean);
    static int getValidInput(int min, int max);
    static std::string sensorTypeToString(int type);
    static int stringToSensorType(const std::string& typeStr);
    static std::string getUnitString(int type);
    static void clearInputBuffer();
};


#endif //STI_TASKS_UTILS_H