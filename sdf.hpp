#include <Eigen/Core>
#include <Eigen/LU>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

namespace sdf {

using Vertices = std::vector<Eigen::Vector2d>;

double compute_distance(const Eigen::Vector2d &p, const Eigen::Vector2d &v0,
                        const Eigen::Vector2d &v1);

double compute_distance(const Eigen::Vector2d &p, const Vertices &verts);

double compute_distance(const Eigen::Vector2d &p,
                        const std::vector<Vertices> &verts_list);

std::optional<double> find_intersection_coef(const Eigen::Vector2d &p0,
                                             const Eigen::Vector2d &p1,
                                             const Eigen::Vector2d &q0,
                                             const Eigen::Vector2d &q1);

std::vector<double>
find_intersection_coefs(const Eigen::Vector2d &p0, const Eigen::Vector2d &p1,
                        const std::vector<Vertices> &verts_list);

Eigen::MatrixXd compute_sdf(const Eigen::Vector2d &lb,
                            const Eigen::Vector2d &ub, size_t nx, size_t ny,
                            const std::vector<Vertices> &verts_list,
                            bool make_signed);

} // namespace sdf
