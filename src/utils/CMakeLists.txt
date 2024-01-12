set(UTILS_SRC
        DateUtil.h
        EnumUtils.h
        EventUtils.h
        OpenAIAPI.h
        DateUtil.cpp
        EventUtils.cpp
        OpenAIAPI.cpp
)

add_library(utils ${UTILS_SRC})

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/third_party/async_simple)

# Link Qt libraries
target_link_libraries(utils PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)