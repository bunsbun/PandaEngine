cmake_minimum_required(VERSION 4.0.3)

project(PandaEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API ON)

add_subdirectory(PandaEngineCore)
add_subdirectory(PandaEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PandaEditor)