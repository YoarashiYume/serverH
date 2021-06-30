#ifndef SOCKET_M_H
#define SOCKET_M_H
/*
 *  Small api on raw socket
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include "package.h"


class Socket_M
{
private:
    struct sockaddr_in addr, clientAddr;
    uint32_t sizeOfAddr, isNonBlocking, mSocket;
    int32_t connetcion;
public:
    Socket_M(std::string _addr, uint32_t _port, bool _isNonBlocking = 0);
    Socket_M() : Socket_M("127.0.0.1",8080) {};
    Socket_M(const Socket_M& other);
    Socket_M(Socket_M&& other);
    Socket_M& operator=(const Socket_M& other);
    Socket_M& operator=(Socket_M&& other);
    void upDate(std::string _addr, uint32_t _port, bool _isNonBlocking = 0);
    int listenPort();
    bool getConnection();
    Package getMessage() const;
    void sendMessage(std::string str) const;
    void closeOuterConnection();
    void closeInnerConnection();
    void sendEmptyInnerMessage();
};

#endif // SOCKET_M_H
