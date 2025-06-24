The Memory Arena

Difficulty: Intermediate
Focus: Custom memory management, allocator patterns, object lifetime
Skill Tags: placement new, arena allocation, std::aligned_storage, memory reuse
Scenario:

You're building a real-time trading engine that must allocate thousands of small objects (e.g., orders, ticks, trades) per second. 
Dynamic allocation with new and delete is too slow and leads to fragmentation. You need to implement a memory arena that reuses memory blocks for speed.
Your Task:

Design a MemoryArena class that pre-allocates a fixed number of slots and allows for efficient object reuse via placement new. This arena should:

    Allow users to construct any type in-place using a create<T>(args...) method.

    Provide a destroy() method that returns the memory to the pool.

    Internally reuse released blocks — no new memory allocation after construction.

Example API usage:

MemoryArena arena(10); // Can store up to 10 objects

auto* p1 = arena.create<Order>(42, 10.5);  // Construct in-place
auto* p2 = arena.create<Tick>("AAPL", 184.20);

arena.destroy(p1); // Return memory to pool
auto* p3 = arena.create<Tick>("MSFT", 331.60); // Reuses slot

Constraints:

    No use of new/delete after arena construction.

    Support reuse: destroy() must enable create() to reuse freed blocks.

    Avoid memory leaks and dangling pointers.

You Should Test:

    That it reuses memory slots after destroy.

    That it works with mixed types (e.g. Order, Tick).

    That destructors are called when objects are destroyed.

    That memory doesn't leak.
