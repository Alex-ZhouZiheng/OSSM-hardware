#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace controller_position_logic {

inline float clampPercent(float value) {
    return std::max(0.0f, std::min(100.0f, value));
}

inline int depthFromPosition(float positionPct, float strokePct) {
    float stroke = clampPercent(strokePct);
    float position = clampPercent(positionPct);
    float travel = 100.0f - stroke;
    return static_cast<int>(std::lround(stroke + (position * travel / 100.0f)));
}

inline int positionFromDepth(float depthPct, float strokePct) {
    float stroke = clampPercent(strokePct);
    float depth = clampPercent(depthPct);
    float travel = 100.0f - stroke;

    if (travel <= 0.0f || depth <= stroke) {
        return 0;
    }

    return static_cast<int>(
        std::lround(clampPercent((depth - stroke) * 100.0f / travel)));
}

}  // namespace controller_position_logic
