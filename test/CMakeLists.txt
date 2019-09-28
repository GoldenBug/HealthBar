add_executable(goldenbug_healthbar_tests tests.cpp)
target_link_libraries(goldenbug_healthbar_tests goldenbug_healthbar)
target_include_directories(goldenbug_healthbar_tests PRIVATE
        ${GOLDENBUG_HEALTHBAR_SOURCE_DIR}/include/HealthBar)
comp_target_features(goldenbug_healthbar_tests PUBLIC CPP11)

set(tests tests.cpp)

add_executable(goldenbug_healthbar_test ${tests})
comp_target_features(goldenbug_healthbar_test PUBLIC CPP11)
target_link_libraries(goldenbug_healthbar_test goldenbug_healthbar)
target_include_directories(goldenbug_healthbar_test PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${HealthBar_SOURCE_DIR}/include/HealthBar)

add_test(NAME test COMMAND goldenbug_healthbar_test)