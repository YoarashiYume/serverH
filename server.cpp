
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

Server::Server(std::string _addr, uint32_t _port, bool _mode)
{
    sock.upDate(_addr,_port,_mode);
    isWork.store(true);
}

bool Server::start()
{
    if(!sock.listenPort())
        return false;
    thPool.start();
    std::thread th(&Server::mainFunc,this);
    worker = std::move(th);
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
