cmake_minimum_required(VERSION 3.8)
project(diff)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main/PatchMaker.cpp main/PatchMaker.h main/wrappers/HashedString.cpp main/wrappers/HashedString.h main/wrappers/flagged.cpp main/wrappers/flagged.h main/patch_formats/PatchFormat.h main/diff_creators/DifferenceCreator.h main/diff_creators/MaximumMatchDifferenceCreator.cpp main/diff_creators/MaximumMatchDifferenceCreator.h main/macro.h main/patch_formats/UnifiedFormat.cpp main/patch_formats/UnifiedFormat.h main/io/LinesCopier.cpp main/io/LinesCopier.h test/tools.cpp)
add_executable(diff main/main.cpp ${SOURCE_FILES})
add_library(diff_l ${SOURCE_FILES})

include(cmake/dependencies.cmake)
include(cmake/functions.cmake)

link_directories(${PROJECT_BINARY_DIR}/lib)

enable_testing()
add_subdirectory(test)