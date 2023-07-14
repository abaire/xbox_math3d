#ifndef XBOX_MATH_TYPES_H_
#define XBOX_MATH_TYPES_H_

#include <cmath>

#if (__cplusplus >= 201103L)
#include <cstdint>
#else
typedef unsigned long uint32_t;
#endif

namespace XboxMath {

typedef float vector_t[4];
typedef float vertex_t[4];

typedef float texcoord_t[3];

typedef float matrix3_t[3][3];
typedef float matrix4_t[4][4];

typedef struct boundingsphere_t {
  vector_t m_centerPt;  // Center point of the prism
  float m_radius;
} boundingsphere_t;

inline float PointDistancePoint(const vertex_t &a, const vertex_t &b) {
  return (float)sqrt(pow(b[0] - a[0], 2.0f) + pow(b[1] - a[1], 2.0f) +
                     pow(b[2] - a[2], 2.0f));
}

void PlaneFindNormal(const vertex_t &a, const vertex_t &b, const vertex_t &c,
                     vector_t &normal);

void PlaneFindNormalizedNormal(const vertex_t &a, const vertex_t &b,
                               const vertex_t &c, vector_t &normal);

}  // namespace XboxMath

#endif  // XBOX_MATH_TYPES_H_
