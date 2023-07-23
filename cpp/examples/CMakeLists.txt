
LIST(APPEND APPS
    simple
)

foreach(MAIN ${APPS})
    add_executable(${MAIN} ${MAIN}.cpp)
    target_link_libraries(${MAIN} PRIVATE gunther)
endforeach()
