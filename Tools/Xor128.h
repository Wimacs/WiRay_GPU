#pragma once

#include <Tracer/Utils/RandomGenerator.h>

class Xor128 : public RandomGenerator
{
  public:
    unsigned int RandomUint() override
    {
        unsigned int t;
        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
    }

  private:
    unsigned int x = 123456789;
    unsigned int y = 362436069;
    unsigned int z = 521288629;
    unsigned int w = 88675123;
};