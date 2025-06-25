#include <iostream>
#include <memory>
#include "memory_arena.hpp"
#include "tick.hpp"
#include "order.hpp"

std::ostream& operator<<(std::ostream& os, const Tick& tick) {
  os << tick.symbol_ << " " << tick.price_;
  return os;
}

int main() {

  auto arena = std::make_shared<MemoryArena>(10);

  auto orderPtr = arena->create<Order>(42, 10.5);

  std::shared_ptr<Order> sharedOrder(orderPtr, [arena](Order* ptr) {
    ptr->~Order();
    arena->destroy(ptr);
  });

  auto tickPtr =
      arena->create<Tick>("AAPL", 184.20); // i think this might be dangling but this is where my
                                           // knowledge gap might need to be filled
  {
    std::shared_ptr<Tick> sharedTick(tickPtr, [arena](Tick* ptr) {
      ptr->~Tick();
      arena->destroy(ptr);
    });
  }

  auto newTickPtr = arena->create<Tick>("AAPL", 10.01);

  std::shared_ptr<Tick> sharedTick(newTickPtr, [arena](Tick* ptr) {
    ptr->~Tick();
    arena->destroy(ptr);
  });

  return 0;
}

