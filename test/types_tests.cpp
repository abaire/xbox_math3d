#include <boost/test/unit_test.hpp>

#include "xbox_math_types.h"

using namespace XboxMath;

BOOST_AUTO_TEST_SUITE(xbox_math_types_suite)

#define TOLERANCE 1e-5f

#define VECTOR_TEST(v, x, y, z, w)                                    \
  BOOST_TEST((v)[0] == (x), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[1] == (y), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[2] == (z), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[3] == (w), boost::test_tools::tolerance(TOLERANCE))

BOOST_AUTO_TEST_CASE(point_distance_point) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  float result = PointDistancePoint(vec1, vec2);

  BOOST_TEST(result == 2.17540249149439f,
             boost::test_tools::tolerance(TOLERANCE));
}

BOOST_AUTO_TEST_CASE(plane_find_normal) {
  vector_t vec1{0.9517f, 0.3829f, -0.987f, 1.f};
  vector_t vec2{-0.8828f, 0.5937f, 0.620f, 1.f};
  vector_t vec3{0.0425f, -0.1562f, 0.634f, 1.f};

  vector_t result;
  PlaneFindNormal(vec1, vec2, vec3, result);

  VECTOR_TEST(result, 1.20804036f, 1.51264012f, 1.18063819f, 1.f);
}

BOOST_AUTO_TEST_CASE(plane_find_normalized_normal) {
  vector_t vec1{0.9517f, 0.3829f, -0.987f, 1.f};
  vector_t vec2{-0.8828f, 0.5937f, 0.620f, 1.f};
  vector_t vec3{0.0425f, -0.1562f, 0.634f, 1.f};

  vector_t result;
  PlaneFindNormalizedNormal(vec1, vec2, vec3, result);

  VECTOR_TEST(result, 0.53277f, 0.66711f, 0.52069f, 1.f);
}

BOOST_AUTO_TEST_SUITE_END()
