//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-20, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_aligned_allocation_INL
#define UMPIRE_aligned_allocation_INL

#include "umpire/util/allocation_statistics.hpp"
#include "umpire/util/Macros.hpp"

#include <tuple>

namespace umpire {
namespace util {

inline std::size_t AlignedAllocation::round_up(std::size_t size)
{
    return size + (m_alignment - 1) - (size - 1) % m_alignment;
}

inline void AlignedAllocation::align_create(std::size_t& size, void*& ptr)
{
    void* buffer{ptr};
    std::size_t buffer_size{size};

    uintptr_t alignment{ m_alignment - 1 };
    uintptr_t mask{ m_mask };
    uintptr_t cptr{ reinterpret_cast<uintptr_t>(ptr) };

    void *aligned_ptr{ reinterpret_cast<void*>((cptr + alignment) & mask) };

    std::size_t aligned_size{buffer_size - (reinterpret_cast<char*>(aligned_ptr) - reinterpret_cast<char*>(buffer))};

    base_pointer_map[aligned_ptr] = std::make_tuple(size, buffer);

    size = aligned_size;
    ptr = aligned_ptr;
}

inline void AlignedAllocation::align_destroy(void* ptr, std::size_t& osize, void*& obuffer)
{
    std::tie(osize, obuffer) = base_pointer_map[ptr];

    base_pointer_map.erase(ptr);
}

} // namespace umpire
} // namespace util
#endif // UMPIRE_aligned_allocation_INL
