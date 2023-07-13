#include "xbox_math_types.h"

#include "xbox_math_vector.h"

namespace XboxMath {

inline void TexcoordSetTexcoord(texcoord_t &tex, float u, float v,
                                float w = 1.0f) {
  tex[0] = u;
  tex[1] = v;
  tex[2] = w;
}

void PlaneFindNormal(const vertex_t &a, const vertex_t &b, const vertex_t &c,
                     vector_t &normal) {
  vector_t ab = {a[0] - b[0], a[1] - b[1], a[2] - b[2], 1.0f};
  vector_t bc = {b[0] - c[0], b[1] - c[1], b[2] - c[2], 1.0f};
  VectorCrossVector(ab, bc, normal);
  normal[3] = 1.0f;
}

void PlaneFindNormalizedNormal(const vertex_t &a, const vertex_t &b,
                               const vertex_t &c, vector_t &normal) {
  PlaneFindNormal(a, b, c, normal);
  VectorNormalize(normal);
}

}  // namespace XboxMath
