add_library(compackt_engine STATIC
    src/Engine.cpp
    src/time/TimeSystem.cpp
    src/time/VariableTimestepController.cpp
    src/time/FixedTimestepController.cpp
    src/rendering/ShapePrimitives2D.cpp
    src/rendering/Mesh.cpp
    src/rendering/ResourceLoaderMinimal.cpp
    src/rendering/OpenGLRenderer.cpp
    src/rendering/OpenGLVertexBuffer.cpp
    src/rendering/OpenGLIndexBuffer.cpp
    src/rendering/OpenGLShaderProgram.cpp
)

target_include_directories(compackt_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(compackt_engine
    PUBLIC
        glad
        glfw
)

target_compile_options(compackt_engine PRIVATE ${COMPACKT_WARNING_FLAGS})
