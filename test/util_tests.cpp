#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>

#include "xbox_math_d3d.h"
#include "xbox_math_matrix.h"
#include "xbox_math_util.h"

using namespace XboxMath;

BOOST_AUTO_TEST_SUITE(xbox_math_util_suite)

static constexpr auto kTolerance = 1e-5f;

#define VECTOR_TEST(v, x, y, z, w)                                     \
  BOOST_TEST((v)[0] == (x), boost::test_tools::tolerance(kTolerance)); \
  BOOST_TEST((v)[1] == (y), boost::test_tools::tolerance(kTolerance)); \
  BOOST_TEST((v)[2] == (z), boost::test_tools::tolerance(kTolerance)); \
  BOOST_TEST((v)[3] == (w), boost::test_tools::tolerance(kTolerance))

#define MATRIX_TEST(m, m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, \
                    m34, m41, m42, m43, m44)                                  \
  VECTOR_TEST((m)[0], m11, m12, m13, m14);                                    \
  VECTOR_TEST((m)[1], m21, m22, m23, m24);                                    \
  VECTOR_TEST((m)[2], m31, m32, m33, m34);                                    \
  VECTOR_TEST((m)[3], m41, m42, m43, m44)

#define MATRIX_MATRIX_TEST(m, e)                           \
  VECTOR_TEST((m)[0], e[0][0], e[0][1], e[0][2], e[0][3]); \
  VECTOR_TEST((m)[1], e[1][0], e[1][1], e[1][2], e[1][3]); \
  VECTOR_TEST((m)[2], e[2][0], e[2][1], e[2][2], e[2][3]); \
  VECTOR_TEST((m)[3], e[3][0], e[3][1], e[3][2], e[3][3])

BOOST_AUTO_TEST_CASE(build_composite_matrix_identity) {
  matrix4_t model_view;
  matrix4_t projection;
  matrix4_t result;

  MatrixSetIdentity(model_view);
  MatrixSetIdentity(projection);

  BuildCompositeMatrix(model_view, projection, result);

  MATRIX_TEST(result, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f,
              0.f, 0.f, 0.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_CASE(build_composite_matrix_with_just_model_view) {
  vector_t eye{-0.3f, 1.25f, -5.f, 1.f};
  vector_t at{0.f, 0.f, 0.f, 1.f};
  vector_t up{0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f};

  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, eye, at, up);

  matrix4_t projection;
  MatrixSetIdentity(projection);

  matrix4_t result;
  BuildCompositeMatrix(model_view, projection, result);

  MATRIX_TEST(result, 0.96336329f, 0.26182887f, 0.0581101887f, 0.f,
              -0.240840822f, 0.939878166f, -0.242125779f, 0.f, -0.118012004f,
              0.219259813f, 0.968503118f, 0.f, -2.23517418e-08f,
              1.49011612e-08f, 5.16260576f, 1.f);
}

static void BuildD3DProjectionViewportMatrix16Bit(matrix4_t &result, float fov,
                                                  float z_near, float z_far) {
  matrix4_t viewport;
  CreateD3DStandardViewport16Bit(viewport, 640.f, 480.f);

  matrix4_t projection;
  CreateD3DPerspectiveFOVLH(projection, fov, 640.f / 480.f, z_near, z_far);

  MatrixMultMatrix(projection, viewport, result);
}

BOOST_AUTO_TEST_CASE(build_composite_matrix_just_projection) {
  matrix4_t model_view;
  MatrixSetIdentity(model_view);

  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);

  matrix4_t result;
  BuildCompositeMatrix(model_view, projection, result);

  MATRIX_TEST(result, 579.411194f, 0.f, 0.f, 0.f, 0.f, -579.411194f, 0.f, 0.f,
              320.f, 240.f, 65864.3203f, 1.f, 0.f, 0.f, -65864.3203f, 0.f);
}

struct CompositeMatrixTestCase {
  vector_t eye;
  vector_t at;
  vector_t up;

  matrix4_t expected;
};

std::ostream &operator<<(std::ostream &os, const CompositeMatrixTestCase &tc) {
  auto print_vector = [&os](const vector_t &pt) {
    os << " " << pt[0] << " " << pt[1] << " " << pt[2] << " " << pt[3]
       << std::endl;
  };

  os << "Eye ";
  print_vector(tc.eye);
  os << "At ";
  print_vector(tc.at);
  os << "Up ";
  print_vector(tc.up);
  os << "Expected matrix {" << std::endl;
  for (auto row : tc.expected) {
    os << " " << row[0] << " " << row[1] << " " << row[2] << " " << row[3]
       << std::endl;
  }
  os << "}" << std::endl;

  return os;
}

const std::vector<CompositeMatrixTestCase> kBuildCompositeMatrixTestCases = {
    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {{576.778748f, -137.760132f, 3827.388184f, 0.058110f},
      {-217.026123f, -602.686096f, -15947.450195f, -0.242126f},
      {241.543518f, 105.399162f, 63789.800781f, 0.968503f},
      {1652.033813f, 1239.025391f, 274167.218750f, 5.162606f}}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {{579.411194f, 0.f, 0.f, 0.f},
      {0.f, -579.411194f, 0.f, 0.f},
      {320.f, 240.f, 65864.3203f, 1.f},
      {2240.f, 1680.f, 395185.938f, 7.f}}},
};
BOOST_DATA_TEST_CASE(
    build_composite_matrix,
    boost::unit_test::data::make(kBuildCompositeMatrixTestCases), test_case) {
  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, test_case.eye, test_case.at, test_case.up);

  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);

  matrix4_t result;
  BuildCompositeMatrix(model_view, projection, result);

  MATRIX_MATRIX_TEST(result, test_case.expected);
}

BOOST_AUTO_TEST_CASE(build_inverse_composite_matrix_identity) {
  matrix4_t model_view;
  MatrixSetIdentity(model_view);
  matrix4_t projection;
  MatrixSetIdentity(projection);
  matrix4_t composite;
  BuildCompositeMatrix(model_view, projection, composite);

  matrix4_t result;
  BuildInverseCompositeMatrix(composite, result);

  MATRIX_TEST(result, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f,
              0.f, 0.f, 0.f, 0.f, 1.f);
}

const std::vector<CompositeMatrixTestCase>
    kBuildInverseCompositeMatrixTestCases = {
        {{-0.3f, 1.25f, -5.f, 1.f},
         {0.f, 0.f, 0.f, 1.f},
         {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
         {{0.00166265934240072966, -0.00041566483560018241,
           -0.00020367576507851481, 0.00000000000072597652},
          {-0.00045188781223259866, -0.00162212620489299297,
           -0.00037841830635443330, -0.00000000000019731039},
          {0.00000455481858807616, -0.00001897841320896987,
           0.00007591365283587947, -0.00001518273074907484},
          {-0.66548770666122436523, 1.53019762039184570312,
           -3.87550163269042968750, 1.00000023841857910156}}},
        {{0.0f, 0.0f, -7.0f, 1.0f},
         {0.0f, 0.0f, 0.0f, 1.0f},
         {0.0f, 1.0f, 0.0f, 1.0f},
         {{0.00172588986f, 0.f, 0.f, 0.f},
          {0.f, -0.00172588986f, 0.f, 0.f},
          {0.f, 0.f, 0.000106279098f, -1.51827298e-05f},
          {-0.552284777f, 0.414213598f, -6.00000095f, 1.00000012f}}},
};
BOOST_DATA_TEST_CASE(
    build_inverse_composite_matrix,
    boost::unit_test::data::make(kBuildInverseCompositeMatrixTestCases),
    test_case) {
  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, test_case.eye, test_case.at, test_case.up);
  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);
  matrix4_t composite;
  BuildCompositeMatrix(model_view, projection, composite);

  matrix4_t result;
  BuildInverseCompositeMatrix(composite, result);

  MATRIX_MATRIX_TEST(result, test_case.expected);
}

struct ProjectUnprojectTestCase {
  vector_t eye;
  vector_t at;
  vector_t up;

  vector_t world_point;
  vector_t screen_point;
};

std::ostream &operator<<(std::ostream &os, const ProjectUnprojectTestCase &tc) {
  auto print_vector = [&os](const vector_t &pt) {
    os << " " << pt[0] << " " << pt[1] << " " << pt[2] << " " << pt[3]
       << std::endl;
  };

  os << "Eye ";
  print_vector(tc.eye);
  os << "At ";
  print_vector(tc.at);
  os << "Up ";
  print_vector(tc.up);
  os << "World ";
  print_vector(tc.world_point);
  os << "Screen ";
  print_vector(tc.screen_point);

  return os;
}

const std::vector<ProjectUnprojectTestCase> kProjectPointTestCases = {
    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {0.f, 0.f, 1.f, 1.f},
     {308.847473f, 219.27919f, 55121.6836f, 1.f}},

    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {-0.251061678f, 1.04609084f, -4.02123594f, 1.f},
     {308.847473f, 219.27919f, 9.99848366f, 1.f}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {-0.531582057f, -0.0604070313f, -5.99998522f, 1.f},
     {11.9998226f, 275.f, 0.999985218f, 1.f}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {0.f, 0.f, -5.99998522f, 1.f},
     {320.f, 240.f, 0.999985218f, 1.f}}};

BOOST_DATA_TEST_CASE(project_point,
                     boost::unit_test::data::make(kProjectPointTestCases),
                     test_case) {
  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, test_case.eye, test_case.at, test_case.up);
  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);
  matrix4_t composite;
  BuildCompositeMatrix(model_view, projection, composite);

  vector_t result;
  ProjectPoint(test_case.world_point, composite, result);

  VECTOR_TEST(result, test_case.screen_point[0], test_case.screen_point[1],
              test_case.screen_point[2], test_case.screen_point[3]);
}

const std::vector<ProjectUnprojectTestCase> kUnprojectPointTestCases = {
    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {-0.251061678f, 1.04609084f, -4.02123594f, 1.f},
     {308.847473f, 219.27919f, 10.f, 1.f}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {-0.531582057f, -0.0604070313f, -5.99998522f, 1.f},
     {12.f, 275.f, 1.f, 1.f}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {0.f, 0.f, -5.99998522f, 1.f},
     {320.f, 240.f, 1.f, 1.f}},

    {{0.0f, 0.0f, -7.0f, 1.0f},
     {0.0f, 0.0f, 0.0f, 1.0f},
     {0.0f, 1.0f, 0.0f, 1.0f},
     {0.483256429f, -0.276146531f, -5.99998522f, 1.f},
     {600.f, 400.f, 1.f, 1.f}},

};
BOOST_DATA_TEST_CASE(unproject_point,
                     boost::unit_test::data::make(kUnprojectPointTestCases),
                     test_case) {
  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, test_case.eye, test_case.at, test_case.up);
  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);
  matrix4_t composite;
  BuildCompositeMatrix(model_view, projection, composite);
  matrix4_t inverse;
  BuildInverseCompositeMatrix(composite, inverse);

  vector_t result;
  UnprojectPoint(test_case.screen_point, inverse, result);

  VECTOR_TEST(result, test_case.world_point[0], test_case.world_point[1],
              test_case.world_point[2], test_case.world_point[3]);
}

const std::vector<ProjectUnprojectTestCase> kUnprojectPointWithZTestCases = {
    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {0.f, 0.f, 1.f, 1.f},
     {308.847473f, 219.27919f, 55121.6836f, 1.f}},

    {{0.f, 0.f, 5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {0.f, 0.f, 1.f, 1.f},
     {320.f, 240.f, 1.f, 1.f}},

    {{-0.3f, 1.25f, -5.f, 1.f},
     {0.f, 0.f, 0.f, 1.f},
     {0.24253562503633297f, 0.9701425001453319f, 0.0f, 1.f},
     {-3.69574022f, -1.38491642f, 1.f, 1.f},
     {10.f, 430.f, 1.f, 1.f}},

};

BOOST_DATA_TEST_CASE(
    unproject_point_with_z,
    boost::unit_test::data::make(kUnprojectPointWithZTestCases), test_case) {
  matrix4_t model_view;
  CreateD3DLookAtLH(model_view, test_case.eye, test_case.at, test_case.up);
  matrix4_t projection;
  BuildD3DProjectionViewportMatrix16Bit(projection, M_PI * 0.25f, 1.0f, 200.0f);
  matrix4_t composite;
  BuildCompositeMatrix(model_view, projection, composite);
  matrix4_t inverse;
  BuildInverseCompositeMatrix(composite, inverse);

  vector_t result;
  UnprojectPoint(test_case.screen_point, inverse, test_case.world_point[2],
                 result);

  VECTOR_TEST(result, test_case.world_point[0], test_case.world_point[1],
              test_case.world_point[2], test_case.world_point[3]);
}

BOOST_AUTO_TEST_SUITE_END()
