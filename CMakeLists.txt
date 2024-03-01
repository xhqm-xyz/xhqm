# cmake最低版本要求
cmake_minimum_required(VERSION 3.5) 
# 设置项目名称及版本
project(xhqm VERSION 0.1 LANGUAGES CXX)

# 设置c++版本为17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置发布模式
# set(CMAKE_BUILD_TYPE Debug)			调试模式，完全不优化，生成调试信息，方便调试程序
# set(CMAKE_BUILD_TYPE Release)			发布模式，优化程度最高，性能最佳，但是编译比 Debug 慢
# set(CMAKE_BUILD_TYPE MinSizeRel)		最小体积发布，生成的文件比 Release 更小，不完全优化，减少体积
# set(CMAKE_BUILD_TYPE RelWithDebInfo)	带调试信息发布，Release带有调试的符号信息，使用程序出错时，能够反馈一些信息
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


set(PROJECT_SOURCES
        head.h
        xhqm.h
)
set(PROJECT_SOURCES
	conception/element.h
        conception/event.h
        conception/exist.h
        conception/plugin.h
        conception/queues.h
        conception/stacks.h
        conception/struct.h
)
set(PROJECT_SOURCES
        metaclass/template.h
        metaclass/compute.h
	metaclass/class_type.h
        metaclass/symbols_has.h
        metaclass/object.h
	metaclass/tuple.h
	metaclass/function.h
)
set(PROJECT_SOURCES
        pattern/instance.cpp
        pattern/instance.h
        pattern/observer.cpp
        pattern/observer.h
)
set(PROJECT_SOURCES
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
)
set(PROJECT_SOURCES
        system/codesys.cpp
        system/codesys.h
        system/filesys.cpp
        system/filesys.h
        system/libmange.cpp
        system/libmange.h
        system/timesys.cpp
        system/timesys.h
)
set(PROJECT_SOURCES
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


install(TARGETS xhqm
    BUNDLE DESTINATION ./build
    LIBRARY DESTINATION ./public
    RUNTIME DESTINATION ./public
)
