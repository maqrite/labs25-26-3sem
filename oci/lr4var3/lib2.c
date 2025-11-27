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

int gcd(int a, int b) {
  int min_val = (a < b) ? a : b;

  for (int i = min_val; i > 0; i--) {
    if (a % i == 0 && b % i == 0) {
      return i;
    }
  }

  return 1;
}
