To compile the libigl python bindings run from the main directory:
mkdir build && cd build
cmake ..
make -j <cores>

To run the tests execute:
make test (not verbose)
make CTEST_OUTPUT_ON_FAILURE=1 test (verbose)

