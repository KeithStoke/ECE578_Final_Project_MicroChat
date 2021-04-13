#ifndef MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H
#define MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>
#include <vector>
#include <iomanip>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <nlohmann/json.hpp>
#include <jwt/jwt.hpp>
#include <random>
#include "../../gen-cpp/FriendRecommendationService.h"
#include "../../gen-cpp/DatabaseService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace microchat{

    class FriendRecommendationServiceHandler : public FriendRecommendationServiceIf {
 public:
  FriendRecommendationServiceHandler(
      std::mutex *,
        const std::string &,
        ClientPool<ThriftClient<DatabaseServiceClient>> *);
  ~FriendRecommendationServiceHandler() override=default;

  void ping(std::string &_return, const std::string &text) override;
  void GetFriendRecommendations(std::vector<std::string> & _return, const std::string& username) override;
  void onLogin(std::string & _return, const std::string& username) override;
   private:
    std::string _machine_id;
    std::mutex *_thread_lock;
    ClientPool<ThriftClient<DatabaseServiceClient>> *_database_client_pool;
};
  /*
 * The following code which obtaines machine ID from machine's MAC address was
 * inspired from https://stackoverflow.com/a/16859693.
 */
  u_int16_t HashMacAddressPid(const std::string &mac)
  {
    u_int16_t hash = 0;
    std::string mac_pid = mac + std::to_string(getpid());
    for (unsigned int i = 0; i < mac_pid.size(); i++)
    {
      hash += (mac[i] << ((i & 1) * 8));
    }
    return hash;
  }
int GetMachineId(std::string *mac_hash)
  {
    std::string mac;
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0)
    {
      LOG(error) << "Unable to obtain MAC address";
      return -1;
    }

    struct ifconf conf
    {
    };
    char ifconfbuf[128 * sizeof(struct ifreq)];
    memset(ifconfbuf, 0, sizeof(ifconfbuf));
    conf.ifc_buf = ifconfbuf;
    conf.ifc_len = sizeof(ifconfbuf);
    if (ioctl(sock, SIOCGIFCONF, &conf))
    {
      LOG(error) << "Unable to obtain MAC address";
      return -1;
    }

    struct ifreq *ifr;
    for (
        ifr = conf.ifc_req;
        reinterpret_cast<char *>(ifr) <
        reinterpret_cast<char *>(conf.ifc_req) + conf.ifc_len;
        ifr++)
    {
      if (ifr->ifr_addr.sa_data == (ifr + 1)->ifr_addr.sa_data)
      {
        continue; // duplicate, skip it
      }

      if (ioctl(sock, SIOCGIFFLAGS, ifr))
      {
        continue; // failed to get flags, skip it
      }
      if (ioctl(sock, SIOCGIFHWADDR, ifr) == 0)
      {
        mac = std::string(ifr->ifr_addr.sa_data);
        if (!mac.empty())
        {
          break;
        }
      }
    }
    close(sock);

    std::stringstream stream;
    stream << std::hex << HashMacAddressPid(mac);
    *mac_hash = stream.str();

    if (mac_hash->size() > 3)
    {
      mac_hash->erase(0, mac_hash->size() - 3);
    }
    else if (mac_hash->size() < 3)
    {
      *mac_hash = std::string(3 - mac_hash->size(), '0') + *mac_hash;
    }
    return 0;
  }
FriendRecommendationServiceHandler::FriendRecommendationServiceHandler(
     std::mutex *thread_lock,
      const std::string &machine_id,
      ClientPool<ThriftClient<DatabaseServiceClient>> *database_client_pool) 
{
    _thread_lock = thread_lock;
    _machine_id = machine_id;
    _database_client_pool = database_client_pool;
}

void FriendRecommendationServiceHandler::ping(std::string &_return, const std::string &text){
    std::cout << "Ping says " << text << std::endl;
    _return = "Pong from FriendRecommendationService";
}

void FriendRecommendationServiceHandler::GetFriendRecommendations(std::vector<std::string> & _return, const std::string& username){
    printf("get friend recommendations RPC");
}

void FriendRecommendationServiceHandler::onLogin(std::string & _return, const std::string& username)
{
    std::cout << "On Login from Friend recommendation" <<std::endl;

    auto database_client_wrapper = _database_client_pool->Pop();
    if (!database_client_wrapper)
    {
      ServiceException se;
      se.errorCode = ErrorCode::SE_THRIFT_CONN_ERROR;
      se.message = "Failed to connect to database-service";
      throw se;
    }
    auto database_client = database_client_wrapper->GetClient();
}

} //namespace microchat

#endif //MICROCHAT_FRIENDRECOMMENDATIONHANDLER_H