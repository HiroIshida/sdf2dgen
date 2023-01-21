#include "sdf.hpp"
#include <Eigen/Core>
#include <Eigen/LU>
#include <gtest/gtest.h>

using namespace sdf;

TEST(TEST_COMPUTE_DISTANCE_EACH, AllTest) {
  Eigen::Vector2d v0, v1, p;
  v0 << 0, 0;
  v1 << 1.0, 0.0;

  p << -1.0, 1.0;
  ASSERT_NEAR(compute_distance(p, v0, v1), std::sqrt(2), 1e-6);

  p << 0.5, 1.0;
  ASSERT_NEAR(compute_distance(p, v0, v1), 1.0, 1e-6);

  p << 2.0, 1.0;
  ASSERT_NEAR(compute_distance(p, v0, v1), std::sqrt(2), 1e-6);
}

TEST(TEST_COMPUTE_DISTANCE_BATCH, AllTest) {
  Eigen::Vector2d v0, v1, v2, v3, p;
  v0 << 0, 0;
  v1 << 1.0, 0.0;
  v2 << 1.0, 1.0;
  v3 << 0.0, 1.0;
  auto verts = std::vector<Eigen::Vector2d>{v0, v1, v2, v3};

  p << 0.0, 0.0;
  ASSERT_NEAR(compute_distance(p, verts), 0.0, 1e-6);

  p << 0.5, 0.5;
  ASSERT_NEAR(compute_distance(p, verts), 0.5, 1e-6);

  p << 1.5, 0.5;
  ASSERT_NEAR(compute_distance(p, verts), 0.5, 1e-6);

  p << 0.5, -0.5;
  ASSERT_NEAR(compute_distance(p, verts), 0.5, 1e-6);
}

TEST(TEST_FIND_INTERSECTION_COEF, AllTest) {
  Eigen::Vector2d p0, p1, q0, q1;
  p0 << 0, 0;
  p1 << 1., 0.0;
  q0 << 0.5, -0.5;
  q1 << 0.5, +0.5;
  ASSERT_NEAR(*find_intersection_coef(p0, p1, q0, q1), 0.5, 1e-6);

  q0 << 0.5, -0.5;
  q1 << 0.5, -0.3;
  ASSERT_EQ(find_intersection_coef(p0, p1, q0, q1), std::nullopt);

  // edge case
  q0 << 0.0, 0.0;
  q1 << 0.0, 1.0;
  ASSERT_NEAR(*find_intersection_coef(p0, p1, q0, q1), 0.0, 1e-6);

  // edge case2
  q0 << 0.0, 0.0;
  q1 << 0.5, 1.0;
  ASSERT_NEAR(*find_intersection_coef(p0, p1, q0, q1), 0.0, 1e-6);

  // parallel case
  q0 << 0.0, 0.0;
  q1 << 1.0, 0.0;
  ASSERT_EQ(find_intersection_coef(p0, p1, q0, q1), std::nullopt);
}

TEST(TEST_FIND_INTERSECTION_COEFS, AllTest) {
  Eigen::Vector2d v0, v1, v2, v3;
  v0 << 0, 0;
  v1 << 1.0, 0.0;
  v2 << 1.0, 1.0;
  v3 << 0.0, 1.0;
  auto verts = std::vector<Eigen::Vector2d>{v0, v1, v2, v3};

  {
    Eigen::Vector2d p0, p1;
    p0 << -0.5, 0.5;
    p1 << 1.5, 0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.75, 1e-6);
  }

  {
    Eigen::Vector2d p0, p1;
    p0 << -0.5, -0.5;
    p1 << 1.5, -0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 0);
  }

  {
    Eigen::Vector2d p0, p1;
    p0 << -0.5, 0.5;
    p1 << 0.5, 0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.5, 1e-6);
    ASSERT_NEAR(coefs.at(1), 1.5, 1e-6);
  }

  {
    Eigen::Vector2d p0, p1;
    p0 << -1.0, -1.0;
    p1 << 3.0, 3.0;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.5, 1e-6);
  }

  {
    Eigen::Vector2d p0, p1;
    p0 << -1.0, 0.0;
    p1 << 3.0, 1.0;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.50, 1e-6);
  }
}

TEST(TEST_COMPUTE_SDF, AllTest) {
  Eigen::Vector2d v0, v1, v2, v3;
  v0 << 0.25, 0.25;
  v1 << 0.75, 0.25;
  v2 << 0.75, 0.75;
  v3 << 0.25, 0.75;
  auto verts = std::vector<Eigen::Vector2d>{v0, v1, v2, v3};
  Eigen::Vector2d lb, ub;
  lb << 0., 0.;
  ub << 1., 1.;
  size_t nx = 10;
  size_t ny = 20;
  const auto mat =
      compute_sdf(lb, ub, nx, ny, std::vector<Vertices>{verts}, true);
  std::cout << mat << std::endl;

  // positive
  ASSERT_NEAR(mat(0, 0), 0.25 * std::sqrt(2.0), 1e-6);
  ASSERT_NEAR(mat(1, 0), std::sqrt(0.15 * 0.15 + 0.25 * 0.25), 1e-6);
  ASSERT_NEAR(mat(0, 1), std::sqrt(0.25 * 0.25 + 0.2 * 0.2), 1e-6);

  ASSERT_NEAR(mat(5, 0), 0.25, 1e-6);
  ASSERT_NEAR(mat(5, 1), 0.20, 1e-6);

  ASSERT_NEAR(mat(5, ny), 0.25, 1e-6);
  ASSERT_NEAR(mat(5, ny - 1), 0.20, 1e-6);

  // negative
  ASSERT_NEAR(mat(5, 10), -0.25, 1e-6);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
