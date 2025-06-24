#pragma once
#include <type_traits>
#include <stddef.h>
#include <vector>

class MemoryArena {

public:
  MemoryArena(std::size_t PoolSize) {
    // set the pool size
    pool_.reserve(PoolSize);
  }

  template<typename T>
  T* create(T

private:
  std::vector<std::byte> pool_;
  std::vector<void*> freelist_;
};