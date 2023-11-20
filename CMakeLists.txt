cmake_minimum_required(VERSION 3.27)
project(IntelliScheduler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Final main.cpp)
target_link_libraries(Final
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

