#include "xbox_math_matrix.h"

#ifndef NDEBUG
#include <cassert>
#define DBGASSERT(c) assert((c))
#else
#define DBGASSERT(c) \
  do {               \
  } while (false)
#endif

namespace XboxMath {

void MatrixAddMatrix(const matrix4_t &a, const matrix4_t &b, matrix4_t &sum) {
  sum[0][0] = a[0][0] + b[0][0];
  sum[0][1] = a[0][1] + b[0][1];
  sum[0][2] = a[0][2] + b[0][2];
  sum[0][3] = a[0][3] + b[0][3];

  sum[1][0] = a[1][0] + b[1][0];
  sum[1][1] = a[1][1] + b[1][1];
  sum[1][2] = a[1][2] + b[1][2];
  sum[1][3] = a[1][3] + b[1][3];

  sum[2][0] = a[2][0] + b[2][0];
  sum[2][1] = a[2][1] + b[2][1];
  sum[2][2] = a[2][2] + b[2][2];
  sum[2][3] = a[2][3] + b[2][3];

  sum[3][0] = a[3][0] + b[3][0];
  sum[3][1] = a[3][1] + b[3][1];
  sum[3][2] = a[3][2] + b[3][2];
  sum[3][3] = a[3][3] + b[3][3];
}

void MatrixAddMatrix(matrix4_t &a, const matrix4_t &b) {
  a[0][0] += b[0][0];
  a[0][1] += b[0][1];
  a[0][2] += b[0][2];
  a[0][3] += b[0][3];

  a[1][0] += b[1][0];
  a[1][1] += b[1][1];
  a[1][2] += b[1][2];
  a[1][3] += b[1][3];

  a[2][0] += b[2][0];
  a[2][1] += b[2][1];
  a[2][2] += b[2][2];
  a[2][3] += b[2][3];

  a[3][0] += b[3][0];
  a[3][1] += b[3][1];
  a[3][2] += b[3][2];
  a[3][3] += b[3][3];
}

void ScalarMultMatrix(const matrix4_t &a, float scalar, matrix4_t &sum) {
  sum[0][0] = a[0][0] * scalar;
  sum[0][1] = a[0][1] * scalar;
  sum[0][2] = a[0][2] * scalar;
  sum[0][3] = a[0][3] * scalar;

  sum[1][0] = a[1][0] * scalar;
  sum[1][1] = a[1][1] * scalar;
  sum[1][2] = a[1][2] * scalar;
  sum[1][3] = a[1][3] * scalar;

  sum[2][0] = a[2][0] * scalar;
  sum[2][1] = a[2][1] * scalar;
  sum[2][2] = a[2][2] * scalar;
  sum[2][3] = a[2][3] * scalar;

  sum[3][0] = a[3][0] * scalar;
  sum[3][1] = a[3][1] * scalar;
  sum[3][2] = a[3][2] * scalar;
  sum[3][3] = a[3][3] * scalar;
}

void ScalarMultMatrix(matrix4_t &a, float scalar) {
  a[0][0] *= scalar;
  a[0][1] *= scalar;
  a[0][2] *= scalar;
  a[0][3] *= scalar;

  a[1][0] *= scalar;
  a[1][1] *= scalar;
  a[1][2] *= scalar;
  a[1][3] *= scalar;

  a[2][0] *= scalar;
  a[2][1] *= scalar;
  a[2][2] *= scalar;
  a[2][3] *= scalar;

  a[3][0] *= scalar;
  a[3][1] *= scalar;
  a[3][2] *= scalar;
  a[3][3] *= scalar;
}

void MatrixMultMatrix(const matrix4_t &a, const matrix4_t &b, matrix4_t &ret) {
  DBGASSERT(&a != &ret && &b != &ret);
  ret[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] +
              a[0][3] * b[3][0];
  ret[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] +
              a[0][3] * b[3][1];
  ret[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] +
              a[0][3] * b[3][2];
  ret[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] +
              a[0][3] * b[3][3];

  ret[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] +
              a[1][3] * b[3][0];
  ret[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] +
              a[1][3] * b[3][1];
  ret[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] +
              a[1][3] * b[3][2];
  ret[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] +
              a[1][3] * b[3][3];

  ret[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] +
              a[2][3] * b[3][0];
  ret[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] +
              a[2][3] * b[3][1];
  ret[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] +
              a[2][3] * b[3][2];
  ret[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] +
              a[2][3] * b[3][3];

  ret[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] +
              a[3][3] * b[3][0];
  ret[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] +
              a[3][3] * b[3][1];
  ret[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] +
              a[3][3] * b[3][2];
  ret[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] +
              a[3][3] * b[3][3];
}

void MatrixMultMatrix(matrix4_t &a, const matrix4_t &b) {
  matrix4_t temp;
  MatrixMultMatrix(a, b, temp);
  MatrixCopyMatrix(a, temp);
}

void MatrixTranspose(const matrix4_t &a, matrix4_t &ret) {
  DBGASSERT(&a != &ret);
  for (auto row = 0; row < 4; ++row) {
    for (auto col = 0; col < 4; ++col) {
      ret[row][col] = a[col][row];
    }
  }
}

void MatrixTranspose(matrix4_t &a) {
  matrix4_t temp;
  MatrixTranspose(a, temp);
  MatrixCopyMatrix(a, temp);
}

void MatrixDeterminant(const matrix4_t &a, float &ret) {
  ret = MatrixDeterminant(a);
}

void MatrixDeterminant(const matrix3_t &a, float &ret) {
  ret = MatrixDeterminant(a);
}

void MatrixInvert(const matrix4_t &a, matrix4_t &ret) {
  DBGASSERT(&a != &ret);
  MatrixCopyMatrix(ret, a);
  MatrixAdjoint(ret);

  ScalarMultMatrix(ret, 1.0f / MatrixDeterminant(a));
}

void MatrixAdjoint(matrix4_t &a) {
  matrix4_t temp;
  MatrixAdjoint(a, temp);
  MatrixCopyMatrix(a, temp);
}

void MatrixAdjoint(const matrix4_t &a, matrix4_t &ret) {
  DBGASSERT(&a != &ret);
  float sign = 1.f;

  matrix3_t cofactor_matrix;
  for (auto r = 0; r < 4; ++r) {
    for (auto c = 0; c < 4; ++c) {
      MatrixCofactor(a, r, c, cofactor_matrix);
      ret[c][r] = sign * MatrixDeterminant(cofactor_matrix);
      sign *= -1.f;
    }
    sign *= -1.f;
  }
}

void MatrixCofactor(const matrix4_t &a, uint32_t row, uint32_t column,
                    matrix3_t &ret) {
  auto orow = 0;

  for (auto r = 0; r < 4; ++r) {
    if (r == row) {
      continue;
    }

    auto ocol = 0;
    for (auto c = 0; c < 4; ++c) {
      if (c == column) {
        continue;
      }
      ret[orow][ocol] = a[r][c];
      ++ocol;
    }

    ++orow;
  }
}

void CreateTranslationMatrix(const vector_t &translation, matrix4_t &ret) {
  MatrixSetIdentity(ret);
  ret[3][0] = translation[0];
  ret[3][1] = translation[1];
  ret[3][2] = translation[2];
}

void MatrixTranslate(const matrix4_t &mat, const vector_t &translation,
                     matrix4_t &ret) {
  matrix4_t translation_matrix;
  CreateTranslationMatrix(translation, translation_matrix);
  MatrixMultMatrix(mat, translation_matrix, ret);
}

void MatrixTranslate(matrix4_t &mat, const vector_t &translation) {
  matrix4_t tmp;
  MatrixTranslate(mat, translation, tmp);
  MatrixCopyMatrix(mat, tmp);
}

void CreateScaleMatrix(const vector_t &scale, matrix4_t &ret) {
  MatrixSetIdentity(ret);
  ret[0][0] = scale[0];
  ret[1][1] = scale[1];
  ret[2][2] = scale[2];
}

void MatrixScale(const matrix4_t &mat, const vector_t &scale, matrix4_t &ret) {
  matrix4_t scale_matrix;
  CreateScaleMatrix(scale, scale_matrix);
  MatrixMultMatrix(mat, scale_matrix, ret);
}

void MatrixScale(matrix4_t &mat, const vector_t &scale) {
  matrix4_t tmp;
  MatrixScale(mat, scale, tmp);
  MatrixCopyMatrix(mat, tmp);
}

void MatrixRotate(const matrix4_t &mat, const vector_t &rotation,
                  matrix4_t &ret) {
  DBGASSERT(&mat != &ret);
  matrix4_t temp;

  MatrixSetIdentity(temp);
  float sin_rz = sinf(rotation[2]);
  float cos_rz = cosf(rotation[2]);
  temp[0][0] = cos_rz;
  temp[0][1] = sin_rz;
  temp[1][0] = -sin_rz;
  temp[1][1] = cos_rz;
  MatrixMultMatrix(mat, temp, ret);

  MatrixSetIdentity(temp);
  float sin_ry = sinf(rotation[1]);
  float cos_ry = cosf(rotation[1]);
  temp[0][0] = cos_ry;
  temp[0][2] = -sin_ry;
  temp[2][0] = sin_ry;
  temp[2][2] = cos_ry;
  MatrixMultMatrix(ret, temp);

  MatrixSetIdentity(temp);
  float sin_rx = sinf(rotation[0]);
  float cos_rx = cosf(rotation[0]);
  temp[1][1] = cos_rx;
  temp[1][2] = sin_rx;
  temp[2][1] = -sin_rx;
  temp[2][2] = cos_rx;
  MatrixMultMatrix(ret, temp);
}

void MatrixRotate(matrix4_t &mat, const vector_t &rotation) {
  matrix4_t tmp;
  MatrixRotate(mat, rotation, tmp);
  MatrixCopyMatrix(mat, tmp);
}

}  // namespace XboxMath
