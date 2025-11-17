
#include "Threshold.h"

bool Threshold::IsThresholdTriggered(float value) {
    if (isBelow) {
        return value < threshold;
    }
    else {
        return value > threshold;
    }
}
