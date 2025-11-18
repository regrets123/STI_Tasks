
#include "Threshold.h"

void Threshold::ToggleAlarm(bool isOn) {
    isActive = isOn;
}

bool Threshold::isThresholdTriggered(double value) {
    if (!isActive) {
        return false;
    }
    if (isBelow && value < threshold) {
        savedValue = value;
        return true;
    }
    if (!isBelow && value > threshold) {
        savedValue = value;
        return true;
    }
    return false;
}
