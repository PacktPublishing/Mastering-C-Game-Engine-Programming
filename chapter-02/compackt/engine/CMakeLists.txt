add_library(compackt_engine STATIC
    src/Engine.cpp
    src/time/TimeSystem.cpp
    src/time/VariableTimestepController.cpp
    src/time/FixedTimestepController.cpp
)

target_include_directories(compackt_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
