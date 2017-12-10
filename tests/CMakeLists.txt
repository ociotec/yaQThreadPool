file(GLOB TEST_YATP_SOURCES
    "*.cpp"
    "*.h"
)

add_executable(test-yatp
    ${TEST_YATP_SOURCES}
)

target_link_libraries(test-yatp
    yatp
    gtest
    gmock
)
