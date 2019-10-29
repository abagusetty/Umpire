//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-19, Lawrence Livermore National Security, LLC and Umpire
// project contributors. See the COPYRIGHT file for details.
//
// SPDX-License-Identifier: (MIT)
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_PoolMap_HPP
#define UMPIRE_PoolMap_HPP

#include "umpire/strategy/AllocationStrategy.hpp"

#include "umpire/util/MemoryMap.hpp"

#include <unordered_map>
#include <map>
#include <tuple>

namespace umpire {

class Allocator;

namespace util {

class FixedMallocPool;

}

namespace strategy {

class Pool : 
  public AllocationStrategy
{
  public:
    using Pointer = void*;

    Pool(
        const std::string& name,
        int id,
        Allocator allocator,
        const std::size_t initial_alloc_size = (512 * 1024 * 1024),
        const std::size_t min_alloc_size = (1 * 1024 * 1024),
        const int align_bytes = 16) noexcept;

    ~Pool();

    Pool(const Pool&) = delete;

    void* allocate(std::size_t bytes) override;
    void deallocate(void* ptr) override;
    void release() override;

    std::size_t getCurrentSize() const noexcept override;
    std::size_t getActualSize() const noexcept override;
    std::size_t getHighWatermark() const noexcept override;

    Platform getPlatform() noexcept override;
  private:
    struct Chunk {
      Chunk(void* ptr, std::size_t s, std::size_t cs) :
        data{ptr}, size{s}, chunk_size{cs} {}

      void* data{nullptr};
      std::size_t size{0};
      std::size_t chunk_size{0};
      bool free{true};
      Chunk* prev{nullptr};
      Chunk* next{nullptr};
      std::multimap<std::size_t, Chunk*>::iterator size_map_it;
    };

    using PointerMap = std::map<void*, Chunk*>;
    using SizeMap = std::multimap<std::size_t, Chunk*>;

    PointerMap m_pointer_map;
    SizeMap m_size_map;

    util::FixedMallocPool m_chunk_pool;

    strategy::AllocationStrategy* m_allocator;

    const std::size_t m_initial_alloc_bytes;
    const std::size_t m_min_alloc_bytes;
    const int m_align_bytes;

    std::size_t m_curr_bytes{0};
    std::size_t m_actual_bytes{0};
    std::size_t m_highwatermark{0};

};

} // end of namespace strategy
} // end namespace umpire

#endif // UMPIRE_Pool_HPP
