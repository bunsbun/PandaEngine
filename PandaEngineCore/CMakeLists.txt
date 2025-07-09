cmake_minimum_required(VERSION 4.0.3)

set(ENGINE_PROJECT_NAME PandaEngineCore)

project(${ENGINE_PROJECT_NAME} LANGUAGES CXX)

set(ENGINE_PUBLIC_INCLUDES
	# includes/PandaEngineCore/Application.hpp
	includes/PandaEngineCore/Log.hpp
)

# set(ENGINE_PRIVATE_INCLUDES
	# src/PandaEngineCore/Window.hpp

# )

# set(ENGINE_PRIVATE_SOURCES
	# src/PandaEngineCore/Application.cpp
	# src/PandaEngineCore/Window.cpp
# )

add_library(${ENGINE_PROJECT_NAME} STATIC 
			${ENGINE_PUBLIC_INCLUDES}
			${ENGINE_PRIVATE_INCLUDES}
			${ENGINE_PRIVATE_SOURCES}
			)
			
target_sources(${ENGINE_PROJECT_NAME}
    PRIVATE
        FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
            src/PandaEngineCore/Window.ixx
            src/PandaEngineCore/Application.ixx
)			
			
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)