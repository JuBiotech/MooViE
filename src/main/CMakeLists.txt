include_directories(cpp/lib resources/thirdparty)

# MooViE library
add_library(libmoovie SHARED
        cpp/lib/DataSet.h cpp/lib/DataSet.cpp cpp/lib/Scale.h cpp/lib/Scale.cpp cpp/lib/Color.h cpp/lib/Color.cpp
        cpp/lib/Configuration.h cpp/lib/Configuration.cpp cpp/lib/OutputGrid.h cpp/lib/OutputGrid.cpp cpp/lib/IOVector.h
        cpp/lib/IOVector.cpp cpp/lib/CairoDrawer.h cpp/lib/CairoDrawer.cpp cpp/lib/Scene.h cpp/lib/Scene.cpp
        cpp/lib/Utils.h cpp/lib/Utils.cpp cpp/lib/InputAxis.h cpp/lib/InputAxis.cpp cpp/lib/Coordinates.h
        cpp/lib/DrawerProperties.h cpp/lib/Label.h cpp/lib/Mapper.h cpp/lib/TextProperties.h cpp/lib/Triangle.h
        cpp/lib/Drawer.h)
include(GenerateExportHeader)
generate_export_header(libmoovie)
set_target_properties (libmoovie PROPERTIES OUTPUT_NAME moovie)
target_link_libraries (libmoovie PUBLIC  ${CAIROMM_LIBRARIES})

install(FILES
        cpp/lib/DataSet.h cpp/lib/Scale.h cpp/lib/Color.h cpp/lib/Configuration.h cpp/lib/OutputGrid.h
        cpp/lib/IOVector.h cpp/lib/CairoDrawer.h cpp/lib/Scene.h cpp/lib/Utils.h cpp/lib/InputAxis.h
        cpp/lib/Coordinates.h cpp/lib/DrawerProperties.h cpp/lib/Label.h cpp/lib/Mapper.h cpp/lib/TextProperties.h
        cpp/lib/Triangle.h cpp/lib/Drawer.h
        ${PROJECT_BINARY_DIR}/libmoovie_export.h
        ${CMAKE_CURRENT_BINARY_DIR}/moovie_config.h
        DESTINATION ${DEST_INCLUDE_DIR})
install(TARGETS libmoovie DESTINATION ${DEST_LIB_DIR})


# MooViE executable
add_executable(moovie cpp/moovie.cpp)
add_dependencies(moovie libmoovie)
target_link_libraries(moovie PUBLIC libmoovie)

install (TARGETS moovie DESTINATION ${DEST_BIN_DIR})


# Qt5 application
if (BUILD_GUI)
    include_directories(${CMAKE_BINARY_DIR} cpp/desktop)
    QT5_WRAP_UI(UI_HEADERS
            resources/ui/MainWindow.ui resources/ui/IOListWidget.ui resources/ui/ConfigurationDialog.ui
            resources/ui/ConfIntWidget.ui resources/ui/ConfDoubleWidget.ui resources/ui/ConfStringWidget.ui)
    QT5_WRAP_CPP(MOC_SRCS
            cpp/desktop/MainWindow.h cpp/desktop/IOList.h
            cpp/desktop/IOListWidget.h cpp/desktop/ConfigurationDialog.h cpp/desktop/ConfIntWidget.h
            cpp/desktop/ConfDoubleWidget.h cpp/desktop/ConfStringWidget.h cpp/desktop/MooViEView.h)
    add_executable (moovie-desktop
            cpp/desktop/MainWindow.cpp cpp/desktop/IOList.cpp cpp/desktop/IOListWidget.cpp
            cpp/desktop/ConfigurationDialog.cpp cpp/desktop/ConfIntWidget.cpp cpp/desktop/ConfDoubleWidget.cpp
            cpp/desktop/ConfStringWidget.cpp cpp/desktop/MooViEView.cpp cpp/desktop/moovie-desktop.cpp
            ${MOC_SRCS}
            ${UI_HEADERS})
    add_dependencies(moovie-desktop libmoovie)
    target_link_libraries(moovie-desktop Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WebEngine Qt5::WebEngineWidgets libmoovie)

    file(WRITE ${PROJECT_BINARY_DIR}/moovie.desktop "[Desktop Entry]
Name=MooViE
Exec=${DEST_BIN_DIR}/moovie-desktop
Icon=${DEST_PIXMAP_DIR}/moovie.png
Categories=Science;DataVisualization;
Terminal=false
Type=Application\n")
    install(TARGETS moovie-desktop DESTINATION ${DEST_BIN_DIR})
    install(FILES ${PROJECT_BINARY_DIR}/moovie.desktop DESTINATION ${DEST_DESKTOP_DIR})
    install(FILES resources/pixmaps/moovie.png DESTINATION ${DEST_PIXMAP_DIR})
endif()


# Installation
install(FILES ${MOOVIE_INCLUDES} ${PROJECT_BINARY_DIR}/libmoovie_export.h ${CMAKE_CURRENT_BINARY_DIR}/moovie_config.h DESTINATION ${DEST_INCLUDE_DIR})
install(TARGETS libmoovie DESTINATION ${DEST_LIB_DIR})
install(TARGETS moovie DESTINATION ${DEST_BIN_DIR})
if (BUILD_GUI)
    file(WRITE ${PROJECT_BINARY_DIR}/moovie.desktop "[Desktop Entry]
Name=MooViE
Exec=${DEST_BIN_DIR}/moovie-desktop
Icon=${DEST_PIXMAP_DIR}/moovie.png
Categories=Science;DataVisualization;
Terminal=false
Type=Application\n")
    install (TARGETS moovie-desktop DESTINATION ${DEST_BIN_DIR})
    install (FILES ${PROJECT_BINARY_DIR}/moovie.desktop DESTINATION ${DEST_DESKTOP_DIR})
    install (FILES moovie.png DESTINATION ${DEST_PIXMAP_DIR})
endif()
install (DIRECTORY ${MOOVIE_DOC_DIR} DESTINATION ${DEST_DOC_DIR})
install (FILES README.md DESTINATION ${DEST_DOC_DIR})