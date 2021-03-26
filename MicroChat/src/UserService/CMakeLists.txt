add_executable(
    UserService
    UserService.cpp
    ${THRIFT_GEN_CPP_DIR}/UserService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	UserService PRIVATE
)

target_link_libraries(
    UserService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)
# Specify the minimum version you require.
find_package (mongoc-1.0 1.0 REQUIRED)

target_link_libraries (hello_mongoc PRIVATE mongo::mongoc_shared)

install(TARGETS UserService DESTINATION ./)