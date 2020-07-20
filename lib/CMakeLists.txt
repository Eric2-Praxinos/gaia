project(libGaia)
add_subdirectory ("src")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#not working with SHARED (investigate if you need it)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_library(lib::gaia ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
