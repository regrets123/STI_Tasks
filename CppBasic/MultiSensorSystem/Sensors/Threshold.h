#pragma once
class Threshold {

public:
    Threshold(double threshold, bool is_below)
        : threshold(threshold),
          isBelow(is_below) {
    }

    void ToggleAlarm(bool isOn);
    [[nodiscard]] bool IsThresholdTriggered(double value) const;

private:
    double threshold;
    bool isBelow;
    bool isActive = false;
};
