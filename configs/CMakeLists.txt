cmake_minimum_required(VERSION 2.4.6)
Project("configs")

FILE(GLOB XML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "drone[0-9]*/[^.]*.xml")
MESSAGE("${XML_FILES}")

FILE(GLOB YAML_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "drone[0-9]*/[^.]*.yaml")
MESSAGE("${YAML_FILES}")

set(OTHER_FILES
        ${XML_FILES}
        ${YAML_FILES}
)
add_custom_target(other_files SOURCES ${OTHER_FILES})
