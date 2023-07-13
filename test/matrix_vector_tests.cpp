#include <boost/test/unit_test.hpp>

#include "xbox_math_matrix.h"

using namespace XboxMath;

BOOST_AUTO_TEST_SUITE(xbox_math_matrix_vector_suite)

#define TOLERANCE 1e-5f

#define VECTOR_TEST(v, x, y, z, w)                                    \
  BOOST_TEST((v)[0] == (x), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[1] == (y), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[2] == (z), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[3] == (w), boost::test_tools::tolerance(TOLERANCE))

#define MATRIX_TEST(m, m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, \
                    m34, m41, m42, m43, m44)                                  \
  VECTOR_TEST((m)[0], m11, m12, m13, m14);                                    \
  VECTOR_TEST((m)[1], m21, m22, m23, m24);                                    \
  VECTOR_TEST((m)[2], m31, m32, m33, m34);                                    \
  VECTOR_TEST((m)[3], m41, m42, m43, m44)

BOOST_AUTO_TEST_CASE(vector_mult_matrix) {
  matrix4_t mat1{0.45f, 0.80f, -0.44f, 0.97f,  0.10f, 0.14f, 0.93f, -0.41f,
                 0.20f, 0.43f, -0.67f, -0.21f, 0.47f, 0.03f, 0.61f, 0.25f};
  vector_t vec1 = {1.0f, 0.20f, 0.30f, 1.0f};

  vector_t result;
  VectorMultMatrix(vec1, mat1, result);

  VECTOR_TEST(result, 1.448f, -0.003f, -0.125f, 0.909f);
}

BOOST_AUTO_TEST_CASE(vector_mult_matrix_inline) {
  matrix4_t mat1{0.45f, 0.80f, -0.44f, 0.97f,  0.10f, 0.14f, 0.93f, -0.41f,
                 0.20f, 0.43f, -0.67f, -0.21f, 0.47f, 0.03f, 0.61f, 0.25f};
  vector_t vec1 = {1.0f, 0.20f, 0.30f, 1.0f};

  VectorMultMatrix(vec1, mat1);

  VECTOR_TEST(vec1, 1.448f, -0.003f, -0.125f, 0.909f);
}

BOOST_AUTO_TEST_CASE(matrix_set_column_vector) {
  matrix4_t mat1{0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
                 0.10285853f, 0.14615238f, 0.933197f,   0.4180919f,
                 0.2032315f,  0.43770744f, 0.67267487f, 0.21421973f,
                 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f};
  vector_t vec1 = {1.f, 2.f, 3.f, -4.f};

  MatrixSetColumnVector(mat1, vec1, 0);

  MATRIX_TEST(mat1, 1.f, 0.80329256f, 0.44714458f, 0.97829298f, 2.f,
              0.14615238f, 0.933197f, 0.4180919f, 3.f, 0.43770744f, 0.67267487f,
              0.21421973f, -4.f, 0.03613376f, 0.61641922f, 0.25477532f);
}

BOOST_AUTO_TEST_CASE(matrix_set_column_vector_components) {
  matrix4_t mat1{0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
                 0.10285853f, 0.14615238f, 0.933197f,   0.4180919f,
                 0.2032315f,  0.43770744f, 0.67267487f, 0.21421973f,
                 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f};
  MatrixSetColumnVector(mat1, 1.f, 2.f, 3.f, -4.f, 0);

  MATRIX_TEST(mat1, 1.f, 0.80329256f, 0.44714458f, 0.97829298f, 2.f,
              0.14615238f, 0.933197f, 0.4180919f, 3.f, 0.43770744f, 0.67267487f,
              0.21421973f, -4.f, 0.03613376f, 0.61641922f, 0.25477532f);
}

BOOST_AUTO_TEST_CASE(matrix_set_row_vector) {
  matrix4_t mat1{0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
                 0.10285853f, 0.14615238f, 0.933197f,   0.4180919f,
                 0.2032315f,  0.43770744f, 0.67267487f, 0.21421973f,
                 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f};
  MatrixSetRowVector(mat1, {1.f, 2.f, 3.f, -4.f}, 2);

  MATRIX_TEST(mat1, 0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
              0.10285853f, 0.14615238f, 0.933197f, 0.4180919f, 1.f, 2.f, 3.f,
              -4.f, 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f);
}

BOOST_AUTO_TEST_CASE(matrix_set_row_vector_components) {
  matrix4_t mat1{0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
                 0.10285853f, 0.14615238f, 0.933197f,   0.4180919f,
                 0.2032315f,  0.43770744f, 0.67267487f, 0.21421973f,
                 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f};
  MatrixSetRowVector(mat1, 1.f, 2.f, 3.f, -4.f, 2);

  MATRIX_TEST(mat1, 0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
              0.10285853f, 0.14615238f, 0.933197f, 0.4180919f, 1.f, 2.f, 3.f,
              -4.f, 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f);
}

BOOST_AUTO_TEST_CASE(matrix_get_row_vector) {
  matrix4_t mat1{0.45497313f, 0.80329256f, 0.44714458f, 0.97829298f,
                 0.10285853f, 0.14615238f, 0.933197f,   0.4180919f,
                 0.2032315f,  0.43770744f, 0.67267487f, 0.21421973f,
                 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f};
  vector_t result;
  MatrixGetRowVector(result, mat1, 3);

  VECTOR_TEST(result, 0.47228118f, 0.03613376f, 0.61641922f, 0.25477532f);
}

BOOST_AUTO_TEST_SUITE_END()
