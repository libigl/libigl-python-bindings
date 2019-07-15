#include <pybind11/pybind11.h>

#include <igl/arap.h>
#include <igl/slim.h>
#include <igl/bbw.h>
#include <npe.h>

namespace py = pybind11;

PYBIND11_MODULE(pyigl_classes, m) {
    py::class_<igl::ARAPData>(m, "ARAP")
        .def(py::init([](Eigen::MatrixXd V, Eigen::MatrixXi F, int dim, Eigen::MatrixXi b) {
          if (!(V.cols() == 4 && dim == 4 || V.cols() == 3 && dim == 2 || V.cols() == 3 && dim == 3 || V.cols() == 2 && dim == 2)) {
            throw pybind11::value_error("Invalid dimension. Argument V must have shape (n, 4), (n, 3), or (n, 2) and dim must be 2, 3, or 4");
          }
          std::unique_ptr<igl::ARAPData> adata(new igl::ARAPData());
          igl::arap_precomputation(V, F, dim, b, *adata);
          return adata;
        }))
        .def("solve", [](igl::ARAPData& self, Eigen::MatrixXd bc, Eigen::MatrixXd initial_guess) {
          igl::arap_solve(bc, self, initial_guess);
          return npe::move(initial_guess);
        });

    py::class_<igl::SLIMData>(m, "SLIM")
        .def(py::init([](Eigen::MatrixXd V, Eigen::MatrixXi F, Eigen::MatrixXd V_init,
                         Eigen::VectorXi b, Eigen::MatrixXd bc,
                         int energy_type, double soft_penalty) {
          if (V.cols() != 3) {
            throw pybind11::value_error("Invalid dimension. Argument V must have shape (#vertices, 3)");
          }
          if (V_init.cols() != 3) {
            throw pybind11::value_error("Invalid dimension. Argument V_init must have shape (#vertices, 3)");
          }
          if (F.cols() != 3) {
            throw pybind11::value_error("Invalid dimension. Argument F must have shape (#faces, 3)");
          }
          if (F.rows() <= 0) {
            throw pybind11::value_error("Invalid argument F has zero rows. Cannot have zero faces.");
          }
          if (V.rows() <= 0) {
            throw pybind11::value_error("Invalid argument V has zero rows. Cannot have zero faces.");
          }
          if (V_init.rows() <= 0) {
            throw pybind11::value_error("Invalid argument V has zero rows. Cannot have zero faces.");
          }
          if (bc.rows() != b.size()) {
             throw pybind11::value_error("Invalid argument bc.shape[0] must equal len(b) has zero rows. Cannot have zero faces.");
          }
          if (bc.rows() > 0 && bc.cols() != 3) {
             throw pybind11::value_error("Invalid argument V has zero rows. Cannot have zero faces.");
          }

          std::unique_ptr<igl::SLIMData> sdata(new igl::SLIMData());
          igl::slim_precompute(V, F, V_init, *sdata, static_cast<igl::MappingEnergyType>(energy_type), b, bc, soft_penalty);
          return sdata;
        }))
        .def("solve", [](igl::SLIMData& self, int num_iters) {
          igl::slim_solve(self, num_iters);
        })
        .def("vertices", [](igl::SLIMData& self) {
          // If we wrap self.V_o in an npe::move() then the instance 'self'
          // no longer owns that memory which is not what we want
          Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Vo;
          Vo = self.V_o;
          return npe::move(Vo);
        })
        .def("energy", [](igl::SLIMData& self) {
          return self.energy;
        });

    py::class_<igl::BBWData>(m, "BBW")
        .def(py::init([](int verbosity=0) {
          std::unique_ptr<igl::BBWData> bdata(new igl::BBWData());
          bdata->verbosity = verbosity;
          return bdata;
        }))
        .def("solve", [](igl::BBWData& self, Eigen::MatrixXd V, Eigen::MatrixXi F,
          Eigen::VectorXi b, Eigen::MatrixXd bc) {
          if (V.cols() != 3) {
            throw pybind11::value_error("Invalid dimension. Argument V must have shape (#vertices, 3)");
          }
          if (F.cols() != 3) {
            throw pybind11::value_error("Invalid dimension. Argument F must have shape (#faces, 3)");
          }
          if (F.rows() <= 0) {
            throw pybind11::value_error("Invalid argument F has zero rows. Cannot have zero faces.");
          }
          if (V.rows() <= 0) {
            throw pybind11::value_error("Invalid argument V has zero rows. Cannot have zero faces.");
          }
          if (bc.rows() != b.size()) {
            throw pybind11::value_error("Invalid argument bc.shape[0] must equal len(b) has zero rows. Cannot have zero faces.");
          }

          Eigen::MatrixXd W;
          igl::bbw(V, F, b, bc, self, W);
          return npe::move(W);
        });
}
