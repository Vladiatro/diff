SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test_bin)

AddTest(round_trip_test round_trip_test.cpp)
AddTest(maximum_match_creator_test diff_creators/maximum_match_creator_test.cpp)

FILE(COPY resources/old/1.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/old")
FILE(COPY resources/old/2.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/old")
FILE(COPY resources/old/from_empty.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/old")
FILE(COPY resources/old/to_empty.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/old")
FILE(COPY resources/new/1.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/new")
FILE(COPY resources/new/2.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/new")
FILE(COPY resources/new/from_empty.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/new")
FILE(COPY resources/new/to_empty.txt DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resources/new")