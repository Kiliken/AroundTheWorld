#pragma once
#include <cmath>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>
#include "Grad.h"

class Noise {
private:
    std::vector<int> perm;
    std::vector<std::shared_ptr<Grad>> gradP;
    std::vector<std::shared_ptr<Grad>> grad3;
    std::vector<int> p;

public:
    Noise();
    ~Noise();

    void seed(int seed);
    float perlin2(float x, float y);

private:
    float fade(float t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    float lerp(float a, float b, float t) const {
        return a + t * (b - a);
    }
};