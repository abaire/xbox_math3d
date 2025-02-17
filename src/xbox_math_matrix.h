#ifndef XBOX_MATH_MATRIX_H_
#define XBOX_MATH_MATRIX_H_

#include "xbox_math_types.h"
#include "xbox_math_vector.h"

namespace XboxMath {

inline void VectorMultMatrix(const vector_t &b, const matrix4_t &a,
                             vector_t &ret) {
  ret[0] = a[0][0] * b[0] + a[1][0] * b[1] + a[2][0] * b[2] + a[3][0] * b[3];
  ret[1] = a[0][1] * b[0] + a[1][1] * b[1] + a[2][1] * b[2] + a[3][1] * b[3];
  ret[2] = a[0][2] * b[0] + a[1][2] * b[1] + a[2][2] * b[2] + a[3][2] * b[3];
  ret[3] = a[0][3] * b[0] + a[1][3] * b[1] + a[2][3] * b[2] + a[3][3] * b[3];
}

inline void VectorMultMatrix(vector_t &ret, const matrix4_t &a) {
  vector_t b;
  VectorMultMatrix(ret, a, b);
  VectorCopyVector(ret, b);
}

inline void MatrixSetIdentity(matrix4_t &matrix) {
  memset(matrix, 0, sizeof(matrix));
  matrix[0][0] = 1.f;
  matrix[1][1] = 1.f;
  matrix[2][2] = 1.f;
  matrix[3][3] = 1.f;
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

inline double MatrixDeterminant(const matrix4_t &mat) {
  const double &a = mat[0][0];
  const double &b = mat[0][1];
  const double &c = mat[0][2];
  const double &d = mat[0][3];
  const double &e = mat[1][0];
  const double &f = mat[1][1];
  const double &g = mat[1][2];
  const double &h = mat[1][3];
  const double &i = mat[2][0];
  const double &j = mat[2][1];
  const double &k = mat[2][2];
  const double &l = mat[2][3];
  const double &m = mat[3][0];
  const double &n = mat[3][1];
  const double &o = mat[3][2];
  const double &p = mat[3][3];

  const double in = i * n;
  const double io = i * o;
  const double ip = i * p;
  const double jm = j * m;
  const double jo = j * o;
  const double jp = j * p;
  const double km = k * m;
  const double kn = k * n;
  const double kp = k * p;
  const double lm = l * m;
  const double ln = l * n;
  const double lo = l * o;

  return a * (f * (kp - lo) - g * (jp - ln) + h * (jo - kn)) -
         b * (e * (kp - lo) - g * (ip - lm) + h * (io - km)) +
         c * (e * (jp - ln) - f * (ip - lm) + h * (in - jm)) -
         d * (e * (jo - kn) - f * (io - km) + g * (in - jm));
}
inline void MatrixDeterminant(const matrix4_t &a, double &ret) {
  ret = MatrixDeterminant(a);
}

inline double MatrixDeterminant(const matrix3_t &mat) {
  const double a = mat[0][0];
  const double b = mat[0][1];
  const double c = mat[0][2];
  const double d = mat[1][0];
  const double e = mat[1][1];
  const double f = mat[1][2];
  const double g = mat[2][0];
  const double h = mat[2][1];
  const double i = mat[2][2];

  return a * (e * i - f * h) - b * (d * i - f * g) +
                 c * (d * h - e * g);
}
inline void MatrixDeterminant(const matrix3_t &a, double &ret) {
  ret = MatrixDeterminant(a);
}

//! Calculates the inverse of `a` and saves it to `ret`.
//! \return false if `a` is not invertible.
bool MatrixInvert(const matrix4_t &a, matrix4_t &ret);

//! Populates `ret` with the submatrix of `a` formed by ignoring `row` and
//`column`
void MatrixSubmatrix(const matrix4_t &a, uint32_t row, uint32_t column,
                     matrix3_t &ret);

//! Replaces `a` with its adjoint.
void MatrixAdjoint(matrix4_t &a);
//! Calculates the adjoint of `a` and saves it to `ret`.
void MatrixAdjoint(const matrix4_t &a, matrix4_t &ret);

void CreateTranslationMatrix(const vector_t &translation, matrix4_t &ret);
void MatrixTranslate(const matrix4_t &mat, const vector_t &translation,
                     matrix4_t &ret);
void MatrixTranslate(matrix4_t &mat, const vector_t &translation);

void CreateScaleMatrix(const vector_t &scale, matrix4_t &ret);
void MatrixScale(const matrix4_t &mat, const vector_t &scale, matrix4_t &ret);
void MatrixScale(matrix4_t &mat, const vector_t &scale);

void MatrixRotate(const matrix4_t &mat, const vector_t &rotation,
                  matrix4_t &ret);
void MatrixRotate(matrix4_t &mat, const vector_t &rotation);

}  // namespace XboxMath

#endif  // XBOX_MATH_MATRIX_H_
