find_package(Qt5Core)

file(GLOB LIB_YATP_SOURCES
    "*.cpp"
    "*.h"
)

add_library(yatp STATIC
    ${LIB_YATP_SOURCES}
)

target_include_directories(yatp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(yatp
    Qt5::Core
)
