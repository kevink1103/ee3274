#include "vector.h"


EEProj::Vector<2> LeastSquareMethod(const int *Arr, const uint8_t len)
{ // Output: y = ax + b; a is slope, b is y-intersept.
  double a, b;
  double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
  for (int x = 0; x < len; x++)   {
    t1 += (x + 1) * (x + 1);
    t2 += (x + 1);
    t3 += (x + 1) * Arr[x];
    t4 += Arr[x];
  }
  a = (t3 * len - t2 * t4) / (t1 * len - t2 * t2);
  b = (t1 * t4 - t2 * t3) / (t1 * len - t2 * t2);
  return EEProj::Vector<2>(a, b);
}