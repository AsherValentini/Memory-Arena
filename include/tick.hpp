#pragma once

#include <string>

struct Tick {
  std::string symbol_;
  float price_;
  Tick(const std::string& symbol, const float& price) : symbol_(symbol), price_(price) {}
};