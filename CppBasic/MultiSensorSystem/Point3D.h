#pragma once

#include <cmath>

struct Point3D {
    double x, y, z;

    // Constructors
    Point3D() : x(0), y(0), z(0) {}
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

    Point3D operator+(const Point3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Point3D operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    [[nodiscard]] double length() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    [[nodiscard]] Point3D normalized() const {
        double len = length();
        if (len > 0) {
            return {x / len, y / len, z / len};
        }
        return *this;  // Return unchanged if length is 0
    }
};