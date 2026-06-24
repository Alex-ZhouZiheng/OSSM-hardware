#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace controller_position_logic {

inline float clampPercent(float value) {
    return std::max(0.0f, std::min(100.0f, value));
}

inline int clampDepthForPosition(float depthPct, float positionPct) {
    float position = clampPercent(positionPct);
    float maxDepth = 100.0f - position;
    return static_cast<int>(std::lround(std::min(clampPercent(depthPct), maxDepth)));
}

inline int clampPositionForDepth(float positionPct, float depthPct) {
    float depth = clampPercent(depthPct);
    float maxPosition = 100.0f - depth;
    return static_cast<int>(std::lround(std::min(clampPercent(positionPct), maxPosition)));
}

inline int deepFromWindow(float positionPct, float depthPct) {
    int position = clampPositionForDepth(positionPct, depthPct);
    int depth = clampDepthForPosition(depthPct, position);
    return position + depth;
}

inline int positionFromWindowSettings(float firmwareDepthPct, float strokePct) {
    float firmwareDepth = clampPercent(firmwareDepthPct);
    float stroke = clampPercent(strokePct);
    return static_cast<int>(std::lround(clampPercent(firmwareDepth - stroke)));
}

}  // namespace controller_position_logic
