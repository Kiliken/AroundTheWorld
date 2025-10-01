#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <numeric>
#include <string>
#include <cmath>
#include "Noise.h"
#include "TerrainType.h"

#define ASSETS(file) ("../assets/"##file)

#define F2() (0.5 * (sqrt(3) - 1))
#define G2() ((3 - sqrt(3)) / 6)
#define F3() (1 / 3)
#define G3() (1 / 6)

namespace utils
{

    std::vector<std::vector<float>> generateNoiseMap(
        int mapWidth, int mapHeight,
        Noise &noise, float scale,
        int octaves, float persistence,
        float lacunarity, float offY,float offX)
    {
        std::vector<std::vector<float>> noiseMap(mapWidth, std::vector<float>(mapHeight, 0.0f));
        std::vector<std::pair<float, float>> octaveOffsets;

        for (int i = 0; i < octaves; ++i)
        {
            float offsetX = offX;
            float offsetY = offY;
            octaveOffsets.emplace_back(offsetX, offsetY);
        }

        if (scale <= 0.0f)
            scale = 0.0001f;

        float maxNoiseHeight = -INFINITY;
        float minNoiseHeight = INFINITY;

        float halfWidth = mapWidth / 2.0f;
        float halfHeight = mapHeight / 2.0f;

        for (int y = 0; y < mapHeight; ++y)
        {
            for (int x = 0; x < mapWidth; ++x)
            {
                float amplitude = 1.0f;
                float frequency = 1.0f;
                float noiseHeight = 0.0f;

                for (int i = 0; i < octaves; ++i)
                {
                    float sampleX = (x - halfWidth) / scale * frequency + octaveOffsets[i].first * frequency;
                    float sampleY = (y - halfHeight) / scale * frequency - octaveOffsets[i].second * frequency;

                    float perlinValue = noise.perlin2(sampleX, sampleY) * 2.0f - 1.0f;
                    noiseHeight += perlinValue * amplitude;

                    amplitude *= persistence;
                    frequency *= lacunarity;
                }

                maxNoiseHeight = std::max(maxNoiseHeight, noiseHeight);
                minNoiseHeight = std::min(minNoiseHeight, noiseHeight);

                noiseMap[x][y] = noiseHeight;
            }
        }

        // Normalize
        for (int y = 0; y < mapHeight; ++y)
        {
            for (int x = 0; x < mapWidth; ++x)
            {
                noiseMap[x][y] = std::clamp((noiseMap[x][y] - minNoiseHeight) / (maxNoiseHeight - minNoiseHeight), 0.0f, 1.0f);
            }
        }

        return noiseMap;
    }

    std::array<int, 3> lerpColor(const std::array<int, 3> &colorA,
                                 const std::array<int, 3> &colorB,
                                 float t)
    {
        return {
            static_cast<int>(colorA[0] + (colorB[0] - colorA[0]) * t),
            static_cast<int>(colorA[1] + (colorB[1] - colorA[1]) * t),
            static_cast<int>(colorA[2] + (colorB[2] - colorA[2]) * t)};
    }

    float normalize(float value, float max, float min)
    {
        if (value > max)
            return 1.0f;
        if (value < min)
            return 0.0f;
        return (value - min) / (max - min);
    }

    std::array<int, 3> getTerrainColor(float noiseValue, const TerrainType &terrain)
    {
        float normalized = normalize(noiseValue, terrain.maxHeight, terrain.minHeight);
        float t = std::clamp(normalized + terrain.lerpAdjustment, 0.0f, 1.0f);
        return lerpColor(terrain.minColor, terrain.maxColor, t);
    }

}
