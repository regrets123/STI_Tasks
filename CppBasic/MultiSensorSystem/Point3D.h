#pragma once

#include <cmath>

struct Point3D {
    double x, y, z;
    Point3D operator+(const Point3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    [[nodiscard]] double length() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};

