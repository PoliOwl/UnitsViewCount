
set(CMAKE_CXX_STANDARD 14)

add_executable(unitsViewCount 
    ${CMAKE_CURRENT_SOURCE_DIR}/testProj.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/radVector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/unit.cpp)
target_link_libraries(unitsViewCount
    pthread)

target_include_directories(unitsViewCount
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)