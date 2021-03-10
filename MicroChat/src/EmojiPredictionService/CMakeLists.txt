add_executable(
    EmojiPredictionService
    EmojiPredictionService.cpp
    ${THRIFT_GEN_CPP_DIR}/EmojiPredictionService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	EmojiPredictionService PRIVATE
)

target_link_libraries(
    EmojiPredictionService
    nlohmann_json::nlohmann_json
    ${THRIFT_LIB}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    Boost::log
    Boost::log_setup
)

install(TARGETS EmojiPredictionService DESTINATION ./)