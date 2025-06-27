Create a placeholder test file

If you haven’t written the test yet, just do:

```bash
mkdir -p tests
touch tests/memory_arena_test.cpp
```

Then add this content to avoid compilation errors:

\#include <gtest/gtest.h>

TEST(DummyTest, JustRuns) {
    EXPECT_EQ(1, 1);
}

After that:

cd build
cmake ..
make
ctest  # runs the dummy test


# 1. Test Setup: GTest 101

A Google Test unit looks like this:

\#include <gtest/gtest.h>

TEST(TestSuiteName, TestCaseName) {
  // Arrange
  // Act
  // Assert (EXPECT_ / ASSERT_)
}

    EXPECT_*: soft checks (test continues even if it fails)

    ASSERT_*: hard checks (test aborts on failure)

We'll write 3 test cases:

    Fresh allocation

    Object reuse after destroy

    Object destruction tracking

# 2. Test File: tests/memory_arena_test.cpp

\#include <gtest/gtest.h>
\#include "memory_arena.hpp"
\#include "tick.hpp"
\#include "order.hpp"

// Dummy types with logging so we can see construction/destruction
struct Dummy {
    int x;
    double y;
    Dummy(int a, double b) : x(a), y(b) {}
};

// Test 1: fresh allocation (no reuse, no destruction yet)
TEST(MemoryArenaTest, FreshAllocationWorks) {
    MemoryArena arena(2);

    Dummy* d1 = arena.create<Dummy>(42, 3.14);
    ASSERT_NE(d1, nullptr);
    EXPECT_EQ(d1->x, 42);
    EXPECT_DOUBLE_EQ(d1->y, 3.14);
}

// Test 2: reuse from freelist
TEST(MemoryArenaTest, ReuseFreelistOnDestroy) {
    MemoryArena arena(2);

    Dummy* d1 = arena.create<Dummy>(1, 1.1);
    Dummy* d2 = arena.create<Dummy>(2, 2.2);

    arena.destroy(d1);  // d1 now in freelist

    Dummy* d3 = arena.create<Dummy>(3, 3.3);  // should reuse d1's slot
    ASSERT_EQ(d3, d1);  // pointer must be the same

    EXPECT_EQ(d3->x, 3);
    EXPECT_DOUBLE_EQ(d3->y, 3.3);
}

// Test 3: destruction tracking (pointer ends up in freelist)
TEST(MemoryArenaTest, DestructionAddsToFreelist) {
    MemoryArena arena(2);

    Dummy* d1 = arena.create<Dummy>(10, 10.1);
    arena.destroy(d1);

    // Expect no exception when reusing
    EXPECT_NO_THROW({
        Dummy* d2 = arena.create<Dummy>(20, 20.2);
        EXPECT_EQ(d2, d1);  // Should reuse same memory
    });
}

# 3. Build and Run

From your root directory:

cd build
cmake ..
make
ctest

Or if you want verbose output:

./bin/memory_arena_tests

🧠 Recap

    Test 1 checks fresh creation.

    Test 2 checks freelist reuse (after destruction).

    Test 3 checks that destruction doesn’t crash and reuses properly.

Let me know if you want to also:

    Check behavior when exceeding pool capacity (i.e. throw std::bad_alloc)

    Log allocation addresses with std::ostringstream for deeper inspection

    Use mocks/spies to track Tick or Order creation/destruction effects

