add_library(communication STATIC communication.c)
target_include_directories(communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(communication PUBLIC hardware_i2c pico_i2c_slave
                                           pico_stdlib)
set_target_properties(communication PROPERTIES PUBLIC_HEADER communication.h)
