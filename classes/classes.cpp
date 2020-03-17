#include <pybind11/pybind11.h>
#include <common.h>

#include <igl/arap.h>
#include <igl/slim.h>
#include <igl/bbw.h>
#include <npe.h>

namespace py = pybind11;

PYBIND11_MODULE(pyigl_classes, m) {
    py::class_<igl::ARAPData>(m, "ARAP")
        .def(py::init([](Eigen::MatrixXd v, Eigen::MatrixXi f, int dim, Eigen::MatrixXi b) {
                 if (dim == 3) {
                     assert_valid_tet_or_tri_mesh(v, f);
                 } else if (dim == 2) {
                     assert_valid_3d_tri_mesh(v, f);
                 } else {
                     throw pybind11::value_error("Invalid dimension must be 2 or 3 but got " + std::to_string(dim));
                 }

                 std::unique_ptr<igl::ARAPData> adata(new igl::ARAPData());
                 if(b.cols() == 1)
                  igl::arap_precomputation(v, f, dim, b, *adata);
                 else if (b.rows() == 1)
                   igl::arap_precomputation(v, f, dim, b.transpose().eval(), *adata);
                 else
                 throw pybind11::value_error("Invalid dimension for b, must be a vector, got " + std::to_string(b.rows()) + "x" + std::to_string(b.cols()));
                 return adata;
        }))
        .def("solve", [](igl::ARAPData& self, Eigen::MatrixXd bc, Eigen::MatrixXd initial_guess) {
          if(bc.size() > 0)
            assert_cols_equals(bc, self.dim, "bc");
          assert_rows_match(bc, self.b, "bc", "self.b");
          assert_rows_match(initial_guess, (int)self.n, 3, std::string("initial_guess"), std::string("self.v"));
          assert_cols_equals(initial_guess, self.dim, "initial_guess");

          igl::arap_solve(bc, self, initial_guess);
          Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> initial_guess_row_major = initial_guess;
          return npe::move(initial_guess_row_major);
        });

    py::class_<igl::SLIMData>(m, "SLIM")
        .def(py::init([](Eigen::MatrixXd v, Eigen::MatrixXi f, Eigen::MatrixXd v_init,
                         Eigen::VectorXi b, Eigen::MatrixXd bc,
                         int energy_type, double soft_penalty) {
          assert_valid_tet_or_tri_mesh(v, f);
          assert_rows_match(bc, b, "bc", "b");
          assert_cols_equals(b, 1, "b");
          assert_rows_match(v_init, v, "v_init", "v");

          // Triangle mesh
          if (f.cols() == 3) {
            if (bc.cols() != 2) {
              throw pybind11::value_error("Invalid dimension for argument bc. Must have shape (#bc, 2) for triangle mesh inputs. You passed in bc with shape ("
                                          + std::to_string(bc.rows()) + std::string(", ") + std::to_string(bc.cols()) + std::string(")"));
            }
            if (v_init.cols() != 2) {
              throw pybind11::value_error("Invalid dimension for argument v_init. Must have shape (#vertices, 2) for triangle mesh inputs. You passed in v_init with shape ("
                                          + std::to_string(v_init.rows()) + std::string(", ") + std::to_string(v_init.cols()) + std::string(")"));
            }
          // Tet mesh
          } else if (f.cols() == 4) {
            if (bc.cols() != 3) {
              throw pybind11::value_error("Invalid dimension for argument bc. Must have shape (#bc, 3) for tet mesh inputs. You passed in bc with shape ("
                                          + std::to_string(bc.rows()) + std::string(", ") + std::to_string(bc.cols()) + std::string(")"));
            }
            if (v_init.cols() != 3) {
              throw pybind11::value_error("Invalid dimension for argument v_init. Must have shape (#vertices, 3) for tet mesh inputs. You passed in v_init with shape ("
                                          + std::to_string(v_init.rows()) + std::string(", ") + std::to_string(v_init.cols()) + std::string(")"));
            }
          } else {
            throw pybind11::value_error("WTF File a github issue");
          }

          if (energy_type >= igl::MappingEnergyType::NUM_SLIM_ENERGY_TYPES) {
            throw pybind11::value_error("Invalid Energy Type. Must be one of igl.SLIM_ENERGY_*");
          }
          std::unique_ptr<igl::SLIMData> sdata(new igl::SLIMData());
          igl::slim_precompute(v, f, v_init, *sdata, static_cast<igl::MappingEnergyType>(energy_type), b, bc, soft_penalty);
          return sdata;
        }))
        .def("solve", [](igl::SLIMData& self, unsigned num_iters) {
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
       .def(py::init([](int verbosity=0, int max_iter=100) {
         std::unique_ptr<igl::BBWData> bdata(new igl::BBWData());
         bdata->verbosity = verbosity;
         bdata->active_set_params.max_iter = max_iter;
         return bdata;
       }))
       .def("solve", [](igl::BBWData& self, Eigen::MatrixXd V, Eigen::MatrixXi F,
         Eigen::VectorXi b, Eigen::MatrixXd bc) {
         if (V.cols() != 3) {
           throw pybind11::value_error("Invalid dimension. Argument V must have shape (#vertices, 3)");
         }
         // Triangle mesh
         if (F.cols() == 3)
         {
           if (V.cols() != 2)
           {
             throw pybind11::value_error("Invalid dimension for argument v_init. Must have shape (#vertices, 2) for triangle mesh inputs. You passed in V with shape (" + std::to_string(V.rows()) + std::string(", ") + std::to_string(V.cols()) + std::string(")"));
           }
           // Tet mesh
         }
         else if (F.cols() == 4)
         {
           if (V.cols() != 3)
           {
             throw pybind11::value_error("Invalid dimension for argument V. Must have shape (#vertices, 3) for tet mesh inputs. You passed in V with shape (" + std::to_string(V.rows()) + std::string(", ") + std::to_string(V.cols()) + std::string(")"));
           }
         }
         else
         {
           throw pybind11::value_error("WTF File a github issue");
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
         Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> W_row_major = W;
         return npe::move(W_row_major);
       });
}
