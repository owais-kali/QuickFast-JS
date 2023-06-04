add_executable(boost-test
        boost-test.cpp)

target_include_directories(boost-test
        PRIVATE
        ${QUICKFAST_SRC}/src
        )

#///////////////////////Xerces/////////////////////////////////////
#XercesC_SRC_DIR
function(GET_FILES NAME DIR EXTENSION)
    file(GLOB_RECURSE FILES
            ${XercesC_SRC_DIR}/${DIR}/*${EXTENSION}
            )
    set(${NAME} ${FILES} PARENT_SCOPE)
endfunction()

#CPP Source Files
GET_FILES(XERCES_SRC_CPP src .cpp)
message(XERCES_SRC_CPP ${XERCES_SRC_CPP})

list(REMOVE_ITEM XERCES_SRC_CPP ${XERCES_SRC_CPP}/src/xercesc/util/FileManagers/WindowsFileMgr.cpp)

#//////////////////////Xerces-END/////////////
target_sources(boost-test PRIVATE
        ${XERCES_SRC_CPP})

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
        )

#set_target_properties(boost-test PROPERTIES
#        COMPILE_FLAGS "-s USE_BOOST_HEADERS=1"
#        LINK_FLAGS "-s USE_BOOST_HEADERS=1 -s WASM=1"
#        -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'
#        -s LLD_REPORT_UNDEFINED)