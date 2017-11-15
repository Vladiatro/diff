cmake_minimum_required(VERSION 3.8)
project(diff)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main/main.cpp main/PatchMaker.cpp main/PatchMaker.h main/wrappers/HashedString.cpp main/wrappers/HashedString.h main/wrappers/flagged.cpp main/wrappers/flagged.h main/patch_formats/PatchFormat.h main/diff_creators/DifferenceCreator.h main/diff_creators/MaximumMatchDifferenceCreator.cpp main/diff_creators/MaximumMatchDifferenceCreator.h main/macro.h main/patch_formats/UnifiedFormat.cpp main/patch_formats/UnifiedFormat.h)
add_executable(diff ${SOURCE_FILES})