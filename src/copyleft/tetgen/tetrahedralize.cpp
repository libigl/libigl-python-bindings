// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Alec Jacobson
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <pybind11/stl.h>


#include <npe.h>
#include <common.h>
#include <typedefs.h>

#include <igl/copyleft/tetgen/tetrahedralize.h>

const char* ds_tetrahedralize = R"igl_Qu8mg5v7(
)igl_Qu8mg5v7";

npe_function(tetrahedralize)
npe_doc(ds_tetrahedralize)

npe_arg(V, dense_float, dense_double)
npe_default_arg(F, dense_int32, dense_int64, Eigen::MatrixXi(0,3))
npe_default_arg(H, npe_matches(V) ,pybind11::array())
npe_default_arg(switches, std::string, "Q")
npe_default_arg(return_adjacency_info, bool, false)
npe_default_arg(VM, npe_matches(F), pybind11::array())
npe_default_arg(FM, npe_matches(F), pybind11::array())
npe_default_arg( R, npe_matches(V), pybind11::array())
npe_begin_code()
const bool has_markers = VM.size() > 0 || FM.size() > 0;
const bool has_regions = R.size() > 0;
EigenDenseLike<npe_Matrix_V> TV;
EigenDenseLike<npe_Matrix_F> TT, TF, TN, FT;
Eigen::Matrix<npe_Scalar_F,Eigen::Dynamic,1> TR,PT,TM;

int num_regions;
igl::copyleft::tetgen::tetrahedralize(
  V,F,H,
  Eigen::Map<Eigen::Matrix<typename decltype(VM)::Scalar,Eigen::Dynamic,1>>(VM.data(),VM.size()),
  Eigen::Map<Eigen::Matrix<typename decltype(FM)::Scalar,Eigen::Dynamic,1>>(FM.data(),FM.size()),
  R,switches,TV,TT,TF,TM,TR,TN,PT,FT,num_regions);

auto ret = std::list<pybind11::object>({npe::move(TV), npe::move(TT), npe::move(TF)});

if(has_markers)
{
  ret.push_back(npe::move(TM));
}
if(has_regions)
{
  ret.push_back(npe::move(TR));
}
if(return_adjacency_info)
{
  ret.push_back(npe::move(TN));
  ret.push_back(npe::move(PT));
  ret.push_back(npe::move(FT));
}
if(has_regions)
{
  ret.push_back(pybind11::cast(num_regions));
}

return ret;

npe_end_code()

