cmake_minimum_required(VERSION 3.10)


project(raspi_led)

include_directories(../3rdparty/rpi-rgb-led-matrix/include)
add_library(rpi_rgb_led_matrix SHARED
	../3rdparty/rpi-rgb-led-matrix/lib/bdf-font.cc
	../3rdparty/rpi-rgb-led-matrix/lib/led-matrix-c.cc
	../3rdparty/rpi-rgb-led-matrix/lib/content-streamer.cc
	../3rdparty/rpi-rgb-led-matrix/lib/multiplex-mappers.cc
	../3rdparty/rpi-rgb-led-matrix/lib/framebuffer.cc
	../3rdparty/rpi-rgb-led-matrix/lib/options-initialize.cc
	../3rdparty/rpi-rgb-led-matrix/lib/gpio.cc
	../3rdparty/rpi-rgb-led-matrix/lib/pixel-mapper.cc
	../3rdparty/rpi-rgb-led-matrix/lib/graphics.cc
	../3rdparty/rpi-rgb-led-matrix/lib/thread.cc
	../3rdparty/rpi-rgb-led-matrix/lib/led-matrix.cc
	../3rdparty/rpi-rgb-led-matrix/lib/hardware-mapping.c
	)

add_executable(raspi_led main.cpp)

target_link_libraries(raspi_led rpi_rgb_led_matrix pthread rt m)
