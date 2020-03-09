project(testGaia)
add_subdirectory ("src")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} lib::gaia)
