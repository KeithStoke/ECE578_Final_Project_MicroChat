include("../cmake/Findthrift.cmake")
include("../cmake/FindLibevent.cmake")

find_package(libmongoc-1.0 1.13 REQUIRED)
find_package(nlohmann_json 3.5.0 REQUIRED)
find_package(Threads)
find_package(OpenSSL REQUIRED)
find_package(amqpcpp REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.54.0 REQUIRED COMPONENTS log log_setup)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif()

set(THRIFT_GEN_CPP_DIR ../../gen-cpp)

add_subdirectory(UserService)
add_subdirectory(MessageService)
add_subdirectory(FriendRecommendationService)
add_subdirectory(DatabaseService)
