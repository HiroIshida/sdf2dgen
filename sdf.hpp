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
                        const Vector2d &v1) {
  const auto diff = v1 - v0;
  const double t = (p - v0).dot(diff) / diff.dot(diff);
  if (t < 0.0) {
    return (p - v0).norm();
  } else if (t > 1.0) {
    return (p - v1).norm();
  } else {
    return (p - (v0 + t * diff)).norm();
  }
}

double compute_distance(const Vector2d &p, const Vertices &verts) {
  double min_dist = std::numeric_limits<double>::infinity();
  for (size_t i = 0; i < verts.size(); ++i) {
    double dist_cand;
    if (i < verts.size() - 1) {
      dist_cand = compute_distance(p, verts.at(i), verts.at(i + 1));
    } else {
      dist_cand = compute_distance(p, verts.back(), verts.at(0));
    }
    if (dist_cand < min_dist) {
      min_dist = dist_cand;
    }
  }
  return min_dist;
}

double compute_distance(const Vector2d &p,
                        const std::vector<Vertices> &verts_list) {
  double min_dist = std::numeric_limits<double>::infinity();
  for (const auto &verts : verts_list) {
    const double dist_cand = compute_distance(p, verts);
    if (dist_cand < min_dist) {
      min_dist = dist_cand;
    }
  }
  return min_dist;
}

std::optional<double> find_intersection_coef(const Vector2d &p0,
                                             const Vector2d &p1,
                                             const Vector2d &q0,
                                             const Vector2d &q1) {
  // when we have p0 + s * (p1 - p0), q0 + t * (q1 - q0), this function returns
  // s
  const Vector2d &e = p1 - p0;
  const Vector2d &f = q1 - q0;
  Matrix2d m;
  m << -e(0), f(0), -e(1), f(1);
  Vector2d v;
  v << f(0), -f(1);

  const double det = m.determinant();
  bool is_parallel = (std::abs(det) < 1e-7);
  if (is_parallel) {
    return {};
  }

  const auto st = m.inverse() * (p0 - q0);
  const double s = st(0);
  const double t = st(1);
  if (t >= 0 && t < 1.0) {
    return s;
  } else {
    return {};
  }
}

std::vector<double>
find_intersection_coefs(const Vector2d &p0, const Vector2d &p1,
                        const std::vector<Vertices> &verts_list) {
  std::vector<double> coefs;
  for (const auto &verts : verts_list) {
    for (size_t i = 0; i < verts.size(); ++i) {
      std::optional<double> coef;
      if (i < verts.size() - 1) {
        coef = find_intersection_coef(p0, p1, verts.at(i), verts.at(i + 1));
      } else {
        coef = find_intersection_coef(p0, p1, verts.back(), verts.at(0));
      }
      if (coef) {
        coefs.push_back(*coef);
      }
    }
  }
  std::sort(coefs.begin(), coefs.end());
  return coefs;
}

MatrixXd compute_sdf(const Vector2d &lb, const Vector2d &ub, size_t nx,
                     size_t ny, const std::vector<Vertices> &verts_list,
                     bool make_signed) {
  const auto &width = ub - lb;
  const double wx = width(0) / nx;
  const double wy = width(1) / ny;
  MatrixXd mat(nx + 1, ny + 1);
  for (size_t i = 0; i < nx + 1; ++i) {
    for (size_t j = 0; j < ny + 1; ++j) {
      auto p = lb;
      p(0) += wx * i;
      p(1) += wy * j;
      mat(i, j) = compute_distance(p, verts_list);
    }
  }
  if (!make_signed) {
    return mat;
  }

  // determine sign
  for (size_t i = 0; i < nx + 1; ++i) {
    auto p_start = lb;
    p_start(0) += wx * i;

    auto p_end = p_start;
    p_end(1) += wy;
    const auto coefs = find_intersection_coefs(p_start, p_end, verts_list);
    if (coefs.size() == 0) {
      continue;
    }

    size_t coef_idx = 0;
    bool is_positive = true;
    for (size_t j = 0; j < ny + 1; ++j) {
      if (coef_idx < coefs.size()) {
        if (j > coefs[coef_idx]) {
          coef_idx++;
          is_positive = !is_positive;
        }
      }
      if (!is_positive) {
        mat(i, j) *= -1;
      }
    }
  }
  return mat;
}
