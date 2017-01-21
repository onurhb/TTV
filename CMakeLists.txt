#------------------------------------------------------------------------------
#░░▄░░░▄░▄▄▄▄░░░░░░░░░░░░░░░
#░░█▀▄▀█░█▄▄░░░░░░░░░░░░░░░░
#░░█░░░█░█▄▄▄░░░░░░░░░░░░░░░
#░░░░░░░░░░░░░░░░░░░░░░░░░░░
#░▄▄▄░▄░░░▄░░▄▄▄░▄▄▄▄▄░░▄▄▄░
#█░░░░█░░░█░█░░░░░░█░░░█░░░█
#█░▀█░█░░░█░░▀▀▄░░░█░░░█▀▀▀█
#░▀▀▀░░▀▀▀░░▄▄▄▀░░░▀░░░▀░░░▀
#------------------------------------------------------------------------------
project(Project)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
SET(GCC_COVERAGE_LINK_FLAGS "-ldl")
#------------------------------------------------------------------------------
#Path to CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
#Path to dependencies
set(DEPENDENCIES_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)
#Path to glfw library
set(GLFW_LOCATION ${DEPENDENCIES_LOCATION}/glfw)
#Path to curl library
set(CURL_LOCATION ${DEPENDENCIES_LOCATION}/curl)
#Path to GLEW
set(GLEW_LOCATION ${DEPENDENCIES_LOCATION}/glew)
#Path to ffmpeg
set(LIBVLC_LOCATION ${DEPENDENCIES_LOCATION}/libvlc)
#------------------------------------------------------------------------------
include_directories(
        ${DEPENDENCIES_LOCATION}/glm/glm
        ${DEPENDENCIES_LOCATION}/curl/include
        ${DEPENDENCIES_LOCATION}/nanovg
        ${DEPENDENCIES_LOCATION}/json
)

#------------------------------------------------------------------------------
set(GLAD_SOURCE_FILES
        ${DEPENDENCIES_LOCATION}/glad/src/glad.c)

set(NANOVG_SOURCE_FILES
        ${DEPENDENCIES_LOCATION}/nanovg/nanovg.c)

set(SOURCE_FILES
        Source/main.cpp
        Source/Utils/Thread.h
        Source/Graphics/Texture.h
        Source/Utils/FileDialog.h
        Source/Utils/HTTP.cpp Source/Utils/HTTP.h
        Source/Application.cpp Source/Application.h
        Source/Graphics/Shader.cpp Source/Graphics/Shader.h
        Source/Graphics/Window.cpp Source/Graphics/Window.h
        Source/Graphics/UserInterface.cpp Source/Graphics/UserInterface.h
        Source/config.h Source/Stream/Stream.cpp Source/Stream/Stream.h)
#------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${NANOVG_SOURCE_FILES})
#------------------------------------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(GLFW REQUIRED glfw3)
find_package(CURL REQUIRED)
find_package(LIBVLC REQUIRED)
find_package(GLEW REQUIRED)

#------------------------------------------------------------------------------
if (OPENGL_FOUND)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
    message("-- OPENGL library was found")
endif (OPENGL_FOUND)

if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
    message("-- GLFW library was found")
endif ()

if (GLEW_FOUND)
    ADD_DEFINITIONS(-DGLEW_STATIC)
    include_directories(${GLEW_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY})
    message("-- GLEW library was found")
endif ()

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
    message("-- CURL library was found")
endif()

if (LIBVLC_FOUND)
    include_directories(${LIBVLC_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${LIBVLC_LIBRARIES})
    message("-- LIBVLC library was found")
endif ()
#------------------------------------------------------------------------------

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DEPENDENCIES_LOCATION}/GLFW/bin/glfw3.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Dependencies/CURL/bin
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Dependencies/libvlc/bin
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    #add_custom_command(
    #        TARGET ${PROJECT_NAME} POST_BUILD
    #        COMMAND ${CMAKE_COMMAND} -E copy_directory
    #        $ENV{PROGRAMFILES}/VideoLAN/vlc/plugins
    #        $<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins)
endif()
