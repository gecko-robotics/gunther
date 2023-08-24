
LIST(APPEND APPS
    simple
    dev
)

foreach(MAIN ${APPS})
    add_executable(${MAIN} ${MAIN}.cpp)
    target_link_libraries(${MAIN} PRIVATE ${PROJECT_NAME})
endforeach()
