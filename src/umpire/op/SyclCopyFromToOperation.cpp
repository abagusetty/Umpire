//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#include "umpire/op/SyclCopyFromToOperation.hpp"

#include <CL/sycl.hpp>

#include "umpire/strategy/AllocationStrategy.hpp"
#include "umpire/util/Macros.hpp"

namespace umpire {
namespace op {

void SyclCopyFromToOperation::transform(
    void* src_ptr,
    void** dst_ptr,
    util::AllocationRecord* src_allocation,
    util::AllocationRecord* UMPIRE_UNUSED_ARG(dst_allocation),
    std::size_t length)
{
  cl::sycl::device sycl_device(dst_allocation->strategy->getTraits().deviceID);
  cl::sycl::queue sycl_queue(sycl_device);
  sycl_queue.submit([&](cl::sycl::handler& cgh)
  {
    cgh.memcpy(*dst_ptr, src_ptr, length);
  });
  sycl_queue.wait_and_throw();

  UMPIRE_RECORD_STATISTIC(
      "SyclCopyFromToOperation",
      "src_ptr", reinterpret_cast<uintptr_t>(src_ptr),
      "dst_ptr", reinterpret_cast<uintptr_t>(dst_ptr),
      "size", length,
      "event", "copy");
}

} // end of namespace op
} // end of namespace umpire