#include "xbox_math_util.h"

#include "xbox_math_matrix.h"

namespace XboxMath {

void BuildCompositeMatrix(const matrix4_t &model_view,
                          const matrix4_t &projection, matrix4_t &result) {
  MatrixMultMatrix(model_view, projection, result);
}

void BuildInverseCompositeMatrix(const matrix4_t &composite_matrix,
                                 matrix4_t &result) {
  MatrixInvert(composite_matrix, result);
}

void ProjectPoint(const vector_t &world_point,
                  const matrix4_t &composite_matrix, vector_t &result) {
  vector_t screen_point;
  VectorMultMatrix(world_point, composite_matrix, screen_point);

  result[0] = screen_point[0] / screen_point[3];
  result[1] = screen_point[1] / screen_point[3];
  result[2] = screen_point[2] / screen_point[3];
  result[3] = 1.0f;
}

void UnprojectPoint(const vector_t &screen_point,
                    const matrix4_t &inverse_composite_matrix,
                    vector_t &result) {
  VectorMultMatrix(screen_point, inverse_composite_matrix, result);

  result[0] /= result[3];
  result[1] /= result[3];
  result[2] /= result[3];
  result[3] = 1.0f;
}

void UnprojectPoint(const vector_t &screen_point,
                    const matrix4_t &inverse_composite_matrix, float world_z,
                    vector_t &result) {
  vector_t work;
  VectorCopyVector(work, screen_point);

  // TODO: Get the near and far plane mappings from the viewport matrix.
  work[2] = 0.0f;
  vector_t near_plane;
  VectorMultMatrix(work, inverse_composite_matrix, near_plane);
  VectorEuclidean(near_plane);

  work[2] = 64000.0f;
  vector_t far_plane;
  VectorMultMatrix(work, inverse_composite_matrix, far_plane);
  VectorEuclidean(far_plane);

  float t = (world_z - near_plane[2]) / (far_plane[2] - near_plane[2]);
  result[0] = near_plane[0] + (far_plane[0] - near_plane[0]) * t;
  result[1] = near_plane[1] + (far_plane[1] - near_plane[1]) * t;
  result[2] = world_z;
  result[3] = 1.0f;
}

}  // namespace XboxMath
