#include <pybind11/pybind11.h>
#include <common.h>

#include <igl/arap.h>
#include <igl/slim.h>
#include <igl/bbw.h>
#include <igl/shapeup.h>
#include <npe.h>

namespace py = pybind11;

// Forward declaration
template <int DIM>
void init_AABB(py::module_ &);

PYBIND11_MODULE(pyigl_classes, m)
{
  init_AABB<2>(m);
  init_AABB<3>(m);

  py::class_<igl::ARAPData>(m, "ARAP")
      .def(py::init([](Eigen::MatrixXd &v, Eigen::MatrixXi &f, int dim, Eigen::MatrixXi &b,
                       const int energy_type, const bool with_dynamics, const double h, const double ym, const int max_iter) {
             if (dim == 3)
             {
               assert_valid_tet_or_tri_mesh(v, f);
             }
             else if (dim == 2)
             {
               assert_valid_23d_tri_mesh(v, f);
             }
             else
             {
               throw pybind11::value_error("Invalid dimension must be 2 or 3 but got " + std::to_string(dim));
             }
             if (energy_type >= igl::NUM_ARAP_ENERGY_TYPES)
             {
               throw pybind11::value_error("Invalid Energy Type. Must be one of igl.ARAP_ENERGY_TYPE_*");
             }

             std::unique_ptr<igl::ARAPData> adata = std::make_unique<igl::ARAPData>();
             adata->energy = static_cast<igl::ARAPEnergyType>(energy_type);
             adata->with_dynamics = with_dynamics;
             adata->h = h;
             adata->ym = ym;
             adata->max_iter = max_iter;

             if (b.cols() == 1)
               igl::arap_precomputation(v, f, dim, b, *adata);
             else if (b.rows() == 1)
               igl::arap_precomputation(v, f, dim, b.transpose().eval(), *adata);
             else
               throw pybind11::value_error("Invalid dimension for b, must be a vector, got " + std::to_string(b.rows()) + "x" + std::to_string(b.cols()));
             return adata;
           }),
           py::arg("v"), py::arg("f"), py::arg("dim"), py::arg("b"), py::arg("energy_type") = 3, py::arg("with_dynamics") = false, py::arg("h") = 1, py::arg("ym") = 1, py::arg("max_iter") = 10)
      .def(
          "solve", [](igl::ARAPData &self, Eigen::MatrixXd &bc, Eigen::MatrixXd &initial_guess) {
            if (bc.size() > 0)
              assert_cols_equals(bc, self.dim, "bc");
            assert_rows_match(bc, self.b, "bc", "self.b");
            assert_rows_match(initial_guess, (int)self.n, 3, std::string("initial_guess"), std::string("self.v"));
            assert_cols_equals(initial_guess, self.dim, "initial_guess");

            igl::arap_solve(bc, self, initial_guess);
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> initial_guess_row_major = initial_guess;
            return npe::move(initial_guess_row_major);
          },
          py::arg("bc"), py::arg("initial_guess"));

  py::class_<igl::SLIMData>(m, "SLIM")
      .def(py::init([](Eigen::MatrixXd &v, Eigen::MatrixXi &f, Eigen::MatrixXd &v_init,
                       Eigen::VectorXi &b, Eigen::MatrixXd &bc,
                       int energy_type, double soft_penalty) {
             assert_valid_tet_or_tri_mesh(v, f);
             assert_rows_match(bc, b, "bc", "b");
             assert_cols_equals(b, 1, "b");
             assert_rows_match(v_init, v, "v_init", "v");

             // Triangle mesh
             if (f.cols() == 3)
             {
               if (bc.cols() != 2)
               {
                 throw pybind11::value_error("Invalid dimension for argument bc. Must have shape (#bc, 2) for triangle mesh inputs. You passed in bc with shape (" + std::to_string(bc.rows()) + std::string(", ") + std::to_string(bc.cols()) + std::string(")"));
               }
               if (v_init.cols() != 2)
               {
                 throw pybind11::value_error("Invalid dimension for argument v_init. Must have shape (#vertices, 2) for triangle mesh inputs. You passed in v_init with shape (" + std::to_string(v_init.rows()) + std::string(", ") + std::to_string(v_init.cols()) + std::string(")"));
               }
               // Tet mesh
             }
             else if (f.cols() == 4)
             {
               if (bc.cols() != 3)
               {
                 throw pybind11::value_error("Invalid dimension for argument bc. Must have shape (#bc, 3) for tet mesh inputs. You passed in bc with shape (" + std::to_string(bc.rows()) + std::string(", ") + std::to_string(bc.cols()) + std::string(")"));
               }
               if (v_init.cols() != 3)
               {
                 throw pybind11::value_error("Invalid dimension for argument v_init. Must have shape (#vertices, 3) for tet mesh inputs. You passed in v_init with shape (" + std::to_string(v_init.rows()) + std::string(", ") + std::to_string(v_init.cols()) + std::string(")"));
               }
             }
             else
             {
               throw pybind11::value_error("WTF File a github issue");
             }

             if (energy_type >= igl::MappingEnergyType::NUM_SLIM_ENERGY_TYPES)
             {
               throw pybind11::value_error("Invalid Energy Type. Must be one of igl.SLIM_ENERGY_*");
             }
             std::unique_ptr<igl::SLIMData> sdata = std::make_unique<igl::SLIMData>();
             igl::slim_precompute(v, f, v_init, *sdata, static_cast<igl::MappingEnergyType>(energy_type), b, bc, soft_penalty);
             return sdata;
           }),
           py::arg("v"), py::arg("f"), py::arg("v_init"), py::arg("b"), py::arg("bc"), py::arg("energy_type"), py::arg("soft_penalty"))
      .def(
          "solve", [](igl::SLIMData &self, unsigned num_iters) {
            igl::slim_solve(self, num_iters);
          },
          py::arg("num_iters"))
      .def("vertices", [](igl::SLIMData &self) {
        // If we wrap self.V_o in an npe::move() then the instance 'self'
        // no longer owns that memory which is not what we want
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Vo;
        Vo = self.V_o;
        return npe::move(Vo);
      })
      .def("energy", [](igl::SLIMData &self) {
        return self.energy;
      });

  py::class_<igl::BBWData>(m, "BBW")
      .def(py::init([](int verbosity, int max_iter) {
             std::unique_ptr<igl::BBWData> bdata = std::make_unique<igl::BBWData>();
             bdata->verbosity = verbosity;
             bdata->active_set_params.max_iter = max_iter;
             return bdata;
           }),
           py::arg("verbosity") = 0, py::arg("max_iter") = 100)
      .def(
          "solve", [](igl::BBWData &self, Eigen::MatrixXd &V, Eigen::MatrixXi &F, Eigen::VectorXi &b, Eigen::MatrixXd &bc) {
            // Triangle mesh
            if (F.cols() == 3)
            {
              // Tet mesh
              if (V.cols() != 2 && V.cols() != 3)
              {
                throw pybind11::value_error("Invalid dimension. Argument V must have shape (#vertices, 2) or (#vertices, 3) for tri mesh inputs. You passed in V with shape (" + std::to_string(V.rows()) + std::string(", ") + std::to_string(V.cols()) + std::string(")"));
              }
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
            if (F.rows() <= 0)
            {
              throw pybind11::value_error("Invalid argument F has zero rows. Cannot have zero faces.");
            }
            if (V.rows() <= 0)
            {
              throw pybind11::value_error("Invalid argument V has zero rows. Cannot have zero faces.");
            }
            if (bc.rows() != b.size())
            {
              throw pybind11::value_error("Invalid argument bc.shape[0] must equal len(b) has zero rows. Cannot have zero faces.");
            }

            Eigen::MatrixXd W;
            igl::bbw(V, F, b, bc, self, W);
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> W_row_major = W;
            return npe::move(W_row_major);
          },
          py::arg("V"), py::arg("F"), py::arg("b"), py::arg("bc"));

  py::class_<igl::ShapeupData>(m, "shapeup")
      .def(py::init([](const Eigen::MatrixXd &P,
                       const Eigen::VectorXi &SC,
                       const Eigen::MatrixXi &S,
                       const Eigen::MatrixXi &E,
                       const Eigen::VectorXi &b,
                       const Eigen::VectorXd &wShape,
                       const Eigen::VectorXd &wSmooth,
                       int maxIterations, double pTolerance) {
             assert_nonzero_rows(P, "P");
             assert_cols_equals(P, 3, "P");
             assert_rows_match(S, wShape, "S", "wShape");
             assert_rows_match(E, wSmooth, "E", "wSmooth");

             std::unique_ptr<igl::ShapeupData> sdata = std::make_unique<igl::ShapeupData>();
             bool ok = igl::shapeup_precomputation(P, SC, S, E, b, wShape, wSmooth, *sdata);
             if (!ok)
               throw pybind11::value_error("Problem with initialization");
             return sdata;
           }),
           py::arg("P"), py::arg("SC"), py::arg("S"), py::arg("E"), py::arg("b"), py::arg("wShape"), py::arg("wSmooth"), py::arg("maxIterations") = 50, py::arg("pTolerance") = 1e-6)
      .def(
          "solve", [](igl::ShapeupData &self, Eigen::MatrixXd bc, const Eigen::MatrixXd &P0, const std::string &local_projection, const bool quietIterations) {
            if (bc.size() == 3 && bc.rows() == 3)
              bc.transposeInPlace();
            assert_cols_equals(bc, 3, "bc");
            assert_cols_equals(P0, 3, "P0");

            if (local_projection == "identity_projection" && local_projection == "regular_face_projection")
            {
              std::cout << "Invalid local_projection " << local_projection << ", switching to default: regular_face_projection";
            }

            igl::shapeup_projection_function func = local_projection == "identity_projection" ? igl::shapeup_identity_projection : igl::shapeup_regular_face_projection;

            Eigen::MatrixXd P;
            igl::shapeup_solve(bc, func, P0, self, quietIterations, P);

            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> P_row_major = P;
            return npe::move(P_row_major);
          },
          py::arg("bc"), py::arg("P0"), py::arg("local_projection") = "regular_face_projection", py::arg("quietIterations") = true);
}
