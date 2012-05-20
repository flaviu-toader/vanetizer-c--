set(cmake_source_dir .)
set(CMAKE_BUILD_TYPE Debug)
set(wt_project_target vanetizer.wt)

# Utility library
set(vanetUtil_source 
    templatefile.cpp
    logger.cpp
)

# Client executable
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
    main.cpp
)

# Xml helper library
set(vanetxml_source 
    xml/modeltoxmlconverter.cpp
    xml/xmlhelper.cpp
)

# Server-side library
set(vanetserver_source 
    server/runners/abstractconfiguration.cpp 
    server/runners/gmsconfiguration.cpp 
    server/runners/vmsconfiguration.cpp 
    server/vanetconfigurator.cpp
    server/database/configurationentity.cpp 
    server/database/configentryentity.cpp 
    server/database/persistencemanager.cpp  
)

set(test_source
    test/pugitest.cpp
)

include_directories(${cmake_source_dir})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

configure_file(${cmake_source_dir}/general.xml ${EXECUTABLE_OUTPUT_PATH}/general.xml COPYONLY)
# create the logs directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/logs)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/resources)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/etc)
# copy themes to resources directory
file(COPY ../themes/ DESTINATION ${PROJECT_BINARY_DIR}/bin/resources/themes/)
# copy glomosim executables and app.conf
file(COPY ../glomosim/bin/ DESTINATION ${PROJECT_BINARY_DIR}/bin/)
# copy glomosim configuration template
file(COPY ../glomosim/etc/ DESTINATION ${PROJECT_BINARY_DIR}/etc/)
# copy vanetmobisim executable
file(COPY ../vanetmobisim/ DESTINATION ${PROJECT_BINARY_DIR}/bin/)

add_library(vanetUtil ${vanetUtil_source})
target_link_libraries(vanetUtil wt)

add_library(vanetXml ${vanetxml_source})
target_link_libraries(vanetXml vanetUtil pugixml wt)

add_library(vanetServer ${vanetserver_source})
target_link_libraries(vanetServer vanetUtil pugixml wt wtdbo wtdbosqlite3 vanetXml)

add_executable(${wt_project_target} ${wt_project_source})
target_link_libraries(${wt_project_target} wthttp wt boost_signals vanetUtil vanetServer)

add_executable(test ${test_source})
target_link_libraries(test pugixml)

add_subdirectory(client)
add_subdirectory(xml)



add_subdirectory(server)
add_subdirectory(test)