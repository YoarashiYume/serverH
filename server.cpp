
#include "server.h"

void Server::mainFunc()
{
    while (isWork.load())
    {
        if(sock.getConnection())
            if (isWork.load())
                thPool.addTask(sock);
    }
}

Server::Server(std::string _addr, uint32_t _port, bool _isNonBlocking)
{
    sock.upDate(_addr,_port,_isNonBlocking);
    isWork.store(true);
}

bool Server::start()
{
    if(!sock.listenPort())
        return false;
    thPool.start();
    worker = std::thread(&Server::mainFunc,this);
    return true;
}

void Server::stop()
{
    isWork.store(false);
    thPool.stop();
    sock.closeInnerConnection();
    worker.join();
}

void Server::addMethod(std::string_view _request, Pool::funcType _func)
{
    thPool.addFunc(_request,_func);
}
