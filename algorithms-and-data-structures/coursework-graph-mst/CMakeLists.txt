add_executable(graph-mst
    src/main.cpp
    src/app.cpp
    src/dyn_array.cpp
    src/queue_array.cpp
    src/app.h
    src/dyn_array.h
    src/queue_array.h
    src/edge.h
    src/edge_array.h
)

# Копируем примеры графов рядом с бинарником, чтобы путь по умолчанию работал
add_custom_command(TARGET graph-mst POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/examples
            $<TARGET_FILE_DIR:graph-mst>/examples
)
