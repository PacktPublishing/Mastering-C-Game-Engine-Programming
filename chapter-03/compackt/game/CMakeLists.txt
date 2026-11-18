add_executable(compackt_game
    src/main.cpp
    src/MovingPointSimulation.cpp
    src/ParticleSimulation.cpp
)

target_link_libraries(compackt_game
    PRIVATE compackt_engine
)

target_compile_options(compackt_game PRIVATE ${COMPACKT_WARNING_FLAGS})
