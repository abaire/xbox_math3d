#include "xbox_math_frustum.h"

#include "xbox_math_matrix.h"

#define DEG2RAD(c) ((float)(c) * (float)M_PI / 180.0f)

namespace XboxMath {

//------------------------------------------------
//	CreateFrustumMatrixForPerspective
//------------------------------------------------
void frustum_t::CreateFrustumMatrixForPerspective(float fovY, float aspect,
                                                  float nearParam,
                                                  float farParam) {
  // Calculate the height/width of the near rect
  float h_2n = (tanf(DEG2RAD(fovY / 2))) * nearParam;
  float w_2n = h_2n * aspect;

  // Calculate the height/width of the far rect
  float h_2f = (tanf(DEG2RAD(fovY / 2))) * farParam;
  float w_2f = h_2f * aspect;

  VectorSetVector(m_upperLeftNear, -w_2n, h_2n, -nearParam);
  VectorSetVector(m_lowerRightFar, w_2f, -h_2f, -farParam);

  // Note: These calculations can be optimized like nobody's business, but this
  //  function will probably only be called once per camera, so I figure it's
  //  better to make clear what's going on than make it fast.

  /* DEBUG */
  VectorSetVector(m_upperRightNear, -m_upperLeftNear[0], m_upperLeftNear[1],
                  m_upperLeftNear[2]);
  VectorSetVector(m_lowerRightNear, -m_upperLeftNear[0], -m_upperLeftNear[1],
                  m_upperLeftNear[2]);
  VectorSetVector(m_lowerLeftNear, m_upperLeftNear[0], -m_upperLeftNear[1],
                  m_upperLeftNear[2]);

  VectorSetVector(m_upperRightFar, m_lowerRightFar[0], -m_lowerRightFar[1],
                  m_lowerRightFar[2]);
  VectorSetVector(m_upperLeftFar, -m_lowerRightFar[0], -m_lowerRightFar[1],
                  m_lowerRightFar[2]);
  VectorSetVector(m_lowerLeftFar, -m_lowerRightFar[0], m_lowerRightFar[1],
                  m_lowerRightFar[2]);

  // Other interesting points, upper-left-far, lower-left-far, upper-right-far
  VectorSetVector(m_upperLeftFar, -m_lowerRightFar[0], -m_lowerRightFar[1],
                  m_lowerRightFar[2]);
  VectorSetVector(m_lowerLeftFar, -m_lowerRightFar[0], m_lowerRightFar[1],
                  m_lowerRightFar[2]);
  VectorSetVector(m_upperRightFar, m_lowerRightFar[0], -m_lowerRightFar[1],
                  m_lowerRightFar[2]);

  CalculatePlaneNormals();

  CreateFrustumMatrix();
}

//------------------------------------------------
//	CreateFrustumMatrix
//------------------------------------------------
void frustum_t::CreateFrustumMatrix(void) {
  m_upperLeftNear[2] *= -1;
  m_lowerRightFar[2] *= -1;

  float TwoN = m_upperLeftNear[2] * 2.0f;
  float TwoFN = TwoN * m_lowerRightFar[2];
  float FarMinusNear = m_lowerRightFar[2] - m_upperLeftNear[2];
  float FarPlusNear = m_lowerRightFar[2] + m_upperLeftNear[2];

  float RightMinusLeft = (-m_upperLeftNear[0]) - m_upperLeftNear[0];
  float TopMinusBottom = m_upperLeftNear[1] - (-m_upperLeftNear[1]);
  float RightPlusLeft = (-m_upperLeftNear[0]) + m_upperLeftNear[0];
  float TopPlusBottom = m_upperLeftNear[1] + (-m_upperLeftNear[1]);

  MatrixSetRowVector(m_frustumMatrix, TwoN / RightMinusLeft, 0,
                     RightPlusLeft / RightMinusLeft, 0, 0);
  MatrixSetRowVector(m_frustumMatrix, 0, TwoN / TopMinusBottom,
                     TopPlusBottom / TopMinusBottom, 0, 1);
  MatrixSetRowVector(m_frustumMatrix, 0, 0, -FarPlusNear / FarMinusNear,
                     -TwoFN / FarMinusNear, 2);
  MatrixSetRowVector(m_frustumMatrix, 0, 0, -1.0f, 0, 3);

  /*
          MatrixSetRowVector( m_frustumInverseMatrix, RightMinusLeft/TwoN, 0, 0,
     RightPlusLeft/TwoN, 0 ); MatrixSetRowVector( m_frustumInverseMatrix, 0,
     TopMinusBottom/TwoN, 0, TopPlusBottom/TwoN, 1 ); MatrixSetRowVector(
     m_frustumInverseMatrix, 0, 0, 0, -1, 2 ); MatrixSetRowVector(
     m_frustumInverseMatrix, 0, 0, -(FarMinusNear)/TwoFN, FarPlusNear/TwoFN, 3
     );
  */

  m_upperLeftNear[2] *= -1;
  m_lowerRightFar[2] *= -1;
}

//------------------------------------------------
//	ApplyFrustum
//------------------------------------------------
void frustum_t::ApplyFrustum(matrix4_t &toapply) {
  MatrixMultMatrix(toapply, m_frustumMatrix);
}

//------------------------------------------------
//	ApplyMatrixToFrustum
//------------------------------------------------
void frustum_t::ApplyMatrixToFrustum(const matrix4_t &toMult) {
  MatrixMultMatrix(m_frustumMatrix, toMult);
  //	MatrixMultMatrix( m_frustumInverseMatrix, toMult );

  VectorMultMatrix(m_upperLeftNear, toMult);
  VectorMultMatrix(m_lowerRightFar, toMult);

  VectorMultMatrix(m_upperRightNear, toMult);
  VectorMultMatrix(m_lowerRightNear, toMult);
  VectorMultMatrix(m_lowerLeftNear, toMult);

  VectorMultMatrix(m_upperRightFar, toMult);
  VectorMultMatrix(m_upperLeftFar, toMult);
  VectorMultMatrix(m_lowerLeftFar, toMult);

  // Recalculate vector normals //
  CalculatePlaneNormals();
}

}  // namespace XboxMath
