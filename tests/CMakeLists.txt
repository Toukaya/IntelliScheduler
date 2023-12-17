# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

find_package(Qt6 COMPONENTS Test REQUIRED)

macro(package_add_test TESTNAME)
    # 为源文件创建一个可执行文件
    add_executable(${TESTNAME} ${TESTNAME}.cpp)

    # 链接到相应的Qt模块
    target_link_libraries(${TESTNAME} intelli_lib
            Qt::Core
            Qt::Gui
            Qt::Widgets
            Qt::Network
            Qt::Test)

    # 添加到 CTest 测试
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})

    set_tests_properties(${TESTNAME} PROPERTIES TIMEOUT 10)
endmacro()

# 添加测试
package_add_test(WeekEvtCellLabelTest)
package_add_test(WeekTableWidgetTest)
package_add_test(EventViewTest)
