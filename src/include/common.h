#include <pybind11/pybind11.h>

#ifdef WIN32 // FIXME: at the end remove me at the end, usefull only fo appveyour debug
#ifdef _DEBUG
  #undef _DEBUG
  #include <python.h>
  #define _DEBUG
#else
  #include <python.h>
#endif
#endif

template <typename T>
void assert_nonzero_rows(const T& mat, std::string name) {
    if (mat.rows() == 0) {
        throw pybind11::value_error("Parameter " + name + " has shape 0 at dimension 0. Expected " + name + ".shape[0] > 0.");
    }
}

template <typename T>
void assert_cols_equals(const T& mat, int cols, std::string name) {
    if (mat.cols() != cols) {
        throw pybind11::value_error("Parameter " + name + " has invalid shape at dimension 1, expected " + name + ".shape[1] = " + std::to_string(cols) +
                                    " but got " + name + ".shape = [" + std::to_string(mat.rows()) + ", " + std::to_string(mat.cols()) + "]");
    }
}

template <typename T>
void assert_rows_equals(const T& mat, int rows, std::string name) {
    if (mat.rows() != rows) {
        throw pybind11::value_error("Parameter " + name + " has invalid shape at dimension 0, expected " + name + ".shape[0] = " + std::to_string(rows) +
                                    " but got " + name + ".shape = [" + std::to_string(mat.rows()) + ", " + std::to_string(mat.cols()) + "]");
    }
}

template <typename T>
void assert_size_equals(const T& mat, int size, std::string name) {
    if (mat.size() != size) {
        throw pybind11::value_error("Parameter " + name + " has invalid size expected " + name + ".size() = " + std::to_string(size) +
                                    " but got " + name + ".shape = [" + std::to_string(mat.rows()) + ", " + std::to_string(mat.cols()) + "]");
    }
}

template <typename T>
void assert_shape_equals(const T& mat, int rows, int cols, std::string name) {
    if (mat.rows() != rows || mat.cols() != cols) {
        throw pybind11::value_error("Parameter " + name + " has invalid shape, expected " + name + ".shape = [" + std::to_string(rows) + ", " + std::to_string(cols) +
                                    "] but got " + name + ".shape = [" + std::to_string(mat.rows()) + ", " + std::to_string(mat.cols()) + "]");
    }
}


template <typename T1, typename T2>
void assert_shapes_match(const T1& mat1, const T2& mat2, std::string name1, std::string name2) {
    if (mat1.rows() != mat2.rows() || mat1.cols() != mat2.cols()) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2.rows()) + ", " + std::to_string(mat2.cols()) + "]");
    }
}

template <typename T1, typename T2>
void assert_rows_match(const T1& mat1, const T2& mat2, std::string name1, std::string name2) {
    if (mat1.rows() != mat2.rows()) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape at dimension 0 (rows) but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2.rows()) + ", " + std::to_string(mat2.cols()) + "]");
    }
}

template <typename T1, typename T2>
void assert_cols_match(const T1& mat1, const T2& mat2, std::string name1, std::string name2) {
    if (mat1.cols() != mat2.cols()) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape at dimension 1 (cols) but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2.rows()) + ", " + std::to_string(mat2.cols()) + "]");
    }
}



template <typename T1>
void assert_rows_match(const T1& mat1, int mat2_rows, int mat2_cols, std::string name1, std::string name2) {
    if (mat1.rows() != mat2_rows) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape at dimension 0 (rows) but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2_rows) + ", " + std::to_string(mat2_cols) + "]");
    }
}

template <typename T1>
void assert_cols_match(const T1& mat1, int mat2_rows, int mat2_cols, std::string name1, std::string name2) {
    if (mat1.cols() != mat2_cols) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape at dimension 1 (cols) but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2_rows) + ", " + std::to_string(mat2_cols) + "]");
    }
}

template <typename T1>
void assert_shapes_match(const T1& mat1, int mat2_rows, int mat2_cols, std::string name1, std::string name2) {
    if (mat1.rows() != mat2_rows || mat1.cols() != mat2_cols) {
        throw pybind11::value_error("Parameters " + name1 + " and " + name2 + " must have the same shape but got " +
                                    name1 + ".shape = [" + std::to_string(mat1.rows()) + ", " + std::to_string(mat1.cols()) + "] and " +
                                    name2 + ".shape = [" + std::to_string(mat2_rows) + ", " + std::to_string(mat2_cols) + "]");
    }
}


template <typename TF>
void assert_valid_tet_or_tri_mesh_faces(const TF& f, std::string f_name="f") {
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (f.cols() != 3 && f.cols() != 4) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " must have shape [#faces, 3] (for a triangle mesh) or [#faces, 4] (for a tet mesh) " +
                                    "but got " + f_name + ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TF>
void assert_valid_simplex_idxs(const TF& f, std::string f_name="f") {
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid simplex indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (f.cols() < 2) {
        throw pybind11::value_error("Invalid simplex indices, " + f_name + " must have shape [#faces, #edges] with #edges >= 2 for a valid simplex." +
                                    "but got " + f_name + ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TF>
void assert_valid_tri_mesh_faces(const TF &f, std::string f_name = "f")
{
    if (f.rows() <= 0)
    {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (f.cols() != 3)
    {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " must have shape [#faces, 3] " +
                                    "but got " + f_name + ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_tet_or_tri_mesh(const TV& v, const TF& f, std::string v_name="v", std::string f_name="f") {
    if (v.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 3) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (f.cols() != 3 && f.cols() != 4) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " must have shape [#faces, 3] (for a triangle mesh) or [#faces, 4] (for a tet mesh) " +
                                    "but got " + f_name + ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_tet_or_tri_mesh_23d(const TV &v, const TF &f, std::string v_name = "v", std::string f_name = "f")
{
    if (v.rows() <= 0)
    {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0)
    {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 3 && v.cols() != 2)
    {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] or [#vertices, 2] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }

    if (f.cols() != 3 && f.cols() != 4)
    {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " must have shape [#faces, 3] (for a triangle mesh) or [#faces, 4] (for a tet mesh) " +
                                    "but got " + f_name + ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }

    if (v.cols() == 2 && f.cols() == 4)
    {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] (and not 2) to be compatible with " + f_name + " which are tets, shape [#faces, 4]");
    }
}

template <typename TV, typename TF>
void assert_valid_3d_tri_mesh(const TV& v, const TF& f, std::string v_name="v", std::string f_name="f") {
    if (v.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 3) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (f.cols() != 3) {
        throw pybind11::value_error("Invalid mesh faces, " + f_name + " must have shape [#faces, 3] but got " + f_name +
                                    ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_3d_quad_mesh(const TV& v, const TF& f, std::string v_name="v", std::string f_name="f") {
    if (v.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 3) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (f.cols() != 4) {
        throw pybind11::value_error("Invalid mesh faces, " + f_name + " must have shape [#faces, 4] but got " + f_name +
                                    ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_23d_tri_mesh(const TV &v, const TF &f, std::string v_name = "v", std::string f_name = "f")
{
    if (v.rows() <= 0)
    {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0)
    {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 3 && v.cols() != 2)
    {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] or [#vertices, 2] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (f.cols() != 3)
    {
        throw pybind11::value_error("Invalid mesh faces, " + f_name + " must have shape [#faces, 3] but got " + f_name +
                                    ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_tet_mesh(const TV& v, const TF& t, std::string v_name="v", std::string t_name="t") {
    if (v.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (t.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + t_name + " has zero rows (" + t_name + ".shape = [" +
                                    std::to_string(t.rows()) + ", " + std::to_string(t.cols()) + "]) ");
    }

    if (v.cols() != 3) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 3] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (t.cols() != 4) {
        throw pybind11::value_error("Invalid mesh tets, " + t_name + " must have shape [#tets, 4] but got " + t_name +
                                    ".shape = [" + std::to_string(t.rows()) + ", " + std::to_string(t.cols()) + "]");
    }
}

template <typename TV, typename TF>
void assert_valid_2d_tri_mesh(const TV& v, const TF& f, std::string v_name="v", std::string f_name="f") {
    if (v.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " has zero rows (" + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]) ");
    }
    if (f.rows() <= 0) {
        throw pybind11::value_error("Invalid mesh indices, " + f_name + " has zero rows (" + f_name + ".shape = [" +
                                    std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]) ");
    }

    if (v.cols() != 2) {
        throw pybind11::value_error("Invalid mesh vertices, " + v_name + " must have shape [#vertices, 2] but got " + v_name +
                                    ".shape = [" + std::to_string(v.rows()) + ", " + std::to_string(v.cols()) + "]");
    }
    if (f.cols() != 3) {
        throw pybind11::value_error("Invalid mesh faces, " + f_name + " must have shape [#faces, 3] but got " + f_name +
                                    ".shape = [" + std::to_string(f.rows()) + ", " + std::to_string(f.cols()) + "]");
    }
}

template <typename TV>
void assert_valid_bone_transforms(const TV& t, std::string t_name="t") {
    if (t.rows() <= 0) {
        throw pybind11::value_error("Invalid number of transforms, " + t_name + " has zero rows (" + t_name +
                                    ".shape = [" + std::to_string(t.rows()) + ", " + std::to_string(t.cols()) + "]) ");
    }
    
    if (t.cols() != 3) {
        throw pybind11::value_error("Invalid number of cols in transforms, " + t_name + " must have shape [#bones * 4, 3] but got " + t_name +
                                    ".shape = [" + std::to_string(t.rows()) + ", " + std::to_string(t.cols()) + "]");
    }

    if (t.rows() % 4 != 0) {
        throw pybind11::value_error("Invalid number of rows in transforms, " + t_name + " must have shape [#bones * 4, 3] but got " + t_name +
                                    ".shape = [" + std::to_string(t.rows()) + ", " + std::to_string(t.cols()) + "].");   
    }
}
