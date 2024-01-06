set(DAO_SRC
        EventDao.h
        EventDao.cpp
)

add_library(dao ${DAO_SRC})

target_include_directories(dao PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/third_party/async_simple)

# Link Qt libraries
target_link_libraries(dao PRIVATE
        Qt::Core
        Qt::Widgets
)
