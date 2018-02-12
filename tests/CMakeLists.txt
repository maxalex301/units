include_directories(${Boost_INCLUDE_DIR})

foreach(d ${SUBDIRS})
    message(STATUS "Adding subdirectory: " ${d})
    add_subdirectory(${d})
endforeach()

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(UnitsTest UnitsTest.cpp)
target_link_libraries(UnitsTest ${Boost_LIBRARIES})
add_test(NAME UnitsTest COMMAND UnitsTest)


