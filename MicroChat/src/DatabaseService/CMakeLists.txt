add_executable(
    DatabaseService
    DatabaseService.cpp
    ${THRIFT_GEN_CPP_DIR}/DatabaseService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	DatabaseService PRIVATE
    ${MONGOC_INCLUDE_DIRS}
    /usr/local/include/jwt
    /usr/local/include/jaegertracing
)

target_link_libraries(
    DatabaseService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
    jaegertracing
    OpenSSL::SSL
    ${MONGOC_LIBRARIES}
)

install(TARGETS DatabaseService DESTINATION ./)