cmake_minimum_required(VERSION 3.16)
project(BallGame)
   
include(cmake/CPM.cmake)
   
# THANK YOU!
CPMAddPackage("gh:HerrNamenlos123/openframeworks#master")

set(SOURCE_FILES
    src/Button.cpp                
    src/ColoredBall.cpp
    src/main.cpp
    src/MainMenu.cpp
    src/Menu.cpp
    src/ofApp.cpp
    src/PauseMenu.cpp
    src/Shooter.cpp
)
   
add_executable(BallGame ${SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/" PREFIX "" FILES ${SOURCE_FILES})
   
target_compile_features(BallGame PUBLIC cxx_std_17)
set_target_properties(BallGame PROPERTIES CXX_EXTENSIONS OFF)
   
target_include_directories(BallGame PUBLIC include)
   
target_link_libraries(BallGame of::openframeworks of::ofxGui)
   
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin/$<IF:$<CONFIG:Debug>,debug,release>")
set_target_properties(BallGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")          
set_target_properties(BallGame PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${BIN_DIR}")         
of_copy_runtime_to_bin_dir_after_build(BallGame "${BIN_DIR}")                                  
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BallGame)      
   
# Copy data folder to bin directory after build
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/data")
    add_custom_command(TARGET BallGame POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/data" "${BIN_DIR}/data")
    endif()