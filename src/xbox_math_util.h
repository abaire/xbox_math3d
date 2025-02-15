#ifndef XBOX_MATH_UTIL_H
#define XBOX_MATH_UTIL_H

#include "xbox_math_types.h"

namespace XboxMath {

//! Creates a model-view + projection matrix.
void BuildCompositeMatrix(const matrix4_t &model_view,
                          const matrix4_t &projection, matrix4_t &result);

//! Inverts the given composite matrix.
void BuildInverseCompositeMatrix(const matrix4_t &composite_matrix,
                                 matrix4_t &result);

//! Projects the given point into screen space using the given composite matrix.
void ProjectPoint(const vector_t &world_point,
                  const matrix4_t &composite_matrix, vector_t &result);

//! Unprojects the given screen point into world space using the given inverse
//! composite matrix.
void UnprojectPoint(const vector_t &screen_point,
                    const matrix4_t &inverse_composite_matrix,
                    vector_t &result);

//! Unprojects the given screen point into world space, finding the world point
//! at the given Z value using the given
// inverse composite matrix.
void UnprojectPoint(const vector_t &screen_point,
                    const matrix4_t &inverse_composite_matrix, float world_z,
                    vector_t &result);

}  // namespace XboxMath

#endif  // XBOX_MATH_UTIL_H
