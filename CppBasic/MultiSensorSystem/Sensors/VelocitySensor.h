#include "Sensor.h"
#include "Measurement.h"
#include "Point3D.h"
#include <chrono>
#include <random>

class VelocitySensor final : public Sensor {
public:
    VelocitySensor(const Point3D& direction, const Point3D& startPosition,
                   float minSpeed, float maxSpeed, const std::string& name, Threshold threshold);

    double read() const override;
    Point3D getMoreData() const override;

private:
    Point3D direction;
    Point3D startPosition;
    mutable double currentSpeed;  // Current speed (mutable for updating in const methods)
    mutable Point3D currentPosition;
    mutable std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::time_point creationTime;

    void updateDistance() const;
};