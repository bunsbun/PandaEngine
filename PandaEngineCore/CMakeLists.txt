cmake_minimum_required(VERSION 4.0.3)

set(ENGINE_PROJECT_NAME PandaEngineCore)

project(${ENGINE_PROJECT_NAME} LANGUAGES CXX)

add_library(${ENGINE_PROJECT_NAME} STATIC 
			src/PandaEngineCore/Utils/test.cpp
			includes/PandaEngineCore/Utils/test.hpp
			)
			
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)