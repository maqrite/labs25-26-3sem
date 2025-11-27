#include "contracts.h"
#include <math.h>

float sin_integral(float a, float b, float e) {
  float sum = 0.0;
  sum += sinf(a) / 2;
  sum += sinf(b) / 2;

  for (float x = a + e; x < b; x += e) {
    sum += sinf(x);
  }

  return sum * e;
}

float pi(int k) {
  float product = 1.0;

  for (int i = 1; i <= k; ++i) {
    float num = 4.0 * i * i;
    float den = 4.0 * i * i - 1;
    product *= (num / den);
  }

  return 2 * product;
}
