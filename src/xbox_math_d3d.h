#ifndef XBOX_MATH_TESTS_SRC_XBOX_MATH_D3D_H_
#define XBOX_MATH_TESTS_SRC_XBOX_MATH_D3D_H_

#include "xbox_math_types.h"

namespace XboxMath {

void CreateD3DLookAtLH(matrix4_t &ret, const vector_t &eye, const vector_t &at,
                       const vector_t &up);

void CreateD3DPerspectiveFOVLH(matrix4_t &ret, float fov_y, float aspect,
                               float z_near, float z_far);

void CreateD3DViewport(matrix4_t &ret, float width, float height,
                       float max_depthbuffer_value, float z_min, float z_max);

void CreateD3DStandardViewport16Bit(matrix4_t &ret, float width, float height);

void CreateD3DStandardViewport16BitFloat(matrix4_t &ret, float width,
                                         float height);

void CreateD3DStandardViewport24Bit(matrix4_t &ret, float width, float height);

void CreateD3DStandardViewport24BitFloat(matrix4_t &ret, float width,
                                         float height);

}  // namespace XboxMath

#endif  // XBOX_MATH_TESTS_SRC_XBOX_MATH_D3D_H_
