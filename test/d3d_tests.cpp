#include <boost/test/unit_test.hpp>

#include "xbox_math_d3d.h"

using namespace XboxMath;

BOOST_AUTO_TEST_SUITE(xbox_math_d3d_suite)

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

BOOST_AUTO_TEST_CASE(test_create_d3d_look_at_lh) {
  vector_t eye{-0.3f, 1.25f, -5.f, 1.f};
  vector_t at{0.f, 0.f, 0.f, 1.f};
  vector_t up{0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f};

  matrix4_t result;
  CreateD3DLookAtLH(result, eye, at, up);

  MATRIX_TEST(result, 0.96336329f, 0.26182887f, 0.0581101887f, 0.f,
              -0.240840822f, 0.939878166f, -0.242125779f, 0.f, -0.118012004f,
              0.219259813f, 0.968503118f, 0.f, -2.23517418e-08f,
              1.49011612e-08f, 5.16260576f, 1.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_perspective_fov_lh) {
  float fov = 65.f;
  float width = 640.f;
  float height = 480.f;
  float z_near = 1.4f;
  float z_far = 183.25f;

  matrix4_t result;
  CreateD3DPerspectiveFOVLH(result, fov, width / height, z_near, z_far);

  MATRIX_TEST(result, 0.396889448f, 0.f, 0.f, 0.f, 0.f, 0.529185951f, 0.f, 0.f,
              0.f, 0.f, 1.00769866f, 1.f, 0.f, 0.f, -1.41077805f, 0.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_viewport) {
  float width = 640.f;
  float height = 480.f;
  float max_depth_buffer = 65536.f;
  float z_near = 1.4f;
  float z_far = 183.25f;

  matrix4_t result;
  CreateD3DViewport(result, width, height, max_depth_buffer, z_near, z_far);

  MATRIX_TEST(result, 320.f, 0.f, 0.f, 0.f, 0.f, -240.f, 0.f, 0.f, 0.f, 0.f,
              11917722.f, 0.f, 320.f, 240.f, 91750.3984f, 1.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_standard_viewport_16_bit) {
  float width = 640.f;
  float height = 480.f;

  matrix4_t result;
  CreateD3DStandardViewport16Bit(result, width, height);

  MATRIX_TEST(result, 320.f, 0.f, 0.f, 0.f, 0.f, -240.f, 0.f, 0.f, 0.f, 0.f,
              65535.f, 0.f, 320.f, 240.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_standard_viewport_16_bit_float) {
  float width = 640.f;
  float height = 480.f;

  matrix4_t result;
  CreateD3DStandardViewport16BitFloat(result, width, height);

  MATRIX_TEST(result, 320.f, 0.f, 0.f, 0.f, 0.f, -240.f, 0.f, 0.f, 0.f, 0.f,
              511.9375f, 0.f, 320.f, 240.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_standard_viewport_24_bit) {
  float width = 640.f;
  float height = 480.f;

  matrix4_t result;
  CreateD3DStandardViewport24Bit(result, width, height);

  MATRIX_TEST(result, 320.f, 0.f, 0.f, 0.f, 0.f, -240.f, 0.f, 0.f, 0.f, 0.f,
              16777215.f, 0.f, 320.f, 240.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_CASE(test_create_d3d_standard_viewport_24_bit_float) {
  float width = 640.f;
  float height = 480.f;

  matrix4_t result;
  CreateD3DStandardViewport24BitFloat(result, width, height);

  MATRIX_TEST(result, 320.f, 0.f, 0.f, 0.f, 0.f, -240.f, 0.f, 0.f, 0.f, 0.f,
              1.00000002e+30f, 0.f, 320.f, 240.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_SUITE_END()
