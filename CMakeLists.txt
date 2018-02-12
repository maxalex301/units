cmake_minimum_required(VERSION 3.0.1)

project(Units)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(PYTHON_INTERFACE "Create python interface" ON)
OPTION(BUILD_TESTS "Build tests" OFF)

set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_MULTITHREDED ON)
set(BOOST_COMPONENTS )

if (PYTHON_INTERFACE)
    FIND_PACKAGE(PythonInterp)
    FIND_PACKAGE(PythonLibs)
    if (APPLE AND ${PYTHON_VERSION_MAJOR} EQUAL 3)
        set(BOOST_COMPONENTS python3)
    else()
        set(BOOST_COMPONENTS python)
    endif()
endif ()

if(BUILD_TESTS)
    set(BOOST_COMPONENTS ${BOOST_COMPONENTS} tests)
    enable_testing()
    add_subdirectory(tests)
endif()

find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found!!!")
endif(NOT Boost_FOUND)


set(HEADERS Unit.hpp
        LengthUnits.hpp
        PressureUnits.hpp
        TemperatureUnits.hpp)

if(PYTHON_INTERFACE)
    add_library(units_ext SHARED UnitsPython.cpp ${HEADERS})
    target_include_directories(units_ext PRIVATE ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    target_link_libraries(units_ext ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
    set_target_properties(units_ext PROPERTIES PREFIX "")
endif(PYTHON_INTERFACE)
