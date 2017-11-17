include(ExternalProject)
set(EP_PREFIX "${PROJECT_SOURCE_DIR}/external")
set_directory_properties(PROPERTIES
        EP_PREFIX ${EP_PREFIX}
        )

if (TESTING)
    ExternalProject_Add(google_test
            GIT_REPOSITORY "https://github.com/google/googletest.git"
            CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -Dgtest_force_shared_crt=ON
            -Dgtest_disable_pthreads=OFF
            INSTALL_COMMAND "" # remove install step
            UPDATE_COMMAND "" # remove update step
            TEST_COMMAND "" # remove test step
            )
    ExternalProject_Get_Property(google_test source_dir binary_dir)
    set(gtest_SOURCE_DIR ${source_dir})
    set(gtest_BINARY_DIR ${binary_dir})

    add_library(gtest STATIC IMPORTED)
    file(MAKE_DIRECTORY ${gtest_SOURCE_DIR}/googletest/include)

    set_target_properties(gtest
            PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${gtest_SOURCE_DIR}/googletest/include
            IMPORTED_LINK_INTERFACE_LIBRARIES "pthread;${gtest_BINARY_DIR}/googlemock/gtest/libgtest_main.a"
            IMPORTED_LOCATION ${gtest_BINARY_DIR}/googlemock/gtest/libgtest.a
            )

    add_library(gmock STATIC IMPORTED)
    file(MAKE_DIRECTORY ${gtest_SOURCE_DIR}/googlemock/include)

    set_target_properties(gmock
            PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${gtest_SOURCE_DIR}/googlemock/include
            IMPORTED_LINK_INTERFACE_LIBRARIES "pthread;${gtest_BINARY_DIR}/googlemock/libgmock_main.a"
            IMPORTED_LOCATION ${gtest_BINARY_DIR}/googlemock/libgmock.a
            )

    add_dependencies(gtest google_test)
    add_dependencies(gmock google_test)
endif ()