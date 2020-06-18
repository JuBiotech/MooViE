set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

file(GLOB TEST_FILES files/*.csv)
foreach(TEST_FILE ${TEST_FILES})
    configure_file(${TEST_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()
configure_file(files/moovie.conf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable (configuration_test_run ConfigurationTest.cpp)
target_link_libraries (configuration_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(configuration_test configuration_test_run)

add_executable (coordinates_test_run CoordinatesTest.cpp)
target_link_libraries (coordinates_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(coordinates_test coordinates_test_run)

add_executable (dataset_test_run DataSetTest.cpp)
target_link_libraries (dataset_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(dataset_test dataset_test_run)

add_executable (graphicalelements_test_run GraphicalElementsTest.cpp)
target_link_libraries (graphicalelements_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(graphicalelements_test graphicalelements_test_run)

add_executable (storageelements_test_run StorageElementsTest.cpp)
target_link_libraries (storageelements_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(storageelements_test storageelements_test_run)

add_executable (utilities_test_run UtilitiesTest.cpp)
target_link_libraries (utilities_test_run ${Boost_LIBRARIES} libmoovie ${CAIROMM_LIBRARIES})
add_test(utilities_test utilities_test_run)