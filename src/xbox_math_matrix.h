#ifndef XBOX_MATH_MATRIX_H_
#define XBOX_MATH_MATRIX_H_

#include "xbox_math_types.h"
#include "xbox_math_vector.h"

namespace XboxMath {

inline void VectorMultMatrix(vector_t &ret, const matrix4_t &a) {
  vector_t b;
  VectorCopyVector(b, ret);

  ret[0] = a[0][0] * b[0] + a[0][1] * b[1] + a[0][2] * b[2] + a[0][3] * b[3];
  ret[1] = a[1][0] * b[0] + a[1][1] * b[1] + a[1][2] * b[2] + a[1][3] * b[3];
  ret[2] = a[2][0] * b[0] + a[2][1] * b[1] + a[2][2] * b[2] + a[2][3] * b[3];
  ret[3] = a[3][0] * b[0] + a[3][1] * b[1] + a[3][2] * b[2] + a[3][3] * b[3];
}

inline void MatrixSetIdentity(matrix4_t &matrix) {
  matrix[0][1] = matrix[0][2] = matrix[0][3] = 0.0f;
  matrix[1][0] = matrix[1][2] = matrix[1][3] = 0.0f;
  matrix[2][0] = matrix[2][1] = matrix[2][3] = 0.0f;
  matrix[3][0] = matrix[3][2] = matrix[3][3] = 0.0f;
  matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1.0f;
}

inline void MatrixSetColumnVector(matrix4_t &matrix, const vector_t &v,
                                  uint32_t column) {
  matrix[0][column] = v[0];
  matrix[1][column] = v[1];
  matrix[2][column] = v[2];
  matrix[3][column] = v[3];
}

inline void MatrixSetColumnVector(matrix4_t &matrix, float v0, float v1,
                                  float v2, float v3, uint32_t column) {
  matrix[0][column] = v0;
  matrix[1][column] = v1;
  matrix[2][column] = v2;
  matrix[3][column] = v3;
}

inline void MatrixSetRowVector(matrix4_t &matrix, const vector_t &v,
                               uint32_t row) {
  memcpy(matrix[row], v, sizeof(v));
}

inline void MatrixSetRowVector(matrix4_t &matrix, float v0, float v1, float v2,
                               float v3, uint32_t row) {
  matrix[row][0] = v0;
  matrix[row][1] = v1;
  matrix[row][2] = v2;
  matrix[row][3] = v3;
}

inline void MatrixGetRowVector(vector_t &ret, const matrix4_t &matrix,
                               uint32_t row) {
  memcpy(ret, matrix[row], sizeof(ret));
}

inline void MatrixCopyMatrix(matrix4_t &dest, const matrix4_t &a) {
  dest[0][0] = a[0][0];
  dest[0][1] = a[0][1];
  dest[0][2] = a[0][2];
  dest[0][3] = a[0][3];

  dest[1][0] = a[1][0];
  dest[1][1] = a[1][1];
  dest[1][2] = a[1][2];
  dest[1][3] = a[1][3];

  dest[2][0] = a[2][0];
  dest[2][1] = a[2][1];
  dest[2][2] = a[2][2];
  dest[2][3] = a[2][3];

  dest[3][0] = a[3][0];
  dest[3][1] = a[3][1];
  dest[3][2] = a[3][2];
  dest[3][3] = a[3][3];
}

void MatrixAddMatrix(const matrix4_t &a, const matrix4_t &b, matrix4_t &sum);
void MatrixAddMatrix(matrix4_t &a, const matrix4_t &b);

void ScalarMultMatrix(const matrix4_t &a, float scalar, matrix4_t &ret);
void ScalarMultMatrix(matrix4_t &a, float scalar);

void MatrixMultMatrix(const matrix4_t &a, const matrix4_t &b, matrix4_t &ret);
void MatrixMultMatrix(matrix4_t &a, const matrix4_t &b);

void MatrixTranspose(const matrix4_t &a, matrix4_t &ret);
void MatrixTranspose(matrix4_t &a);

void MatrixDeterminant(const matrix4_t &a, float &ret);
inline float MatrixDeterminant(const matrix4_t &mat) {
  auto &a = mat[0][0];
  auto &b = mat[0][1];
  auto &c = mat[0][2];
  auto &d = mat[0][3];
  auto &e = mat[1][0];
  auto &f = mat[1][1];
  auto &g = mat[1][2];
  auto &h = mat[1][3];
  auto &i = mat[2][0];
  auto &j = mat[2][1];
  auto &k = mat[2][2];
  auto &l = mat[2][3];
  auto &m = mat[3][0];
  auto &n = mat[3][1];
  auto &o = mat[3][2];
  auto &p = mat[3][3];

  auto in = i * n;
  auto io = i * o;
  auto ip = i * p;
  auto jm = j * m;
  auto jo = j * o;
  auto jp = j * p;
  auto km = k * m;
  auto kn = k * n;
  auto kp = k * p;
  auto lm = l * m;
  auto ln = l * n;
  auto lo = l * o;

  return a * (f * (kp - lo) - g * (jp - ln) + h * (jo - kn)) -
         b * (e * (kp - lo) - g * (ip - lm) + h * (io - km)) +
         c * (e * (jp - ln) - f * (ip - lm) + h * (in - jm)) -
         d * (e * (jo - kn) - f * (io - km) + g * (in - jm));
}

void MatrixDeterminant(const matrix3_t &a, float &ret);
inline float MatrixDeterminant(const matrix3_t &mat) {
  auto &a = mat[0][0];
  auto &b = mat[0][1];
  auto &c = mat[0][2];
  auto &d = mat[1][0];
  auto &e = mat[1][1];
  auto &f = mat[1][2];
  auto &g = mat[2][0];
  auto &h = mat[2][1];
  auto &i = mat[2][2];

  return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

void MatrixInvert(const matrix4_t &a, matrix4_t &ret);

void MatrixCofactor(const matrix4_t &a, uint32_t row, uint32_t column,
                    matrix3_t &ret);

void MatrixAdjoint(matrix4_t &a);
void MatrixAdjoint(const matrix4_t &a, matrix4_t &ret);

}  // namespace XboxMath

#endif  // XBOX_MATH_MATRIX_H_
