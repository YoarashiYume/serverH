#include "socket_m.h"

Socket_M::Socket_M(std::string _addr, uint32_t _port,bool _mode)
{
    upDate(_addr,_port,_mode);
}

Socket_M::Socket_M(const Socket_M &other)
{
    this->addr = other.addr;
    this->cAddr = other.cAddr;
    this->iMode = other.iMode;
    this->mSocket = other.mSocket;
    this->connetcion = other.connetcion;
    this->sizeOfAddr = other.sizeOfAddr;
}

Socket_M::Socket_M(Socket_M &&other)
{
    this->addr = other.addr;
    this->cAddr = other.cAddr;
    this->iMode = other.iMode;
    this->mSocket = other.mSocket;
    this->sizeOfAddr = other.sizeOfAddr;
    this->connetcion = other.connetcion;
    other.iMode = other.connetcion = other.sizeOfAddr = other.mSocket = 0;
    other.addr = other.cAddr = {};
}

Socket_M &Socket_M::operator=(const Socket_M &other)
{
    if (&other == this)
        return *this;
    this->addr = other.addr;
    this->cAddr = other.cAddr;
    this->iMode = other.iMode;
    this->mSocket = other.mSocket;
    this->connetcion = other.connetcion;
    this->sizeOfAddr = other.sizeOfAddr;
    return *this;

}
Socket_M &Socket_M::operator=(Socket_M &&other)
{
    if (&other == this)
        return *this;
    this->addr = other.addr;
    this->cAddr = other.cAddr;
    this->iMode = other.iMode;
    this->mSocket = other.mSocket;
    this->sizeOfAddr = other.sizeOfAddr;
    this->connetcion = other.connetcion;
    other.iMode = other.connetcion = other.sizeOfAddr = other.mSocket = 0;
    other.addr = other.cAddr = {};
    return *this;
}
void Socket_M::upDate(std::string _addr, uint32_t _port, bool _mode)
{
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = inet_addr(_addr.c_str());
    this->addr.sin_port = htons(_port);
    this->iMode = _mode;
    this->sizeOfAddr = sizeof (sizeOfAddr);
    closeInnerConnection();
    closeOuterConnection();
}



int Socket_M::listenPort()
{
    int temp =1;
    if (mSocket = socket(AF_INET,SOCK_STREAM,0); mSocket !=0)
    {
        if (iMode)
            fcntl(mSocket, F_SETFL, O_NONBLOCK);
        if (setsockopt(mSocket,SOL_SOCKET,SO_REUSEADDR ,&temp,sizeof (int))>=0)
            if (bind(mSocket,(struct sockaddr*)&addr,sizeof (addr))>=0)
                if (listen(mSocket,SOMAXCONN) >=0)
                    return  1;
    }
    return 0;
}
bool Socket_M::getConnection()
{

    cAddr.sin_addr.s_addr = INADDR_ANY;
    unsigned int cSize = sizeof (cAddr);
    connetcion = accept(mSocket,(struct sockaddr*)&cAddr,&cSize);
    return connetcion >=0;
}

Package Socket_M::getMessage() const
{
    std::string msg(1024,' ');
    recv(connetcion,msg.data(),msg.size(),NULL);
    std::reverse(msg.begin(),msg.end());
    msg.erase(0,msg.find_first_not_of("  "));
    std::reverse(msg.begin(),msg.end());
    return std::move(Package(msg));
}

void Socket_M::sendMessage(std::string str) const
{
    send(connetcion, str.data(), str.length(), NULL);
}

void Socket_M::closeOuterConnection()
{
    close(connetcion);
}
void Socket_M::closeInnerConnection()
{
    send(mSocket, "", 0, NULL);
    close(mSocket);
}
