if (MSVC)
    # warning level 4
    add_compile_options(/W4)
    add_compile_options("$<$<CONFIG:DEBUG>:/fsanitize=address>")
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)