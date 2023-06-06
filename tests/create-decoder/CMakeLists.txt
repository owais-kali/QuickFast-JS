set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/client/vendor)

add_executable(boost-test
        boost-test.cpp
        template_consumer.cpp)

target_include_directories(boost-test
        PRIVATE
        ${QUICKFAST_SRC}/src
        )

target_include_directories(boost-test PRIVATE
        .
        ${XercesC_SRC_DIR}/src
        )

target_compile_definitions(boost-test
        PUBLIC
        BOOST_BIND_GLOBAL_PLACEHOLDERS
        ASIOSERVICE_FWD_H)

target_link_libraries(boost-test
        PUBLIC
        QuickFAST
        xerces-c
        )

if (CLION)
    target_compile_definitions(boost-test PRIVATE -DCLION)
else (CLION)
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
    set_target_properties(boost-test PROPERTIES LINK_FLAGS "-s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")
endif (CLION)