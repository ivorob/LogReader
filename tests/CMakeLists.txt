CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (tests)

SET (CMAKE_CXX_STANDARD 11)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
SET (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
SET (SOURCES
        tests.cpp
        StackTest.cpp
        CLogReaderTest.cpp
        ${SRC_DIR}/CLogReader.cpp
        ${SRC_DIR}/LogFileViewImpl.cpp)

SET (HEADERS
        ${INCLUDE_DIR}/CLogReader.h
        ${INCLUDE_DIR}/LogReaderImpl.h
        ${INCLUDE_DIR}/LogFileViewImpl.h
        ${INCLUDE_DIR}/Stack.h)

INCLUDE_DIRECTORIES (. ${INCLUDE_DIR}/)

ADD_DEFINITIONS (-D_VARIADIC_MAX=10)

ADD_EXECUTABLE (tests ${SOURCES} ${HEADERS})
SET_TARGET_PROPERTIES (tests PROPERTIES COMPILE_FLAGS "/EHsc")

ADD_CUSTOM_COMMAND(
    TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_CURRENT_SOURCE_DIR}/test_data/logfile.txt
        ${CMAKE_CURRENT_BINARY_DIR}/test_data/logfile.txt)

ADD_SUBDIRECTORY (${CMAKE_CURRENT_SOURCE_DIR}/googletest/)

TARGET_LINK_LIBRARIES (tests gtest)

ADD_TEST (LogReaderTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
