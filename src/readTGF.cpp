// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2023 Teseo Schneider
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include <npe.h>
#include <typedefs.h>



#include <igl/readTGF.h>

const char *ds_read_tgf = R"igl_Qu8mg5v7(
Read a graph from a .tgf file

Parameters
----------
filename  .tgf file name

Returns
-------

    V  # vertices by 3 list of vertex positions
    E  # edges by 2 list of edge indices
    P  # point-handles list of point handle indices
    BE # bone-edges by 2 list of bone-edge indices
    CE # cage-edges by 2 list of cage-edge indices
    PE # pseudo-edges by 2 list of pseudo-edge indices

See also
--------


Notes
-----
Assumes that graph vertices are 3 dimensional

Examples
--------
  V,E,P,BE,CE,PE = igl.read_tgf(filename)

)igl_Qu8mg5v7";

npe_function(read_tgf)
npe_doc(ds_read_tgf)

npe_arg(tgf_filename, std::string)


npe_begin_code()

  Eigen::MatrixXd v;
  Eigen::MatrixXi e;
  Eigen::VectorXi p;
  Eigen::MatrixXi be;
  Eigen::MatrixXi ce;
  Eigen::MatrixXi pe;
  bool ok = igl::readTGF(tgf_filename, v, e, p, be, ce, pe);
  if (!ok)
  {
    throw std::invalid_argument("File '" + tgf_filename + "' not found.");
  }

  EigenDenseFloat v_row_major = v.template cast<typename EigenDenseFloat::Scalar>();
  EigenDenseInt e_row_major = e.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseInt p_row_major = p.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseInt be_row_major = be.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseInt ce_row_major = ce.template cast<typename EigenDenseInt::Scalar>();
  EigenDenseInt pe_row_major = pe.template cast<typename EigenDenseInt::Scalar>();

  return std::make_tuple(npe::move(v_row_major), npe::move(e_row_major), npe::move(p_row_major), npe::move(be_row_major), npe::move(ce_row_major), npe::move(pe_row_major));

npe_end_code()
