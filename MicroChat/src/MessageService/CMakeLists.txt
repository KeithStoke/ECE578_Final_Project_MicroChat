add_executable(
    MessageService
    MessageService.cpp
    ${THRIFT_GEN_CPP_DIR}/MessageService.cpp
    ${THRIFT_GEN_CPP_DIR}/DatabaseService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	MessageService PRIVATE
    ${MONGOC_INCLUDE_DIRS}
    /usr/local/include/jwt
    /usr/local/include/jaegertracing
)

target_link_libraries(
    MessageService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
    jaegertracing
    OpenSSL::SSL
)

install(TARGETS MessageService DESTINATION ./)