## sdf2dgen
simple 2-dimensional sdf generation library

### Build
c++
```bash
git submodule update --init
mkdir build
cd build && cmake .. && make
```
python
```bash
git submodule update --init
pip3 install scikit-build
pip3 install -e .
```

### Usage 
c++ usage
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
  const auto mat = compute_sdf(lb, ub, nx, ny, std::vector<Vertices>{verts}, true);
  std::cout << mat << std::endl;
}
```

python usage
```python
import numpy as np
import matplotlib.pyplot as plt
from pysdf2d import compute_sdf

verts1 = [
        [0.1, 0.1],
        [0.9, 0.1],
        [0.9, 0.9],
        [0.1, 0.9],
        [0.1, 0.8],
        [0.8, 0.8],
        [0.8, 0.2],
        [0.1, 0.2],
        ]

verts2 = [
        [0.5, 0.4],
        [0.6, 0.5],
        [0.5, 0.6],
        [0.4, 0.5],
        ]

mat = compute_sdf([0, 0], [1, 1], 101, 101, [verts1, verts2], True)
plt.imshow(mat)
plt.show()
```
output of above python code is:
![demo](https://user-images.githubusercontent.com/38597814/213878491-173f572b-09c0-4622-9fda-97ef36f96fa1.png)
