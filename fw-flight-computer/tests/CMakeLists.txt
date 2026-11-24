cmake_minimum_required(VERSION 3.16)
project(CmfsHostTests LANGUAGES CXX)

find_package(GTest CONFIG REQUIRED)
enable_testing()

add_executable(FlightStateMachineTest
    FlightStateMachineTest.cpp
    ../src/core/FlightStateMachine.cpp
)
target_include_directories(FlightStateMachineTest PRIVATE ../src)
target_compile_features(FlightStateMachineTest PRIVATE cxx_std_17)
target_link_libraries(FlightStateMachineTest PRIVATE GTest::gtest_main)

add_test(NAME FlightStateMachineTest COMMAND FlightStateMachineTest)
