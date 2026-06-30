add_executable(compackt_game
    src/main.cpp
    src/MovingPointSimulation.cpp
)

target_link_libraries(compackt_game
    PRIVATE compackt_engine
)
