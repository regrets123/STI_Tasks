
#include "Threshold.h"

void Threshold::ToggleAlarm(bool isOn) {
    isActive = isOn;
}

bool Threshold::IsThresholdTriggered(double value) const {
    if (isBelow) {
        return value < threshold;
    }
    else {
        return value > threshold;
    }
}
