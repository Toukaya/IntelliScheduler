cmake_minimum_required(VERSION 3.27)
project(IntelliScheduler CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Test
        Svg
        REQUIRED)

qt_add_resources(RES resources.qrc)

add_executable(${PROJECT_NAME} main.cpp
        src/core/scheduler.hpp
        src/types.hpp
        src/entity/Event.cpp
        src/entity/Event.h
        src/widget/canlendarwidget.cpp
        src/widget/canlendarwidget.h
        src/widget/canlendarwidget.ui
        src/view/monthview.cpp
        src/view/monthview.h
        src/view/monthview.ui
        src/view/mainwindow.cpp
        src/view/mainwindow.h
        src/view/mainwindow.ui
        src/uitls/OpenAIAPI.cpp
        src/uitls/OpenAIAPI.h
        src/widget/gridcell.cpp
        src/widget/gridcell.h
        src/widget/gridcell.ui
        ${RES}
        src/widget/searchline.cpp
        src/widget/searchline.h
        src/widget/searchline.ui
)
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Svg
)

if (Qt6Test_FOUND)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(third_party/async_simple)
target_include_directories(${PROJECT_NAME} PRIVATE third_party/async_simple)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} async_simple)