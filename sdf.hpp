#include <Eigen/Core>
#include <Eigen/LU>
#include <iostream>
#include <limits>
#include <optional>
#include <vector>

using Vector2d = Eigen::Vector2d;
using Matrix2d = Eigen::Matrix2d;
using MatrixXd = Eigen::MatrixXd;
using Vertices = std::vector<Vector2d>;

double compute_distance(const Vector2d &p, const Vector2d &v0,
                        const Vector2d &v1);

double compute_distance(const Vector2d &p, const Vertices &verts);

double compute_distance(const Vector2d &p,
                        const std::vector<Vertices> &verts_list);

std::optional<double> find_intersection_coef(const Vector2d &p0,
                                             const Vector2d &p1,
                                             const Vector2d &q0,
                                             const Vector2d &q1);

std::vector<double>
find_intersection_coefs(const Vector2d &p0, const Vector2d &p1,
                        const std::vector<Vertices> &verts_list);

MatrixXd compute_sdf(const Vector2d &lb, const Vector2d &ub, size_t nx,
                     size_t ny, const std::vector<Vertices> &verts_list,
                     bool make_signed);
