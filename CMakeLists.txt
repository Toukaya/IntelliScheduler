cmake_minimum_required(VERSION 3.27)
project(IntelliScheduler VERSION 0.82 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        Network
        Test
        Svg
        Sql
)

qt_add_resources(RES resources.qrc)

set(PROJECT_SOURCES
        main.cpp
        ${RES}
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
        src/controller/AppManager.cpp
        src/controller/AppManager.h
#        src/interface/IEventSubscriber.cpp
#        src/interface/IEventSubscriber.h
        src/entity/Recurrence.cpp
        src/entity/Recurrence.h
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
        src/widget/event_view/categorycombobox.cpp
        src/widget/event_view/categorycombobox.h
        src/controller/Services/EventService.cpp
        src/controller/Services/EventService.h
        src/controller/Services/EventSubscriptionService.cpp
        src/controller/Services/EventSubscriptionService.h
        src/controller/Services/EventICalFormatService.cpp
        src/controller/Services/EventICalFormatService.h
        src/db/DBManager.cpp
        src/db/DBManager.h
        src/widget/event_view/repeatdialog.cpp
        src/widget/event_view/repeatdialog.h
        src/widget/event_view/repeatdialog.ui
        src/widget/eventlistwidget.cpp
        src/widget/eventlistwidget.h
        src/widget/eventlistitem.cpp
        src/widget/eventlistitem.h
        src/widget/eventlistitem.ui
        src/controller/Services/EventReminderService.cpp
        src/controller/Services/EventReminderService.h
        src/AppConfig.hpp
        src/widget/event_view/customalertdialog.cpp
        src/widget/event_view/customalertdialog.h
        src/widget/event_view/customalertdialog.ui
        src/utils/DateUtil.cpp
        src/utils/EnumUtils.h
        src/utils/EventUtils.h
        src/utils/OpenAIAPI.h
        src/utils/DateUtil.cpp
        src/utils/EventUtils.cpp
        src/utils/OpenAIAPI.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET IntelliScheduler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
                ${PROJECT_SOURCES}
        )
    endif()
endif()

#add_executable(${PROJECT_NAME} main.cpp ${RES})


if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            ${BUNDLE_ID_OPTION}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
            WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
            BUNDLE DESTINATION .
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(IntelliScheduler)
    endif()
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND /opt/homebrew/Cellar/qt/6.6.1/bin/macdeployqt
#        $<TARGET_BUNDLE_DIR:${PROJECT_NAME}> -always-overwrite
#        COMMENT "Running macdeployqt..."
#)

#add_subdirectory(third_party/async_simple)
#add_subdirectory(src/utils)
#target_link_libraries(${PROJECT_NAME} PRIVATE utils)
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Widgets #[[async_simple]] #[[intelli_lib]] )
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE FALSE
            WIN32_EXECUTABLE FALSE
    )
    if (Qt6Test_FOUND)
        enable_testing()
        add_subdirectory(tests)
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Svg
        Qt${QT_VERSION_MAJOR}::Sql
)

target_include_directories(${PROJECT_NAME} PUBLIC src #[[${CMAKE_SOURCE_DIR}/third_party/async_simple]])
