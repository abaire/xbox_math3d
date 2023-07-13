#ifndef XBOX_MATH_FRUSTUM_H_
#define XBOX_MATH_FRUSTUM_H_

#include "xbox_math_types.h"
#include "xbox_math_vector.h"

namespace XboxMath {

//----------------------------------
//	frustum_t
//----------------------------------
typedef struct frustum_t {
  vertex_t m_upperLeftNear;
  vertex_t m_lowerRightFar;

  // Debug
  vertex_t m_upperRightNear;
  vertex_t m_lowerRightNear;
  vertex_t m_lowerLeftNear;

  vertex_t m_upperRightFar;
  vertex_t m_upperLeftFar;
  vertex_t m_lowerLeftFar;

  vector_t m_nearPlaneNormal;
  vector_t m_topPlaneNormal;
  vector_t m_leftPlaneNormal;

  vector_t m_bottomPlaneNormal;
  vector_t m_rightPlaneNormal;

  // Distance from origin to near and far planes (the two that don't intersect
  // the origin) //
  float m_distNear;
  float m_distFar;
  float m_distLeft;
  float m_distRight;
  float m_distTop;
  float m_distBottom;

  matrix4_t m_frustumMatrix;
  matrix4_t m_frustumInverseMatrix;

  // Creates a frustum matrix for a given perspective view //
  void CreateFrustumMatrixForPerspective(float fovY, float aspect,
                                         float nearParam, float farParam);

  void CreateFrustumMatrix();
  void ApplyFrustum(matrix4_t &toapply);

  void ApplyMatrixToFrustum(const matrix4_t &toMult);

  inline void CalculatePlaneNormals() {
    vector_t v2;

    // Find the "left" plane normal
    VectorCopyVector(m_leftPlaneNormal, m_upperLeftFar);
    VectorSubtractVector(m_leftPlaneNormal, m_upperLeftNear);
    VectorSubtractVector(m_upperLeftNear, m_lowerLeftFar, v2);

    VectorCrossVector(m_leftPlaneNormal, v2);
    VectorNormalize(m_leftPlaneNormal);

    VectorCopyVector(m_rightPlaneNormal, m_lowerRightFar);
    VectorSubtractVector(m_rightPlaneNormal, m_upperRightNear);
    VectorSubtractVector(m_upperRightNear, m_upperRightFar, v2);

    VectorCrossVector(m_rightPlaneNormal, v2);
    VectorNormalize(m_rightPlaneNormal);

    // Find the "top" plane normal
    VectorCopyVector(m_topPlaneNormal, m_upperLeftFar);
    VectorSubtractVector(m_topPlaneNormal, m_upperLeftNear);
    VectorSubtractVector(m_upperLeftNear, m_upperRightFar, v2);

    VectorCrossVector(m_topPlaneNormal, v2);
    VectorNormalize(m_topPlaneNormal);

    VectorCopyVector(m_bottomPlaneNormal, m_lowerRightFar);
    VectorSubtractVector(m_bottomPlaneNormal, m_lowerLeftNear);
    VectorSubtractVector(m_upperLeftNear, m_lowerLeftFar, v2);

    VectorCrossVector(m_bottomPlaneNormal, v2);
    VectorNormalize(m_bottomPlaneNormal);

    // Find the "near" plane normal
    VectorCopyVector(m_nearPlaneNormal, m_upperLeftNear);
    VectorSubtractVector(m_nearPlaneNormal, m_upperRightNear);
    VectorSubtractVector(m_upperRightNear, m_lowerRightNear, v2);

    VectorCrossVector(m_nearPlaneNormal, v2);
    VectorNormalize(m_nearPlaneNormal);

    // Distance to the zNear and zFar planes is just the dot product of the
    // plane against the ULN and LRF points
    m_distNear = VectorDotVector(m_nearPlaneNormal, m_upperLeftNear);
    m_distFar = VectorDotVector(m_nearPlaneNormal, m_upperLeftFar);

    m_distLeft = VectorDotVector(m_leftPlaneNormal, m_upperLeftFar);
    m_distRight = VectorDotVector(m_rightPlaneNormal, m_upperRightFar);

    m_distTop = VectorDotVector(m_topPlaneNormal, m_upperLeftFar);
    m_distBottom = VectorDotVector(m_bottomPlaneNormal, m_lowerLeftFar);
  }

  inline bool PointInFrustum(const vector_t &pt) const {
    // Check against left and right planes
    if (VectorDotVector(pt, m_leftPlaneNormal) - m_distLeft < 0.0f)
      return false;
    if (VectorDotVector(pt, m_rightPlaneNormal) - m_distRight < 0.0f)
      return false;

    // Check against near and far planes
    if (VectorDotVector(pt, m_nearPlaneNormal) - m_distNear < 0.0f)
      return false;
    if (VectorDotVector(pt, m_nearPlaneNormal) - m_distFar > 0.0f) return false;

    // Check against top and bottom planes
    if (VectorDotVector(pt, m_topPlaneNormal) - m_distTop > 0.0f) return false;
    if (VectorDotVector(pt, m_bottomPlaneNormal) - m_distBottom > 0.0f)
      return false;

    return true;
  }

  // Note: Sphere.m_radius is expected to be less than 0
  inline bool SphereInFrustum(const boundingsphere_t &sphere) const {
    // Check against left and right planes
    if (VectorDotVector(sphere.m_centerPt, m_leftPlaneNormal) - m_distLeft <
        sphere.m_radius)
      return false;
    if (VectorDotVector(sphere.m_centerPt, m_rightPlaneNormal) - m_distRight <
        sphere.m_radius)
      return false;

    // Check against near and far planes
    if (VectorDotVector(sphere.m_centerPt, m_nearPlaneNormal) - m_distNear <
        sphere.m_radius)
      return false;
    if (VectorDotVector(sphere.m_centerPt, m_nearPlaneNormal) - m_distFar >
        -sphere.m_radius)
      return false;

    // Check against top and bottom planes
    if (VectorDotVector(sphere.m_centerPt, m_topPlaneNormal) - m_distTop >
        -sphere.m_radius)
      return false;
    if (VectorDotVector(sphere.m_centerPt, m_bottomPlaneNormal) - m_distBottom >
        -sphere.m_radius)
      return false;

    return true;
  }

} frustum_t;

}  // namespace XboxMath

#endif  // XBOX_MATH_FRUSTUM_H_
