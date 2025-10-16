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
        float lacunarity, float offY,float offX);

    std::array<int, 3> lerpColor(const std::array<int, 3> &colorA,
                                 const std::array<int, 3> &colorB,
                                 float t);

    float normalize(float value, float max, float min);

    std::array<int, 3> getTerrainColor(float noiseValue, const TerrainType &terrain);

}
