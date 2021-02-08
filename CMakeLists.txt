cmake_minimum_required(VERSION 3.10.0)
project(FiveCChessEngine VERSION 0.1.0)

enable_testing()
find_package(GTest CONFIG REQUIRED)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(FiveCChessEngine ${sources})

target_include_directories(FiveCChessEngine  PUBLIC 
        ${PROJECT_SOURCE_DIR}/src)

string(REPLACE "-O2" "-OFast" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
string(REPLACE "-O2" "-OFast" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

add_executable(boardTests tests/boardtestmain.cpp tests/movegentests.cpp)
target_link_libraries(boardTests GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_include_directories(boardTests PUBLIC ${PROJECT_SOURCE_DIR}/src)
add_test(NAME boardTests COMMAND boardTests)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
