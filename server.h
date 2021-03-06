#ifndef SERVER_H
#define SERVER_H
/*
 * Gets outer connection and push it in processing pool
*/
#include "pool.h"
#include "socket_m.h"


class Server
{
private:
    void mainFunc();
    Socket_M sock;
    Pool thPool;
    std::thread worker;
    std::atomic<bool> isWork;
public:
    using servFuncType = std::function<std::string(Package)>;
    Server(std::string _addr, uint32_t _port,bool _isNonBlocking = false);
    bool start();
    void stop();
    void addMethod(std::string_view _request,std::string_view _returnType ,servFuncType _func);
};

#endif // SERVER_H
