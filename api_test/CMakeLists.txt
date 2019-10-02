project(HealthBar_tests)

add_executable(tests_bin tests.cpp)
target_link_libraries(tests_bin libHealthBar)