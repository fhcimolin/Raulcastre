# Setup which sources are going to be compiled
set(SOURCE
    main.cpp
    quickcg.cpp
)

# Add sources to executable. The executable's name is the same as the project's
# name in this case.
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})

# Link external libraries and source directories
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    ${SDL_LIBRARY}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${SDL_INCLUDE_DIR}
)

# Set outputs to build/{lib,bin}
set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy `pics` directory's contents into build/bin/pics directory.
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/pics $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/pics
    COMMENT "Copying pics directory's contents..."
)
