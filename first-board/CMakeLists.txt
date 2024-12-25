add_executable(first-board ${CMAKE_CURRENT_LIST_DIR}/main.c)

target_include_directories(first-board PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(first-board pico_stdlib)

pico_add_extra_outputs(first-board)
