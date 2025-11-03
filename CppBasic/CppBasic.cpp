#include "UserInterface.h"
#include "Storage.h"
#include <vector>
#include <memory>

int main() {
    Storage storage;
    std::vector<std::shared_ptr<Sensor>> sensors;
    //sensors.push_back(std::make_shared<Sensor>(...));

    UserInterface ui(sensors, storage);
    ui.run();
    return 0;
}