#include "xbox_math_d3d.h"

#include "xbox_math_matrix.h"
#include "xbox_math_vector.h"

namespace XboxMath {

void CreateD3DLookAtLH(matrix4_t &ret, const vector_t &eye, const vector_t &at,
                       const vector_t &up) {
  // https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxmatrix4_tlookatlh
  vector_t z_axis{0.f, 0.f, 0.f, 1.f};
  VectorSubtractVector(at, eye, z_axis);
  VectorNormalize(z_axis);

  vector_t x_axis{0.f, 0.f, 0.f, 1.f};
  VectorCrossVector(up, z_axis, x_axis);
  VectorNormalize(x_axis);

  vector_t y_axis{0.f, 0.f, 0.f, 1.f};
  VectorCrossVector(z_axis, x_axis, y_axis);
  VectorNormalize(y_axis);

  ret[0][0] = x_axis[0];
  ret[0][1] = y_axis[0];
  ret[0][2] = z_axis[0];
  ret[0][3] = 0.f;

  ret[1][0] = x_axis[1];
  ret[1][1] = y_axis[1];
  ret[1][2] = z_axis[1];
  ret[1][3] = 0.f;

  ret[2][0] = x_axis[2];
  ret[2][1] = y_axis[2];
  ret[2][2] = z_axis[2];
  ret[2][3] = 0.f;

  ret[3][0] = -1.f * VectorDotVector(x_axis, eye);
  ret[3][1] = -1.f * VectorDotVector(y_axis, eye);
  ret[3][2] = -1.f * VectorDotVector(z_axis, eye);
  ret[3][3] = 1.f;
}

void CreateD3DPerspectiveFOVLH(matrix4_t &ret, float fov1, float aspect,
                               float z_near, float z_far) {
  float y_scale = 1.0f / tanf(fov1 * 0.5f);
  float x_scale = y_scale / aspect;

  float z_adjustment = z_far / (z_far - z_near);

  MatrixSetIdentity(ret);
  ret[0][0] = x_scale;
  ret[1][1] = y_scale;
  ret[2][2] = z_adjustment;
  ret[2][3] = 1.f;
  ret[3][2] = -1.f * z_near * z_adjustment;
  ret[3][3] = 0.f;
}

void CreateD3DViewport(matrix4_t &ret, float width, float height,
                       float max_depthbuffer_value, float z_min, float z_max) {
  MatrixSetIdentity(ret);

  ret[0][0] = width * 0.5f;
  ret[3][0] = ret[0][0];
  ret[3][1] = height * 0.5f;
  ret[1][1] = -1.0f * ret[3][1];
  ret[2][2] = max_depthbuffer_value * (z_max - z_min);
  ret[3][2] = max_depthbuffer_value * z_min;
}

void CreateD3DStandardViewport16Bit(matrix4_t &ret, float width, float height) {
  CreateD3DViewport(ret, width, height, (float)0xFFFF, 0.0f, 1.0f);
}

void CreateD3DStandardViewport16BitFloat(matrix4_t &ret, float width,
                                         float height) {
  constexpr uint32_t max_value_int = 0x43FFF800;
  float max_value = *(float *)&max_value_int;
  CreateD3DViewport(ret, width, height, (float)max_value, 0.0f, 1.0f);
}

void CreateD3DStandardViewport24Bit(matrix4_t &ret, float width, float height) {
  CreateD3DViewport(ret, width, height, (float)0x00FFFFFF, 0.0f, 1.0f);
}

void CreateD3DStandardViewport24BitFloat(matrix4_t &ret, float width,
                                         float height) {
  constexpr uint32_t max_value_int = 0x7149F2CA;
  float max_value = *(float *)&max_value_int;
  CreateD3DViewport(ret, width, height, max_value, 0.0f, 1.0f);
}

}  // namespace XboxMath
