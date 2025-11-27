#include "contracts.h"
#include <math.h>

float sin_integral(float a, float b, float e) {
  float sum = 0.0;
  for (float x = a; x < b; x += e) {
    sum += sinf(x + e / 2) * e;
  }

  return sum;
}

float pi(int k) {
  float sum = 0.0;
  for (int i = 0; i < k; ++i) {
    float term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    sum += term;
  }

  return 4 * sum;
}
