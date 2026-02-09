cmake_minimum_required(VERSION 3.10)

project(SiemensCruiseControl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra -Wpedantic)
#--------------------
#finding Gtest package
#---------------------
find_package(GTest REQUIRED)

#---------------------
#production library
#---------------------
add_library(cruise_control
    src/CruiseControl.cpp
    src/CruiseManager.cpp
)

target_include_directories(cruise_control PUBLIC src)


#---------------------
#test executables
#---------------------
add_executable(cruise_tests
    tests/test_cruise.cpp)

target_link_libraries(cruise_tests
    cruise_control
    GTest::GTest
    GTest::gtest_main
    pthread
)

#---------------------------
#Enable testing
#---------------------------

enable_testing()
add_test(NAME CruiseControlTests COMMAND cruise_tests)
