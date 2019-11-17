cmake_minimum_required(VERSION 3.5)

add_custom_target(check)
set_target_properties(check PROPERTIES FOLDER tests)

macro(add_one_test test)
    add_executable(${test} "${test}.cpp")
    target_link_libraries(${test} PUBLIC ${PROJECT_NAME})
    set_target_properties(${test} PROPERTIES FOLDER tests)
    add_custom_command(TARGET check POST_BUILD COMMAND ${test})
    add_dependencies(check ${test})
endmacro()

add_one_test(CLI11_test)
add_one_test(easy_profiler_test)
add_one_test(SimpleIni_test)
add_one_test(catch_010-TestCase)
add_one_test(spdlog_test)
add_one_test(xmltest)

# Copy test resources and create test output directory
add_custom_command(TARGET xmltest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources/out
    COMMENT "Configuring xmltest resources directory: ${CMAKE_CURRENT_BINARY_DIR}/resources"
)