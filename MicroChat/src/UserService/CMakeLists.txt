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

install(TARGETS UserService DESTINATION ./)