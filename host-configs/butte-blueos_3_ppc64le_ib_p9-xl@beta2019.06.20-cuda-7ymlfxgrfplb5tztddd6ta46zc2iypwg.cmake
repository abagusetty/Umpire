###################
# Generated host-config - Edit at own risk!
###################
# Copyright (c) 2020, Lawrence Livermore National Security, LLC and
# other Umpire Project Developers. See the top-level LICENSE file for
# details.
#
# SPDX-License-Identifier: (BSD-3-Clause) 
###################

#------------------
# SYS_TYPE: blueos_3_ppc64le_ib_p9
# Compiler Spec: xl@beta2019.06.20
# CMake executable path: /usr/tce/packages/cmake/cmake-3.14.5/bin/cmake
#------------------

#------------------
# Compilers
#------------------

set(CMAKE_C_COMPILER "/usr/tce/packages/xl/xl-beta-2019.06.20/bin/xlc" CACHE PATH "")

set(CMAKE_CXX_COMPILER "/usr/tce/packages/xl/xl-beta-2019.06.20/bin/xlc++" CACHE PATH "")

#------------------------------------------------------------------------------
# Cuda
#------------------------------------------------------------------------------

set(ENABLE_CUDA ON CACHE BOOL "")

set(CUDA_TOOLKIT_ROOT_DIR "/usr/tce/packages/cuda/cuda-10.1.168" CACHE PATH "")

set(CMAKE_CUDA_COMPILER "${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc" CACHE PATH "")

set(ENABLE_C ON CACHE BOOL "")

set(ENABLE_FORTRAN OFF CACHE BOOL "")

set(ENABLE_NUMA OFF CACHE BOOL "")

set(ENABLE_OPENMP OFF CACHE BOOL "")
