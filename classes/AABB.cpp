#include <igl/AABB.h>
#include <npe.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>
#include <variant>


namespace py = pybind11;
template <int DIM>
void init_AABB(py::module_ &m)
{
  using AABB_f64_DIM = igl::AABB<Eigen::MatrixXd,DIM>;
  py::class_<AABB_f64_DIM >(m, (std::string("AABB_f64_")+std::to_string(DIM)).c_str() )
    .def(py::init([]()
      {
        std::unique_ptr<AABB_f64_DIM> self = std::make_unique<AABB_f64_DIM>();
        return self;
      }))
    .def("init",[](AABB_f64_DIM & self, const Eigen::MatrixXd & V, const Eigen::MatrixXi & F)
      {
        self.init(V,F);
      },
      py::arg("V"), py::arg("F"))
    .def("squared_distance",[](
          AABB_f64_DIM & self, 
          const Eigen::MatrixXd & V, 
          const Eigen::MatrixXi & F,
          const Eigen::MatrixXd & P,
          const bool return_index = false,
          const bool return_closest_point = false) ->
        std::variant<py::object,std::list<py::object> >
      {
        Eigen::VectorXd sqrD; 
        Eigen::VectorXi I;
        Eigen::MatrixXd C;
        self.squared_distance(V,F,P,sqrD,I,C);
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
