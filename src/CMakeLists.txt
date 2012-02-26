set(cmake_source_dir .)
set(CMAKE_BUILD_TYPE Debug)
set(wt_project_target vanetizer.wt)
set(wt_project_source 
    client/widgets/mappropertyeditor.cpp
    client/widgets/paintbrush.cpp 
    client/mapmakerpage.cpp 
    client/navigationmenu.cpp
    logger.cpp 
    main.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

configure_file(${cmake_source_dir}/general.xml ${EXECUTABLE_OUTPUT_PATH}/general.xml COPYONLY)

add_executable(${wt_project_target} ${wt_project_source})
target_link_libraries(${wt_project_target} wthttp wt boost_signals)
include_directories(${cmake_source_dir})

# create the logs directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/logs)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resources)
# copy themes to resources directory
file(COPY ../themes/ DESTINATION ${PROJECT_BINARY_DIR}/bin/resources/themes/)

add_subdirectory(client)
add_subdirectory(xml)
add_subdirectory(model)

