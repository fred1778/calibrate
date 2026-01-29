cmake_minimum_required(VERSION 3.5)
project(calibrate)
# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
find_package(nlohmann_json 3.12.0 REQUIRED)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_executable(calibrate calibrate.cpp DayModel.cpp DayModel.hh
        events.h
        events.cpp
        EventMaker.cpp
        EventMaker.h)
target_link_libraries(calibrate PRIVATE SDL3::SDL3 nlohmann_json::nlohmann_json)
set_target_properties(calibrate PROPERTIES LINKER_LANGUAGE CXX)
