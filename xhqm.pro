TEMPLATE = lib
TARGET = xhqm

QT +=
DEFINES += LIBRARY XHQM_QT XHQM_PROGRAM

CONFIG += c++17
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

DESTDIR = $$PWD/../public/


INCLUDEPATH += .

CONFIG+=debug_and_release
CONFIG(debug, debug|release) {

} else {
    DEFINES += NDEBUG

}

HEADERS += \
    conception/colors.h \
    conception/element.h \
    conception/event.h \
    conception/exist.h \
    conception/plugin.h \
    conception/queues.h \
    conception/stacks.h \
    conception/struct.h \
    head.h \
    metaclass/class_type.h \
    metaclass/compute.h \
    metaclass/symbols_has.h \
    metaclass/template.h \
    metaclass/tuple.h \
    pattern/instance.h \
    pattern/observer.h \
    software/action.h \
    software/command.h \
    software/mousekey_events.h \
    software/page.h \
    software/signal.h \
    software/signalslot_events.h \
    system/codesys.h \
    system/filesys.h \
    system/libmange.h \
    system/timesys.h \
    universe/info/csvfile.h \
    universe/info/fileinfo.h \
    universe/info/igesfile.h \
    universe/info/infomation.h \
    universe/info/stepfile.h \
    universe/info/stlfile.h \
    universe/info/xcfg.h \
    universe/info/xlog.h \
    universe/math/algorithm/analysis.h \
    universe/math/algorithm/crc.h \
    universe/math/algorithm/extremum.h \
    universe/math/algorithm/geometry.h \
    universe/math/algorithm/ransac.h \
    universe/math/gather.h \
    universe/math/matrix.h \
    universe/math/number.h \
    universe/math/point.h \
    universe/math/vector.h \
    xhqm.h

SOURCES += \
    pattern/instance.cpp \
    pattern/observer.cpp \
    software/action.cpp \
    software/command.cpp \
    software/mousekey_events.cpp \
    software/page.cpp \
    software/signal.cpp \
    software/signalslot_events.cpp \
    system/codesys.cpp \
    system/filesys.cpp \
    system/libmange.cpp \
    system/timesys.cpp \
    universe/info/csvfile.cpp \
    universe/info/fileinfo.cpp \
    universe/info/igesfile.cpp \
    universe/info/infomation.cpp \
    universe/info/stepfile.cpp \
    universe/info/stlfile.cpp \
    universe/info/xcfg.cpp \
    universe/info/xlog.cpp \
    universe/math/algorithm/crc.cpp \
    universe/math/algorithm/geometry.cpp \
    universe/math/algorithm/ransac.cpp


