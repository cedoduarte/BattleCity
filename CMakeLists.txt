cmake_minimum_required(VERSION 3.5)

project(BattleCity VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        scene.h scene.cpp
        res.qrc
        items/tank.h
        items/tank.cpp
        items/player.h
        items/player.cpp
        items/enemy.h 
        items/enemy.cpp
        items/missile.h 
        items/missile.cpp
        items/imageitem.h
        items/imageitem.cpp
        items/movableitem.h
        items/movableitem.cpp
        items/flagitem.h 
        items/flagitem.cpp
        items/brick.h
        items/brick.cpp
        mousetracker.h mousetracker.cpp mousetracker.ui
        huds/playerhud.h
        huds/playerhud.cpp
        huds/playerhud.ui
        huds/enemyhud.h
        huds/enemyhud.cpp
        huds/enemyhud.ui
        huds/keyhud.h
        huds/keyhud.cpp
        huds/keyhud.ui
        keycombobox.h keycombobox.cpp
        namekey.h namekey.cpp
        util.h util.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BattleCity
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BattleCity APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BattleCity SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BattleCity
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BattleCity PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(BattleCity PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_include_directories(BattleCity PRIVATE .)

set_target_properties(BattleCity PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS BattleCity
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BattleCity)
endif()
