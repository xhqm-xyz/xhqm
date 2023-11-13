cmake_minimum_required(VERSION 3.5)

project(xhqm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        head.h
        xhqm.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(xhqm
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        conception/element.h
        conception/event.h
        conception/exist.h
        conception/plugin.h
        conception/queues.h
        conception/stacks.h
        conception/struct.h
        metaclass/class_type.h
        metaclass/compute.h
        metaclass/symbols_has.h
        metaclass/template.h
        metaclass/tuple.h
        pattern/instance.cpp
        pattern/instance.h
        pattern/observer.cpp
        pattern/observer.h
        software/page.cpp
        software/page.h
        software/action.cpp
        software/action.h
        software/command.cpp
        software/command.h
        software/mousekey_events.cpp
        software/mousekey_events.h
	software/signal.cpp
        software/signal.h
        software/signalslot_events.cpp
        software/signalslot_events.h
        system/codesys.cpp
        system/codesys.h
        system/filesys.cpp
        system/filesys.h
        system/libmange.cpp
        system/libmange.h
        system/timesys.cpp
        system/timesys.h
        universe/life/nurbs.cpp
        universe/life/nurbs.h
        universe/life/pointcloud.h
        universe/life/shape.h
        universe/math/gather.h
        universe/math/matrix.h
        universe/math/number.h
        universe/math/point.h
        universe/math/vector.h
        universe/math/algorithm/analysis.h
        universe/math/algorithm/extremum.h
        universe/math/algorithm/crc.cpp
        universe/math/algorithm/crc.h
        universe/math/algorithm/geometry.cpp
        universe/math/algorithm/geometry.h
        universe/math/algorithm/ransac.cpp
        universe/math/algorithm/ransac.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET xhqm APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(xhqm SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(xhqm
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(xhqm PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.xhqm)
endif()
set_target_properties(xhqm PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS xhqm
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(xhqm)
endif()
