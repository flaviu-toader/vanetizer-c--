set(vanetxml_source
    xml/property/areapropertyconvertor.cpp
    modeltoxmlconverter.cpp
)

add_library(vanetXml ${vanetxml_source})
target_link_libraries(vanetXml pugixml wt)
add_subdirectory(property)
