set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Public")

# Create QUICK_FAST_DECODER with custom source files
add_library(QUICK_FAST_DECODER STATIC)

set(QUICK_FAST_ROOT_DIR ${CMAKE_SOURCE_DIR}/libs/quickfast)
set(QUICK_FAST_SOURCE_DIR ${QUICK_FAST_ROOT_DIR}/src)
#Function to Glob all files by extension
function(GET_FILES NAME DIR EXTENSION)
    file(GLOB_RECURSE FILES
            ${QUICK_FAST_SOURCE_DIR}/${DIR}/*${EXTENSION}
            )
    set(${NAME} ${FILES} PARENT_SCOPE)
endfunction()

#CPP Source Files
GET_FILES(Application_CPP Application .cpp)
GET_FILES(Codecs_CPP Codecs .cpp)
GET_FILES(Common_CPP Common .cpp)
GET_FILES(Communication_CPP Communication .cpp)
GET_FILES(Messages_CPP Messages .cpp)

#Header Directory
target_include_directories(QUICK_FAST_DECODER PRIVATE
        ${QUICK_FAST_SOURCE_DIR}
        )

target_sources(QUICK_FAST_DECODER
        PRIVATE
        ${Codecs_CPP}
        )

target_compile_definitions(QUICK_FAST_DECODER
        PUBLIC
        BOOST_BIND_GLOBAL_PLACEHOLDERS
        ASIOSERVICE_FWD_H
        DATASOURCE_FWD_H
        DECIMAL_H)