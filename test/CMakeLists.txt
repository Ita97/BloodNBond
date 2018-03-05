cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp DetectiveStatesTests.cpp DetectiveInventoriesTest.cpp FireWeaponTests.cpp StarTest.cpp)
add_executable(runGameTests ${TEST_SOURCE_FILES})
target_link_libraries(runGameTests gtest gtest_main core)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(runGameTests ${SFML_LIBRARIES})
endif()