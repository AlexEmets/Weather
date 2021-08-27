cmake_minimum_required(VERSION 3.2)

project(Weather)

set(HEADERS_DIRECTORY src/headers)
set(SOURCE_DIRECTORY src/sources)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system thread program_options REQUIRED)

set(PROJECT_SOURCES
    ${SOURCE_DIRECTORY}/application.cpp
    ${SOURCE_DIRECTORY}/client.cpp
    ${SOURCE_DIRECTORY}/network.cpp
    ${SOURCE_DIRECTORY}/main.cpp
)

set(PROJECT_HEADERS
        ${HEADERS_DIRECTORY}/application.hpp
        ${HEADERS_DIRECTORY}/client.hpp
        ${HEADERS_DIRECTORY}/network.hpp
)
add_executable(Weather ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(Weather PUBLIC ${HEADERS_DIRECTORY})
target_include_directories(Weather PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Weather ${Boost_LIBRARIES})
