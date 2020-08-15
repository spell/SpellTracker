cmake_minimum_required(VERSION 3.5)

project(SpellTracker LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools Xml REQUIRED)

set(SOURCE_FILES
        src/main.cpp
        src/IconSet.cpp
        src/IconSet.h
        src/Item.cpp
        src/Item.h
        src/widgets/ItemTrackerIcon.cpp
        src/widgets/ItemTrackerIcon.h
        src/models/ItemLayoutModel.cpp
        src/models/ItemLayoutModel.h
        src/models/ItemLayoutObject.cpp
        src/models/ItemLayoutObject.h
        src/views/ItemTrackerView.cpp
        src/views/ItemTrackerView.h
        src/windows/MainWindow.cpp
        src/windows/MainWindow.h
        src/windows/MainWindow.ui
        src/windows/StreamerPopoutWindow.cpp
        src/windows/StreamerPopoutWindow.h
        src/windows/SettingsDialog.cpp
        src/windows/SettingsDialog.h
        src/windows/SettingsDialog.ui)

set(RESOURCE_FILES
        resources/gamedata/OOT_Randomizer.xml
        resources/icons/the_legend_of_zelda_ocarina_of_time.png)

set(TS_FILES
        lang/SpellTracker_en_US.ts)

if (ANDROID)
    add_library(SpellTracker SHARED
            ${TS_FILES}
            ${SOURCE_FILES})
elseif (WIN32)
    add_executable(SpellTracker WIN32
            ${TS_FILES}
            ${SOURCE_FILES})
elseif (APPLE)
    add_executable(SpellTracker MACOSX_BUNDLE
            ${TS_FILES}
            ${SOURCE_FILES}
            ${RESOURCE_FILES})
    set_target_properties(SpellTracker PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_FRAMEWORK_IDENTIFIER nl.lolwtf.SpellTracker
            RESOURCE "${RESOURCE_FILES}")
else ()
    add_executable(SpellTracker
            ${TS_FILES}
            ${SOURCE_FILES})
endif ()

target_link_libraries(SpellTracker PRIVATE Qt5::Widgets)
target_include_directories(SpellTracker
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
