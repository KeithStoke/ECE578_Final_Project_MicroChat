add_executable(
    DatabaseService
    DatabaseService.cpp
    ${THRIFT_GEN_CPP_DIR}/DatabaseService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	DatabaseService PRIVATE
)

target_link_libraries(
    DatabaseService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)

install(TARGETS DatabaseService DESTINATION ./)