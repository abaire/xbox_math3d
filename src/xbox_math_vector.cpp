#include "xbox_math_vector.h"

#include <cassert>

namespace XboxMath {

void VectorNormalize(vector_t &v) {
  float inv_length = 1.f / VectorLength(v);
  v[0] *= inv_length;
  v[1] *= inv_length;
  v[2] *= inv_length;
}

void VectorNormalize(const vector_t &v, vector_t &ret) {
  float inv_length = 1.f / VectorLength(v);
  ret[0] = v[0] * inv_length;
  ret[1] = v[1] * inv_length;
  ret[2] = v[2] * inv_length;
}

void VectorAddVector(const vector_t &a, const vector_t &b, vector_t &sum) {
  assert(a[3] == 1.f);
  assert(b[3] == 1.f);
  sum[0] = a[0] + b[0];
  sum[1] = a[1] + b[1];
  sum[2] = a[2] + b[2];
}

void VectorSubtractVector(const vector_t &a, const vector_t &b, vector_t &sum) {
  assert(a[3] == 1.f);
  assert(b[3] == 1.f);
  sum[0] = a[0] - b[0];
  sum[1] = a[1] - b[1];
  sum[2] = a[2] - b[2];
}

void ScalarMultVector(const vector_t &a, float scalar, vector_t &ret) {
  ret[0] = scalar * a[0];
  ret[1] = scalar * a[1];
  ret[2] = scalar * a[2];
}

void ScalarMultVector(vector_t &a, float scalar) {
  a[0] *= scalar;
  a[1] *= scalar;
  a[2] *= scalar;
}

void VectorDotVector(const vector_t &a, const vector_t &b, float &sum) {
  sum = VectorDotVector(a, b);
}

void VectorLength(const vector_t &a, float &len) { len = VectorLength(a); }

void VectorCrossVector(const vector_t &a, const vector_t &b, vector_t &sum) {
  sum[0] = a[1] * b[2] - a[2] * b[1];
  sum[1] = a[2] * b[0] - a[0] * b[2];
  sum[2] = a[0] * b[1] - a[1] * b[0];
}

void VectorCrossVector(vector_t &a, const vector_t &b) {
  vector_t sum;
  VectorCrossVector(a, b, sum);
  a[0] = sum[0];
  a[1] = sum[1];
  a[2] = sum[2];
}

}  // namespace XboxMath
