#include "sdf.hpp"
#include <Eigen/Core>
#include <Eigen/LU>
#include <gtest/gtest.h>

TEST(TEST_COMPUTE_DISTANCE_EACH, AllTest) {
  Vector2d v0, v1, p;
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
  Vector2d v0, v1, v2, v3, p;
  v0 << 0, 0;
  v1 << 1.0, 0.0;
  v2 << 1.0, 1.0;
  v3 << 0.0, 1.0;
  auto verts = std::vector<Vector2d>{v0, v1, v2, v3};

  p << 0.0, 0.0;
  ASSERT_NEAR(compute_distance(p, verts), 0.0, 1e-6);

  p << 0.5, 0.5;
  ASSERT_NEAR(compute_distance(p, verts), 0.5, 1e-6);

  p << 1.5, 0.5;
  ASSERT_NEAR(compute_distance(p, verts), 0.5, 1e-6);
}

TEST(TEST_FIND_INTERSECTION_COEF, AllTest) {
  Vector2d p0, p1, q0, q1;
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
  Vector2d v0, v1, v2, v3;
  v0 << 0, 0;
  v1 << 1.0, 0.0;
  v2 << 1.0, 1.0;
  v3 << 0.0, 1.0;
  auto verts = std::vector<Vector2d>{v0, v1, v2, v3};

  {
    Vector2d p0, p1;
    p0 << -0.5, 0.5;
    p1 << 1.5, 0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.75, 1e-6);
  }

  {
    Vector2d p0, p1;
    p0 << -0.5, -0.5;
    p1 << 1.5, -0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 0);
  }

  {
    Vector2d p0, p1;
    p0 << -0.5, 0.5;
    p1 << 0.5, 0.5;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 1);
    ASSERT_NEAR(coefs.at(0), 0.5, 1e-6);
  }

  {
    Vector2d p0, p1;
    p0 << -1.0, -1.0;
    p1 << 3.0, 3.0;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.5, 1e-6);
  }

  {
    Vector2d p0, p1;
    p0 << -1.0, 0.0;
    p1 << 3.0, 1.0;
    auto coefs = find_intersection_coefs(p0, p1, std::vector<Vertices>{verts});
    ASSERT_EQ(coefs.size(), 2);
    ASSERT_NEAR(coefs.at(0), 0.25, 1e-6);
    ASSERT_NEAR(coefs.at(1), 0.50, 1e-6);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
