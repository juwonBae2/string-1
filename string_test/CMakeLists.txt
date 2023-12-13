project(string_test)

add_executable(${PROJECT_NAME}
    src/string_test.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
        string_implementation
        console_style
        gtest
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        ${PROJECT_BINARY_DIR}/include
    PRIVATE
        ${PROJECT_BINARY_DIR}/src
)