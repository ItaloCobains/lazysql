set(SOURCES
  main.c
)

add_executable(lazysql ${SOURCES})

target_include_directories(lazysql
    PRIVATE ${CMAKE_SOURCE_DIR}/deps/notcurses/include
)

target_link_libraries(lazysql
    PRIVATE notcurses-core notcurses
)
