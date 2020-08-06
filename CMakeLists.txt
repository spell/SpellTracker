cmake_minimum_required(VERSION 3.5)

project(SpellTracker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(Qt5 COMPONENTS Widgets LinguistTools Xml REQUIRED)

set(TS_FILES SpellTracker_en_US.ts)

if (ANDROID)
    add_library(SpellTracker SHARED
            ${TS_FILES}
            main.cpp
            Item.cpp
            Item.h
            MainWindow.cpp
            MainWindow.h
            MainWindow.ui
            ZoneGroupBox.cpp
            ZoneGroupBox.h
            SubzoneGroupBox.cpp
            SubzoneGroupBox.h
            Check.cpp
            Check.h
            Slot.cpp
            Slot.h ItemTracker.cpp ItemTracker.h ItemPickerDialog.cpp ItemPickerDialog.h)
else ()
    add_executable(SpellTracker
            ${TS_FILES}
            main.cpp
            Item.cpp
            Item.h
            MainWindow.cpp
            MainWindow.h
            MainWindow.ui
            ZoneGroupBox.cpp
            ZoneGroupBox.h
            SubzoneGroupBox.cpp
            SubzoneGroupBox.h
            Check.cpp
            Check.h
            Slot.cpp
            Slot.h ItemTracker.cpp ItemTracker.h ItemPickerDialog.cpp ItemPickerDialog.h)
endif ()

target_link_libraries(SpellTracker PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
