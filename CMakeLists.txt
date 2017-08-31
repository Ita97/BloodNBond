cmake_minimum_required(VERSION 3.4)
project(BloodBond)
set(CMAKE_CXX_STANDARD 11)

# Define sources and executable

add_executable(BloodBond main.cpp Window.cpp Window.h Game.cpp Game.h)



# Detect and add SFML
set(CMAKE_MODULE_PATH  "/home/ita/CLionProjects/BloodBond/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(BloodBond ${SFML_LIBRARIES})
endif()
