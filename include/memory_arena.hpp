#pragma once
#include <type_traits>
#include <stddef.h>
#include <vector>
#include <optional>
#include <algorithm>
#include "tick.hpp"
#include "order.hpp"

class MemoryArena {

public:
  MemoryArena(std::size_t PoolSize) : capacity_(PoolSize) {
    // set the pool size
    pool_.reserve(PoolSize);
  }

  template <typename T, typename U, typename V>
  T* create(U arg1, V arg2) {
    // check capacity
    if (pool_.size() >= capacity_)
      throw std::bad_alloc();

    // check if we have free blocks
    if (freelist_.empty()) {
      void* raw = &pool_.emplace_back();
      new (raw) T(arg1, arg2); // i think this only works if the byte is trivially destructable...
      std::cout << "[MemoryArena]: object created at new address: " << raw << "\n";
      return reinterpret_cast<T*>(raw);
    } else {
      void* raw = freelist_.back();
      new (raw) T(arg1, arg2);
      std::cout << "[MemoryArena]: object created at old address: " << raw << "\n";
      return reinterpret_cast<T*>(raw);
    }
  }

  template <typename T>
  void destroy(T* objPtr) {
    freelist_.push_back(objPtr);
    std::cout << "[MemoryArena]: object destroyed at address: " << objPtr << "\n";
  }

private:
  static constexpr std::size_t MaxObjectSize = std::max(sizeof(Order), sizeof(Tick));
  static constexpr std::size_t MaxObjectAlign = std::max(alignof(Order), alignof(Tick));
  std::vector<std::aligned_storage_t<MaxObjectSize, MaxObjectAlign>> pool_;
  std::vector<void*> freelist_;
  std::size_t capacity_;
};