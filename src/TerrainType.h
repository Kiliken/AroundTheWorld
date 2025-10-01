#pragma once
#include <array>

class TerrainType {
public:
    float minHeight;
    float maxHeight;
    std::array<int, 3> minColor;
    std::array<int, 3> maxColor;
    float lerpAdjustment;

    TerrainType(float minH, float maxH,
                std::array<int, 3> minC,
                std::array<int, 3> maxC,
                float lerpAdj = 0.0f)
        : minHeight(minH), maxHeight(maxH),
          minColor(minC), maxColor(maxC),
          lerpAdjustment(lerpAdj) {}
};