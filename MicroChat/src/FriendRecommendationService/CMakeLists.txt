add_executable(
    FriendRecommendationService
    FriendRecommendationService.cpp
    ${THRIFT_GEN_CPP_DIR}/FriendRecommendationService.cpp
    ${THRIFT_GEN_CPP_DIR}/microchat_types.cpp
)

target_include_directories(
	FriendRecommendationService PRIVATE
    ${MONGOC_INCLUDE_DIRS}
    /usr/local/include/jwt
    /usr/local/include/jaegertracing
)

target_link_libraries(
    FriendRecommendationService
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

install(TARGETS FriendRecommendationService DESTINATION ./)