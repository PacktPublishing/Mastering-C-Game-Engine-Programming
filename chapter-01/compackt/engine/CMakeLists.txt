add_library(compackt_engine STATIC
    src/Engine.cpp
)

target_include_directories(compackt_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
