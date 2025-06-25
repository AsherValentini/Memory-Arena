#pragma once
#include <cstdint>
struct Order {
  std::uint64_t amount_;
  float price_;
  Order(std::uint64_t amount, float price) : amount_(amount), price_(price) {}
};