#pragma once
class Threshold {

public:
    bool IsThresholdTriggered(float value);
private:
    float threshold = 0;
    bool isBelow = false;
};
