include_directories(../main/cpp ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

file(GLOB TEST_FILES resources/*.csv)
foreach(TEST_FILE ${TEST_FILES})
    configure_file(${TEST_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()
configure_file(resources/moovie.conf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable (configuration_test_run cpp/ConfigurationTest.cpp)
target_link_libraries (configuration_test_run ${Boost_LIBRARIES} libmoovie)
add_test(configuration_test configuration_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_configuration_test.xml --report_level=detailed)

add_executable (coordinates_test_run cpp/CoordinatesTest.cpp)
target_link_libraries (coordinates_test_run ${Boost_LIBRARIES} libmoovie)
add_test(coordinates_test coordinates_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_coordinates_test.xml --report_level=detailed)

add_executable (dataset_test_run cpp/DataSetTest.cpp)
target_link_libraries (dataset_test_run ${Boost_LIBRARIES} libmoovie)
add_test(dataset_test dataset_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_dataset_test.xml --report_level=detailed)

add_executable (graphicalelements_test_run cpp/GraphicalElementsTest.cpp)
target_link_libraries (graphicalelements_test_run ${Boost_LIBRARIES} libmoovie)
add_test(graphicalelements_test graphicalelements_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_graphicalelements_test.xml --report_level=detailed)

add_executable (storageelements_test_run cpp/StorageElementsTest.cpp)
target_link_libraries (storageelements_test_run ${Boost_LIBRARIES} libmoovie)
add_test(storageelements_test storageelements_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_storageelements_test.xml --report_level=detailed)

add_executable (utilities_test_run cpp/UtilitiesTest.cpp)
target_link_libraries (utilities_test_run ${Boost_LIBRARIES} libmoovie)
add_test(NAME utilities_test COMMAND utilities_test_run --log_level=all --log_format=JUNIT --log_sink=${CMAKE_CURRENT_BINARY_DIR}/report_utilities_test.xml --report_level=detailed)
