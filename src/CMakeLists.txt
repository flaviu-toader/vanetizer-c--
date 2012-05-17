set(cmake_source_dir .)
set(CMAKE_BUILD_TYPE Debug)
set(wt_project_target vanetizer.wt)
set(wt_project_source 
    client/widgets/dialogs/abstractpropertyform.cpp
    client/widgets/dialogs/vanetareapropertyform.cpp
    client/widgets/dialogs/vanetsteppropertyform.cpp 
    client/widgets/dialogs/vanetseedpropertyform.cpp 
    client/widgets/dialogs/vanetextensionform.cpp 
    client/widgets/dialogs/vanetroutingprotocolpropertyform.cpp 
    client/widgets/dialogs/vanetgmsoutpropertyform.cpp
    client/widgets/dialogs/vanetspatialmodelpropertyform.cpp
    client/widgets/dialogs/vanetspmodeldump.cpp
    client/widgets/dialogs/vanettimesimulationpropertyform.cpp
    client/widgets/dialogs/vanettrafficlightpropertyform.cpp
    client/widgets/dialogs/vanetmobilitymodelform.cpp 
    client/widgets/dialogs/vanetnodegroupform.cpp 
    client/widgets/dialogs/vanetnodeform.cpp
    client/widgets/dialogs/propertydialog.cpp
    client/widgets/paintbrush.cpp 
    client/widgets/paintbrushform.cpp  
    client/widgets/mappropertyeditor.cpp
    client/configurationpage.cpp 
    client/navigationmenu.cpp
    logger.cpp 
    main.cpp
)

set(vanetxml_source 
    xml/modeltoxmlconverter.cpp
    xml/xmlhelper.cpp
)

set(vanetserver_source 
    server/runners/gmsconfiguration.cpp 
    server/runners/vmsconfiguration.cpp 
    server/vanetconfigurator.cpp
)

include_directories(${cmake_source_dir})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

configure_file(${cmake_source_dir}/general.xml ${EXECUTABLE_OUTPUT_PATH}/general.xml COPYONLY)
# create the logs directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/logs)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resources)
# copy themes to resources directory
file(COPY ../themes/ DESTINATION ${PROJECT_BINARY_DIR}/bin/resources/themes/)

add_library(vanetXml ${vanetxml_source})
target_link_libraries(vanetXml pugixml wt)

add_library(vanetServer ${vanetserver_source})
target_link_libraries(vanetServer pugixml wt vanetXml)

add_executable(${wt_project_target} ${wt_project_source})
target_link_libraries(${wt_project_target} wthttp wt boost_signals vanetServer)


add_subdirectory(client)
add_subdirectory(xml)



add_subdirectory(server)