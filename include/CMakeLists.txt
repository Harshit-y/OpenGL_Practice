add_library(glad STATIC
    ../libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ../libs/glad/include
)
