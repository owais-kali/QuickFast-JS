set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/client/vendor)

set(EXE_NAME JS-DECODER)

add_executable(${EXE_NAME}
        decoder.cpp
        template_consumer.cpp)

target_include_directories(${EXE_NAME}
        PRIVATE
        ${QUICKFAST_SRC}/src
        )

target_include_directories(${EXE_NAME} PRIVATE
        .
        ${XercesC_SRC_DIR}/src
        )

target_compile_definitions(${EXE_NAME}
        PUBLIC
        BOOST_BIND_GLOBAL_PLACEHOLDERS
        ASIOSERVICE_FWD_H)

target_link_libraries(${EXE_NAME}
        PUBLIC
        QuickFAST
        xerces-c
        )

if (CLION)
    target_compile_definitions(${EXE_NAME} PRIVATE -DCLION)
else (CLION)
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
    set_target_properties(${EXE_NAME} PROPERTIES LINK_FLAGS "-s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")
endif (CLION)