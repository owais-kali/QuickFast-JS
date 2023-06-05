set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/client/vendor)

#/media/owais/LinuxHDD1/Freelancer/BitZee/QuickFast-JS/tests/boost-test/client/vendor
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
GET_FILES(XERCES_SRC_HPP src .hpp)

list(REMOVE_ITEM XERCES_SRC_CPP ${XERCES_SRC_CPP}/src/xercesc/util/FileManagers/WindowsFileMgr.cpp)

#//////////////////////Xerces-END/////////////

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

set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
set_target_properties(boost-test PROPERTIES LINK_FLAGS "-s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")