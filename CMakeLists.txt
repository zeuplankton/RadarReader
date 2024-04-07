cmake_minimum_required(VERSION 3.16)


set(PROJECT_VERSION "1.2.3")
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "2")

execute_process(COMMAND hg parents --template '{latesttag}.{latesttagdistance}' OUTPUT_VARIABLE PROJECT_VERSION_TEMP OUTPUT_STRIP_TRAILING_WHITESPACE)

if(PROJECT_VERSION_TEMP)
    string(REGEX MATCH "[0-9]+" PROJECT_VERSION_MAJOR ${PROJECT_VERSION_TEMP})
    string(REGEX MATCH "[0-9]+\\.[0-9]+" PROJECT_VERSION_MINOR ${PROJECT_VERSION_TEMP})
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" PROJECT_VERSION ${PROJECT_VERSION_TEMP})
endif()

project(RadarReader VERSION ${PROJECT_VERSION} LANGUAGES CXX)

add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)


find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")

qt_add_executable(appRadarReader
    main.cpp ${app_icon_resource_windows}
)

#    QML_FILES
qt_add_qml_module(appRadarReader
    URI RadarReader
    VERSION ${PROJECT_VERSION}
    SOURCES
        startup.h
        startup.cpp
        utils.h
        utils.cpp
        ViewManager/mainviewmanager.h
        ViewManager/mainviewmanager.cpp
        Model/settings.h
        Model/settings.cpp
        Model/provider.h
        Model/provider.cpp
        Model/instrument.h
        Model/instrument.cpp
        Model/connector.h
        Model/connector.cpp
    RESOURCES
        images.qrc
        qmls.qrc
        json.qrc
        icon.rc
        RadarReader.ico
        README.md


)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.

set_target_properties(appRadarReader PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appRadarReader
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appRadarReader
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appRadarReader
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
