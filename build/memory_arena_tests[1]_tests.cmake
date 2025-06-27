add_test([=[DummyTest.JustRuns]=]  /home/asher/cpp-projects/Memory-Arena/build/bin/memory_arena_tests [==[--gtest_filter=DummyTest.JustRuns]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DummyTest.JustRuns]=]  PROPERTIES WORKING_DIRECTORY /home/asher/cpp-projects/Memory-Arena/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  memory_arena_tests_TESTS DummyTest.JustRuns)
