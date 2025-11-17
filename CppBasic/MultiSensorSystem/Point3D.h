#pragma once

#include <cmath>
#include <sstream>
#include <iomanip>

struct Point3D {
    double x, y, z;

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
        return *this;
    }

    [[nodiscard]] std::string toString() const {
        if (x == 0 && y == 0 && z == 0) {
            return  "";
        }
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << " x:" << x << "; y:" << y << "; z:" << z;
        return ss.str();
    }

    [[nodiscard]] static Point3D fromString(const std::string& str) {
        Point3D point;
        std::stringstream ss(str);
        char semicolon;

        ss >> point.x >> semicolon >> point.y >> semicolon >> point.z;
        return point;
    }

    [[nodiscard]]Point3D operator-(const Point3D& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
};
