find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_YATP_SOURCES
    "*.cpp"
    "*.h"
)

add_executable(test-yatp
    ${TEST_YATP_SOURCES}
)

target_link_libraries(test-yatp
    yatp
    ${GTEST_BOTH_LIBRARIES}
)
