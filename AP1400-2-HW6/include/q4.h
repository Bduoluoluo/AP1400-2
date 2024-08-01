#ifndef Q4_H
#define Q4_H

#include <vector>
#include <algorithm>

namespace q4 {
    struct Vector2D {
        double x, y;
    };

    struct Sensor {
        Vector2D pos;
        double accuracy;
    };

    Vector2D kalman_filter(const std::vector<Sensor>& sensors);
}

inline q4::Vector2D q4::kalman_filter(const std::vector<q4::Sensor>& sensors) {
    double sumAcc = 0, X = 0, Y = 0;
    for (const auto& sensor : sensors)
        sumAcc += sensor.accuracy;
    for (const auto& sensor : sensors) {
        X += sensor.pos.x * sensor.accuracy / sumAcc;
        Y += sensor.pos.y * sensor.accuracy / sumAcc;
    }
    return q4::Vector2D{X, Y};
}

#endif //Q4_H