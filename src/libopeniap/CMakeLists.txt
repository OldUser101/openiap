file(GLOB LIBOPENIAP_SOURCES CONFIGURE_DEPENDS *.cpp *.c)

add_library(openiap STATIC ${LIBOPENIAP_SOURCES})

target_include_directories(openiap PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

target_include_directories(openiap PRIVATE ${LIBUSB_INCLUDE_DIRS})
target_link_libraries(openiap PRIVATE ${LIBUSB_LIBRARIES})