#ifndef XBOX_MATH_QUATERNION_H_
#define XBOX_MATH_QUATERNION_H_

#include <cmath>

#include "xbox_math_types.h"

#define SLERP_ERROR_TOLERANCE 1e-6

namespace XboxMath {

class CQuaternion {
 public:
  CQuaternion();
  CQuaternion(const CQuaternion &q) = default;
  CQuaternion(float xI, float yI, float zI, float wI);
  CQuaternion(const vector_t &axis, float angle);
  CQuaternion(float yaw, float pitch, float roll);

  CQuaternion &operator*=(const CQuaternion &q);
  CQuaternion &operator*=(float s);
  CQuaternion &operator+=(const CQuaternion &q);
  CQuaternion &operator-=(const CQuaternion &q);
  float &operator[](uint32_t idx);
  float operator[](uint32_t idx) const;

  friend CQuaternion operator-(const CQuaternion &a);
  friend CQuaternion operator+(const CQuaternion &a, const CQuaternion &b);
  friend CQuaternion operator*(const CQuaternion &a, float s);
  friend CQuaternion operator*(float s, const CQuaternion &a);
  friend CQuaternion operator*(const CQuaternion &a, const CQuaternion &b);

  CQuaternion &SetValues(float xI, float yI, float zI, float wI);

  CQuaternion &SetEuler(float yaw = 0.0f, float pitch = 0.0f,
                        float roll = 0.0f);

  CQuaternion &Normalize() { return *this *= (1.0f / GetLength()); }

  [[nodiscard]] float GetLength() const {
    return sqrtf(w * w + x * x + y * y + z * z);
  }

  void GetMatrix(matrix4_t &ret) const;

 protected:
  float x, y, z, w;
};

typedef CQuaternion quaternion_t;

inline float QuaternionDotQuaternion(const CQuaternion &a,
                                     const CQuaternion &b) {
  return ((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]));
}

inline CQuaternion Slerp(const CQuaternion &from, const CQuaternion &to,
                         float interp) {
  float omega, cosO, sinO;
  float scale0, scale1;

  cosO = QuaternionDotQuaternion(from, to);

  if (cosO < 0.0) cosO = -cosO;

  if ((1.0 - cosO) > SLERP_ERROR_TOLERANCE) {
    omega = (float)acos(cosO);
    sinO = sinf(omega);
    scale0 = sinf((1.0F - interp) * omega) / sinO;
    scale1 = sinf(interp * omega) / sinO;
  } else {
    scale0 = 1.0f - interp;
    scale1 = interp;
  }

  return (scale0 * from) + (scale1 * -to);
}

}  // namespace XboxMath

#endif  // XBOX_MATH_QUATERNION_H_
