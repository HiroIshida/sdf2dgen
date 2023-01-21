## tiny 2d sdf generation library

Usage (see `demo.cpp`)
```c++
#include "sdf.hpp"
#include <Eigen/Core>
#include <iostream>

using namespace sdf;
using namespace std;

int main() {
  Eigen::Vector2d v0, v1, v2, v3;

  v0 << 0.25, 0.25;
  v1 << 0.75, 0.25;
  v2 << 0.75, 0.75;
  v3 << 0.25, 0.75;
  auto verts = std::vector<Eigen::Vector2d>{v0, v1, v2, v3};

  Eigen::Vector2d lb, ub;
  lb << 0., 0.;
  ub << 1., 1.;
  size_t nx = 8;
  size_t ny = 8;
  const auto mat =
      compute_sdf(lb, ub, nx, ny, std::vector<Vertices>{verts}, true);
  std::cout << mat << std::endl;
}
```
