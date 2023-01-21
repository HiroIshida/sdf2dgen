#include "pybind11/eigen.h"
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "sdf.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_pysdf2d, m) {
  m.doc() = "2d sdf generator";
  m.def("compute_sdf", &sdf::compute_sdf);
}
