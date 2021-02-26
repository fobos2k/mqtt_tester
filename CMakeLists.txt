cmake_minimum_required(VERSION 3.12)

project(MQTT_Tester)

set(TARGET_NAME mqtt_tester)
set(MAINLIB_TARGET_NAME libtester)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
add_compile_options(-Wno-deprecated-declarations)

set(PROJECT_INCLUDES include)
set(PROJECT_SOURCES src)
set(PROJECT_MAIN_SOURCE main.cpp)

aux_source_directory(${PROJECT_SOURCES} LIB_SOURCES)
list(REMOVE_ITEM LIB_SOURCES ${PROJECT_SOURCES}/${PROJECT_MAIN_SOURCE})
message(STATUS "-> LIB_SOURCES = ${LIB_SOURCES}")

add_executable(${TARGET_NAME}
    ${PROJECT_SOURCES}/${PROJECT_MAIN_SOURCE})
add_dependencies(${TARGET_NAME} ${MAINLIB_TARGET_NAME})

includes_guard(GLOBAL)

# Boost
list(APPEND Boost_LIBRARIES_LIST filesystem system unit_test_framework)
find_package(Boost COMPONENTS ${Boost_LIBRARIES_LIST} REQUIRED)

# Mosquitto
find_library(LIBMOSQUITTOPP libmosquittopp.so)
list(APPEND Mosquitto_LIBRARIES ${LIBMOSQUITTOPP})
find_library(LIBMOSQUITTO libmosquitto.so)
list(APPEND Mosquitto_LIBRARIES ${LIBMOSQUITTO})

# RapidJson
if (IS_DIRECTORY $ENV{RAPIDJSON_PATH} )
    set(RapidJSON_INCLUDES $ENV{RAPIDJSON_PATH}/include)
endif()

# Isolator++
find_library(LIBISOLATOR libisolator.so HINTS $ENV{ISOLATOR_LIB_PATH})

add_library(${MAINLIB_TARGET_NAME} OBJECT ${LIB_SOURCES})

if ( LOCAL_APP )
    include(includes.cmake/localtest.cmake)
endif()

target_include_directories(${MAINLIB_TARGET_NAME} PUBLIC
    ${PROJECT_INCLUDES}
    ${Boost_INCLUDE_DIRS}
    ${RapidJSON_INCLUDES}
    )

target_link_libraries(${MAINLIB_TARGET_NAME} PUBLIC
    ${Boost_LIBRARIES}
    ${Mosquitto_LIBRARIES}
    )

target_compile_options(${MAINLIB_TARGET_NAME} PRIVATE -fprofile-arcs -ftest-coverage -fPIC -O0 -ggdb)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_INCLUDES}
    ${Boost_INCLUDE_DIRS}
    ${RapidJSON_INCLUDES}
    )
target_link_options(${TARGET_NAME} BEFORE PRIVATE -lgcov --coverage)
target_link_libraries(${TARGET_NAME} ${MAINLIB_TARGET_NAME})

# Install
install(TARGETS ${TARGET_NAME} RUNTIME)
