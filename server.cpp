
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

Server::Server(const std::string& _addr, const uint32_t _port,const bool _isNonBlocking)
{
    sock.upDate(_addr,_port,_isNonBlocking);
    isWork.store(true);
}

bool Server::start()
{
    if(!sock.listenPort())
        return false;
    thPool.addFunc("",[](Socket_M sock,Package param)-> void{ //Add function handler for a non-existent request,if it doesn`t exist
        sock.sendMessage(param.getProtocol()+ " 200 OK\r\nConnection: close\r\n");
        sock.closeOuterConnection();
    });
    thPool.start();
    worker = std::thread(&Server::mainFunc,this);
    return true;
}

void Server::stop()
{
    isWork.store(false);
    thPool.stop();
    sock.sendEmptyInnerMessage();
    sock.closeInnerConnection();
    worker.join();
}

void Server::addMethod(const std::string_view _request,const std::string_view _returnType ,servFuncType _func)
{
    thPool.addFunc(_request,[_returnType,_func](Socket_M sock,Package param)->void{
        std::string msg =_func(param);
        if (!_returnType.empty())
            sock.sendMessage(param.getProtocol()+ " 200 OK\r\nConnection: close\r\nContent-Length: "
            + std::to_string(msg.size()) + "\r\n"+_returnType.data()+"\r\n\r\n"+ msg.data());
        else
            sock.sendMessage(param.getProtocol()+ " 200 OK\r\nConnection: close\r\n");
        sock.closeOuterConnection();
    });
}
