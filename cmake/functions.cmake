# Creates test "test_name", with "SOURCES" (use string as second argument)
function(addtest test_name SOURCES)
    add_executable(${test_name} ${SOURCES})
    target_link_libraries(${test_name} diff_l gtest gmock)
    target_include_directories(${test_name} PUBLIC ${PROJECT_SOURCE_DIR}/test ${PROJECT_SOURCE_DIR})
    add_test(
            NAME ${test_name}
            COMMAND $<TARGET_FILE:${test_name}>
    )
endfunction()