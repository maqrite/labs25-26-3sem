#include "contracts.h"
#include <math.h>

float sin_integral(float a, float b, float e) {
  float sum = 0.0;
  for (float x = a; x < b; x += e) {
    sum += sinf(x + e / 2) * e;
  }

  return sum;
}

int gcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}
