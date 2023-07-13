#ifndef XBOX_MATH_VECTOR_H_
#define XBOX_MATH_VECTOR_H_

#include <cmath>
#include <cstring>

#include "xbox_math_types.h"

namespace XboxMath {

inline void VectorIdentity(vector_t &v) {
  v[0] = 0.0f;
  v[1] = 0.0f;
  v[2] = 0.0f;
  v[3] = 1.0f;
}

void VectorNormalize(const vector_t &v, vector_t &ret);
void VectorNormalize(vector_t &v);

void VectorAddVector(const vector_t &a, const vector_t &b, vector_t &sum);
inline void VectorAddVector(vector_t &plusEquals, const vector_t &b) {
  plusEquals[0] += b[0];
  plusEquals[1] += b[1];
  plusEquals[2] += b[2];
}

void VectorSubtractVector(const vector_t &a, const vector_t &b, vector_t &sum);
inline void VectorSubtractVector(vector_t &minusEquals, const vector_t &b) {
  minusEquals[0] -= b[0];
  minusEquals[1] -= b[1];
  minusEquals[2] -= b[2];
}

void ScalarMultVector(const vector_t &a, float scalar, vector_t &ret);
void ScalarMultVector(vector_t &a, float scalar);

void VectorDotVector(const vector_t &a, const vector_t &b, float &sum);
inline float VectorDotVector(const vector_t &a, const vector_t &b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void VectorLength(const vector_t &a, float &len);
inline float VectorLength(const vector_t &v) {
  return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void VectorCrossVector(const vector_t &a, const vector_t &b, vector_t &sum);
void VectorCrossVector(vector_t &a, const vector_t &b);

inline void VectorCopyVector(vector_t &dest, const vector_t &a) {
  memcpy(&dest, &a, sizeof(dest));
}

inline void VectorSetVector(vector_t &dest, float x, float y, float z,
                            float w = 1.0f) {
  dest[0] = x;
  dest[1] = y;
  dest[2] = z;
  dest[3] = w;
}

inline void VectorEuclidean(const vector_t &v, vector_t &result) {
  if (v[3] == INFINITY) {
    result[0] = INFINITY;
    result[1] = INFINITY;
    result[2] = INFINITY;
    result[3] = 1.f;
  } else {
    result[0] = v[0] / v[3];
    result[1] = v[1] / v[3];
    result[2] = v[2] / v[3];
    result[3] = 1.f;
  }
}

}  // namespace XboxMath

#endif  // XBOX_MATH_VECTOR_H_
