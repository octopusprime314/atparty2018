#include "Noise.h"

#include <cmath>

template <typename T>
T lerp(T t, T lo, T hi)
{
    return t*lo + (1 - t)*hi;
}

template <typename T>
T bilerp(T t0, T t1, T q00, T q01, T q10, T q11)
{
    T r0 = lerp(t0, q00, q10);
    T r1 = lerp(t0, q01, q11);
    return lerp(t1, r0, r1);
}

template <typename T>
T PowerOfTwo(uint8_t power)
{
    uint64_t res = 1;
    return static_cast<T>(res << power);
}

// Return a random float in [0, 1] which changes smoothly in x and y.
// Effectively 'Value Noise'.
float ValueNoise2D::noise(float x, float y) {
    uint32_t w = 128;
    uint32_t h = 128;

    float pls_just_null_check = 0;

    float    xf = modf(x, &pls_just_null_check);
    uint32_t x1 = (uint32_t(x) + w) % w;
    uint32_t x2 = (x1 + w - 1) % w;

    float    yf = modf(y, &pls_just_null_check);
    uint32_t y1 = (uint32_t(y) + h) % h;
    uint32_t y2 = (y1 + h - 1) % h;

    return bilerp(xf, yf,
                  data[x1][y1],
                  data[x1][y2],
                  data[x2][y1],
                  data[x2][y2]);
}

float ValueNoise2D::turbulence(float x, float y, uint8_t octaves) {
    float val = 0.f;
    for (auto w = PowerOfTwo<uint64_t>(octaves); w >= 1; w /=2) {
        val += w * noise(x/w, y/w);
    }
    val /= PowerOfTwo<float>(octaves + 1);

    return val;
}

// This noise data matches the original data from its Python roots.
// The goal is to replicate the maps verbatim, at least for testing.
#include "NoiseData.h"
ValueNoise2D kNoise(kValueNoise2DPythonData);