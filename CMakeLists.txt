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
        Sql
        REQUIRED)

qt_add_resources(RES resources.qrc)

add_library(intelli_lib STATIC
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
#        src/utils/OpenAIAPI.cpp
#        src/utils/OpenAIAPI.h
        src/widget/gridcell.cpp
        src/widget/gridcell.h
        src/widget/gridcell.ui
        src/widget/searchline.cpp
        src/widget/searchline.h
        src/widget/searchline.ui
#        src/utils/DateUtil.cpp
#        src/utils/DateUtil.h
        src/view/weekview.cpp
        src/view/weekview.h
        src/view/weekview.ui
        src/widget/weekeventcell.cpp
        src/widget/weekeventcell.h
        src/widget/weekeventcell.ui
        src/widget/weekevtcelllabel.cpp
        src/widget/weekevtcelllabel.h
        src/widget/weekevtcelllabel.ui
        src/widget/weektablewidget.cpp
        src/widget/weektablewidget.h
        src/widget/weektablewidget.ui
        src/widget/gridview.cpp
        src/widget/gridview.h
        src/controller/EventManager.cpp
        src/controller/EventManager.h
        src/interface/IEventSubscriber.cpp
        src/interface/IEventSubscriber.h
        src/entity/Recurrence.cpp
        src/entity/Recurrence.h
        src/entity/Alarm.cpp
        src/entity/Alarm.h
        src/entity/EventCategories.cpp
        src/entity/EventCategories.h
        src/widget/weekeventcell.ui
#        src/utils/EventUtils.cpp
#        src/utils/EventUtils.h
#        src/utils/EnumUtils.h
#        src/utils/EventUtils.cpp
        src/view/eventview.cpp
        src/view/eventview.h
        src/view/eventview.ui
        src/tools/EventRepository.cpp
        src/tools/EventRepository.h
        src/widget/event_view/categorycombobox.cpp
        src/widget/event_view/categorycombobox.h
)
target_link_libraries(intelli_lib PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        Qt::Svg
)

add_executable(${PROJECT_NAME} main.cpp ${RES}
        src/controller/EventManager.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Widgets  async_simple intelli_lib )

if (Qt6Test_FOUND)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(src/utils)
add_subdirectory(src/dao)
add_subdirectory(third_party/async_simple)
target_include_directories(intelli_lib PUBLIC src ${CMAKE_SOURCE_DIR}/third_party/async_simple)
target_link_libraries(intelli_lib PRIVATE utils)
target_link_libraries(intelli_lib PRIVATE dao)