add_executable(boost-test
        boost-test.cpp)

target_include_directories(boost-test
        PRIVATE
        ${QUICKFAST_SRC}/src
        )

target_compile_definitions(boost-test
        PUBLIC
        BOOST_BIND_GLOBAL_PLACEHOLDERS
        ASIOSERVICE_FWD_H)

target_link_libraries(boost-test
        PUBLIC
        QuickFAST
        )

set_target_properties(boost-test PROPERTIES
        COMPILE_FLAGS "-s USE_BOOST_HEADERS=1"
        LINK_FLAGS "-s USE_BOOST_HEADERS=1 -s WASM=1"
        -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'
        -s LLD_REPORT_UNDEFINED)