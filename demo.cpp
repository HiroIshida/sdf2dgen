#include "sdf.hpp"
#include <Eigen/Core>
#include <fstream>
#include <iostream>

using namespace sdf;
using namespace std;

int main() {
  Eigen::Vector2d v0, v1, v2, v3, v4, v5, v6, v7;

  v0 << 0.1, 0.1;
  v1 << 0.9, 0.1;
  v2 << 0.9, 0.9;
  v3 << 0.1, 0.9;
  v4 << 0.1, 0.8;
  v5 << 0.8, 0.8;
  v6 << 0.8, 0.2;
  v7 << 0.1, 0.2;

  auto verts = std::vector<Eigen::Vector2d>{v0, v1, v2, v3, v4, v5, v6, v7};

  v0 << 0.5, 0.4;
  v1 << 0.6, 0.5;
  v2 << 0.5, 0.6;
  v3 << 0.4, 0.5;
  auto verts2 = std::vector<Eigen::Vector2d>{v0, v1, v2, v3};

  Eigen::Vector2d lb, ub;
  lb << 0., 0.;
  ub << 1., 1.;
  size_t nx = 101;
  size_t ny = 101;
  const auto mat =
      compute_sdf(lb, ub, nx, ny, std::vector<Vertices>{verts, verts2}, true);

  const Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols,
                                  ", ", "\n");
  ofstream file("output.csv");
  file << mat.format(CSVFormat);
}
