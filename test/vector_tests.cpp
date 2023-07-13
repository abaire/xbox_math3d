#include <boost/test/unit_test.hpp>
#include <cmath>

#include "xbox_math_vector.h"

using namespace XboxMath;

BOOST_AUTO_TEST_SUITE(xbox_math_vector_suite)

#define TOLERANCE 1e-5f

#define VECTOR_TEST(v, x, y, z, w)                                    \
  BOOST_TEST((v)[0] == (x), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[1] == (y), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[2] == (z), boost::test_tools::tolerance(TOLERANCE)); \
  BOOST_TEST((v)[3] == (w), boost::test_tools::tolerance(TOLERANCE))

BOOST_AUTO_TEST_CASE(vector_identity_produces_identity_vector) {
  vector_t test;

  VectorIdentity(test);

  VECTOR_TEST(test, 0.f, 0.f, 0.f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_add_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  vector_t result{0.f, 0.f, 0.f, 1.f};
  VectorAddVector(vec1, vec2, result);

  VECTOR_TEST(result, 0.25f, 0.324f, -0.69f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_add_vector_inplace) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  VectorAddVector(vec1, vec2);

  VECTOR_TEST(vec1, 0.25f, 0.324f, -0.69f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_subtract_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  vector_t result{0.f, 0.f, 0.f, 1.f};
  VectorSubtractVector(vec1, vec2, result);

  VECTOR_TEST(result, 1.75f, 0.076f, 1.29f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_subtract_vector_inplace) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  VectorSubtractVector(vec1, vec2);

  VECTOR_TEST(vec1, 1.75f, 0.076f, 1.29f, 1.f);
}

BOOST_AUTO_TEST_CASE(scalar_mult_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};

  vector_t result{0.f, 0.f, 0.f, 1.f};
  ScalarMultVector(vec1, -0.6f, result);

  VECTOR_TEST(result, -0.6f, -0.12f, -0.18f, 1.f);
}

BOOST_AUTO_TEST_CASE(scalar_mult_vector_inplace) {
  vector_t result{1.f, 0.2f, 0.3f, 1.f};

  ScalarMultVector(result, -0.6f);

  VECTOR_TEST(result, -0.6f, -0.12f, -0.18f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_normalize) {
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  vector_t result{0.f, 0.f, 0.f, 1.f};
  VectorNormalize(vec2, result);

  VECTOR_TEST(result, -0.6008704987622265f, 0.09934392246202145f,
              -0.793149058366139f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_normalize_inplace) {
  vector_t result{-0.75f, 0.124f, -0.99f, 1.f};

  VectorNormalize(result);

  VECTOR_TEST(result, -0.6008704987622265f, 0.09934392246202145f,
              -0.793149058366139f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_dot_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  float result;
  VectorDotVector(vec1, vec2, result);

  BOOST_TEST(result, -1.0222f);
}

BOOST_AUTO_TEST_CASE(vector_length) {
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  float result;
  VectorLength(vec2, result);

  BOOST_TEST(result, 1.2481890882394382f);
}

BOOST_AUTO_TEST_CASE(vector_cross_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  vector_t result{0.f, 0.f, 0.f, 1.f};
  VectorCrossVector(vec1, vec2, result);

  VECTOR_TEST(result, -0.23520000000000002f, 0.765f, 0.274f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_cross_vector_inplace) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  VectorCrossVector(vec1, vec2);

  VECTOR_TEST(vec1, -0.23520000000000002f, 0.765f, 0.274f, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_copy_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};
  vector_t vec2{-0.75f, 0.124f, -0.99f, 1.f};

  VectorCopyVector(vec1, vec2);

  VECTOR_TEST(vec1, vec2[0], vec2[1], vec2[2], vec2[3]);
}

BOOST_AUTO_TEST_CASE(vector_set_vector) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};

  VectorSetVector(vec1, 12.f, -992.123f, 1024.f, -50.f);

  VECTOR_TEST(vec1, 12.f, -992.123f, 1024.f, -50.f);
}

BOOST_AUTO_TEST_CASE(vector_euclidean_with_1w) {
  vector_t vec1{1.f, 0.2f, 0.3f, 1.f};

  vector_t result;
  VectorEuclidean(vec1, result);

  VECTOR_TEST(result, vec1[0], vec1[1], vec1[2], 1.f);
}

BOOST_AUTO_TEST_CASE(vector_euclidean_with_infw) {
  vector_t vec1{1.f, 0.2f, 0.3f, INFINITY};

  vector_t result;
  VectorEuclidean(vec1, result);

  VECTOR_TEST(result, INFINITY, INFINITY, INFINITY, 1.f);
}

BOOST_AUTO_TEST_CASE(vector_euclidean) {
  vector_t vec1{-1.f, 0.2f, 0.3f, -10.f};

  vector_t result;
  VectorEuclidean(vec1, result);

  VECTOR_TEST(result, 0.1f, -0.02f, -0.03f, 1.f);
}

BOOST_AUTO_TEST_SUITE_END()
