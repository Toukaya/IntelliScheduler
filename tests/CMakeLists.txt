# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

macro(define_test_target target)
    add_executable(${target} ${target}.h ${target}.cpp)
    add_test(${target} ${target})
    target_link_libraries(${target}
            Qt::Core
            Qt::Gui
            Qt::Widgets
            Qt::Network
            Qt::Test)
    target_include_directories(${target}
            PUBLIC ${PROJECT_SOURCE_DIR}/src)
endmacro(define_test_target)

set(TARGETS_FOR_TEST monthviewTest)
foreach(target ${TARGETS_FOR_TEST})
    define_test_target(${target})
endforeach()