#include <igl/AABB.h>
#include <npe.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>
#include <variant>
#include <iostream>


namespace py = pybind11;

template <typename T> 
void check_c_contiguity(py::array_t<T> V, const std::string name = "arg")
{
  auto V_buf = V.request();
  if (V_buf.ndim != 2 || V_buf.strides[1] != sizeof(T)) {
      throw std::runtime_error(name+" must be C-contiguous with a 2D shape.");
  }
};
template <typename T> 
void check_f_contiguity(py::array_t<T> V, const std::string name = "arg")
{
  auto V_buf = V.request();
  if (V_buf.ndim != 2 || V_buf.strides[1] == sizeof(T)) {
      throw std::runtime_error(name+" must be F-contiguous (ColMajor) with a 2D shape.");
  }
};

template <int DIM>
void init_AABB(py::module_ &m)
{
  using namespace Eigen;
  using MatrixXdRowMajor = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>;
  using MatrixXiRowMajor = Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>;
  using MapMatrixXdRowMajor = Eigen::Map<const MatrixXdRowMajor>;
  using MapMatrixXiRowMajor = Eigen::Map<const MatrixXiRowMajor>;
  using MapMatrixXd = Eigen::Map<const Eigen::MatrixXd>;
  using MapMatrixXi = Eigen::Map<const Eigen::MatrixXi>;
  using DerivedV = MapMatrixXd;
  using AABB_f64_DIM = igl::AABB<DerivedV,DIM>;
  py::class_<AABB_f64_DIM >(m, (std::string("AABB_f64_")+std::to_string(DIM)).c_str() )
    .def(py::init([]()
      {
        std::unique_ptr<AABB_f64_DIM> self = std::make_unique<AABB_f64_DIM>();
        return self;
      }))
    .def("init", [](AABB_f64_DIM &self, py::array_t<double> V, py::array_t<int> F) 
      {
        auto V_buf = V.request();
        auto F_buf = F.request();

        if (V_buf.ndim != 2 || F_buf.ndim != 2) {
          throw std::runtime_error("Input matrices must be 2-dimensional.");
        }

        check_f_contiguity(V,"V");
        check_f_contiguity(F,"F");

        MapMatrixXd V_eigen(static_cast<double*>(V_buf.ptr), V_buf.shape[0], V_buf.shape[1]);
        MapMatrixXi F_eigen(static_cast<int*>(F_buf.ptr), F_buf.shape[0], F_buf.shape[1]);

        self.init(V_eigen, F_eigen);
      }, py::arg("V"), py::arg("F"))
  .def("squared_distance",[](
        AABB_f64_DIM & self, 
        py::array_t<double> V, 
        py::array_t<int> F,
        py::array_t<double> P,
        const bool return_index = false,
        const bool return_closest_point = false) ->
      std::variant<py::object,std::list<py::object> >
    {
      check_f_contiguity(V,"V");
      check_f_contiguity(F,"F");
      check_f_contiguity(P,"P");

      auto V_buf = V.request();
      auto F_buf = F.request();
      auto P_buf = P.request();
      MapMatrixXd V_eigen(static_cast<double*>(V_buf.ptr), V_buf.shape[0], V_buf.shape[1]);
      MapMatrixXi F_eigen(static_cast<int*>(F_buf.ptr), F_buf.shape[0], F_buf.shape[1]);
      MapMatrixXd P_eigen(static_cast<double*>(P_buf.ptr), P_buf.shape[0], P_buf.shape[1]);

      Eigen::VectorXd sqrD; 
      Eigen::VectorXi I;
      MatrixXd C;
      self.squared_distance(V_eigen,F_eigen,P_eigen,sqrD,I,C);
      if(return_index && return_closest_point)
      {
        return std::list<py::object>({npe::move(sqrD),npe::move(I),npe::move(C)});
      }else if(return_index)
      {
        return std::list<py::object>({npe::move(sqrD),npe::move(I)});
      }else if(return_closest_point)
      {
        return std::list<py::object>({npe::move(sqrD),npe::move(C)});
      }else
      {
        return npe::move(sqrD);
      }
    },
    py::arg("V"), 
    py::arg("F"), 
    py::arg("P"),
    py::arg("return_index")=false,
    py::arg("return_closest_point")=false
    )
  ;
}

template void init_AABB<2>(py::module_ &);
template void init_AABB<3>(py::module_ &);
