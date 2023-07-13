#include "xbox_math_quaternion.h"

#include <cassert>

#include "xbox_math_matrix.h"

#define DEG2RAD(c) ((float)(c) * (float)M_PI / 180.0f)

namespace XboxMath {

CQuaternion::CQuaternion() : x(0), y(0), z(0), w(1) {}

CQuaternion::CQuaternion(float xI, float yI, float zI, float wI)
    : x(xI), y(yI), z(zI), w(wI) {}

CQuaternion::CQuaternion(const vector_t &axis, float angle) {
  float d = VectorLength(axis);
  float s = sinf(DEG2RAD(angle) * 0.5f) / d;

  SetValues(axis[0] * s, axis[1] * s, axis[2] * s, cosf(DEG2RAD(angle) * 0.5f));
}

CQuaternion::CQuaternion(float yaw, float pitch, float roll) {
  SetEuler(yaw, pitch, roll);
}

CQuaternion &CQuaternion::operator*=(const CQuaternion &q) {
  CQuaternion temp = *this * q;
  *this = temp;
  return *this;
}

CQuaternion &CQuaternion::operator*=(float s) {
  SetValues(x * s, y * s, z * s, w * s);
  return *this;
}

CQuaternion &CQuaternion::operator+=(const CQuaternion &q) {
  SetValues(x + q.x, y + q.y, z + q.z, w + q.w);
  return *this;
}

CQuaternion &CQuaternion::operator-=(const CQuaternion &q) {
  SetValues(x - q.x, y - q.y, z - q.z, w - q.w);
  return *this;
}

float &CQuaternion::operator[](uint32_t idx) {
  switch (idx) {
    case 0:
      return x;

    case 1:
      return y;

    case 2:
      return z;

    case 3:
      return w;

    default:
      assert(false && "Index out of bounds");
  }

  return w;
}

float CQuaternion::operator[](uint32_t idx) const {
  switch (idx) {
    case 0:
      return x;

    case 1:
      return y;

    case 2:
      return z;

    case 3:
      return w;

    default:
      assert(false && "Index out of bounds");
  }

  return 0.0f;
}

CQuaternion operator-(const CQuaternion &a) { return {-a.x, -a.y, -a.z, -a.w}; }

CQuaternion operator+(const CQuaternion &a, const CQuaternion &b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

CQuaternion operator*(const CQuaternion &a, float s) {
  return {a.x * s, a.y * s, a.z * s, a.w * s};
}

CQuaternion operator*(float s, const CQuaternion &a) {
  return {a.x * s, a.y * s, a.z * s, a.w * s};
}

CQuaternion operator*(const CQuaternion &a, const CQuaternion &b) {
  return {a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
          a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
          a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
          a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}

CQuaternion &CQuaternion::SetValues(float xI, float yI, float zI, float wI) {
  x = xI;
  y = yI;
  z = zI;
  w = wI;
  return *this;
}

CQuaternion &CQuaternion::SetEuler(float yaw, float pitch, float roll) {
  float cosY = 1.0f, sinY = 0.0f, cosP = 1.0f, sinP = 0.0f, cosR = 1.0f,
        sinR = 0.0f;
  float yRad = DEG2RAD(yaw) / 2.0f;
  float pRad = DEG2RAD(pitch) / 2.0f;
  float rRad = DEG2RAD(roll) / 2.0f;

  if (yRad != 0.0f) {
    cosY = cosf(yRad);
    sinY = sinf(yRad);
  }

  if (pRad != 0.0f) {
    cosP = cosf(pRad);
    sinP = sinf(pRad);
  }

  if (rRad != 0.0f) {
    cosR = cosf(rRad);
    sinR = sinf(rRad);
  }

  SetValues(cosR * sinP * cosY + sinR * cosP * sinY,
            cosR * cosP * sinY - sinR * sinP * cosY,
            sinR * cosP * cosY - cosR * sinP * sinY,
            cosR * cosP * cosY + sinR * sinP * sinY);

  return *this;
}

void CQuaternion::GetMatrix(matrix4_t &ret) const {
  MatrixSetRowVector(ret, 1.0f - 2.0f * (y * y) - 2.0f * (z * z),
                     2.0f * (x * y + w * z), 2.0f * (x * z - w * y), 0, 0);

  MatrixSetRowVector(ret, 2.0f * (x * y - w * z),
                     1.0f - 2.0f * (x * x) - 2.0f * (z * z),
                     2.0f * (y * z + w * x), 0, 1);

  MatrixSetRowVector(ret, 2.0f * (x * z + w * y), 2.0f * (y * z - w * x),
                     1.0f - 2.0f * (x * x) - 2.0f * (y * y), 0, 2);

  MatrixSetRowVector(ret, 0, 0, 0, 1, 3);
}

}  // namespace XboxMath
