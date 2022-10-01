#ifndef SOCKET_M_H
#define SOCKET_M_H

#include <netinet/in.h>// Internet Protocol family on linux
#include <arpa/inet.h>//socket struct on linux
#include <unistd.h> //"close()" to close a file descriptor
#include <string>
#include <fcntl.h> //fcntl func
#include "package.h"

/**
\brief Small api on raw socket
*/
class Socket_M final
{
private:
    struct sockaddr_in addr, ///< server information
	clientAddr;///< client information
    uint32_t sizeOfAddr, ///< size of sockaddr_in
	isNonBlocking,///< should the setsockopt function block further code execution until connected
	mSocket;///< socket descriptor
    int32_t connetcion;///< socket descriptor through which the client communicates with the server
public:
	/**
	\brief Constructor
	\param _addr address to which the socket will be bound.
	\param _port server port
	\param _isNonBlocking whether waiting for a socket connection should block code execution
	*/
    Socket_M(const std::string& _addr, const uint32_t _port, const bool _isNonBlocking = 0);
	/**
	\brief Default constructor
	ip = 127.0.0.1, port = 8080
	*/
    Socket_M() : Socket_M("127.0.0.1",8080) {};

	/**
	\brief Method that updates the socket information about the server
	\param _addr nre address to which the socket will be bound.
	\param _port new server port
	\param _isNonBlocking whether waiting for a socket connection should block code execution
	*/
    void upDate(const std::string& _addr, const uint32_t _port, const bool _isNonBlocking = 0);
	/**
	\brief Method that starts listening on a port
	*/
    int listenPort();
	/**
	\brief Method that establishes a connection
	\return true if connection was successful, otherwise false
	*/
    bool getConnection();
	/**
	\brief Method to read information from a socket
	\return Package containing the REST request
	*/
    Package getMessage() const;
	/**
	\brief Method to send response
	\param str response message
	*/
    void sendMessage(const std::string& str) const;
	/**
	\brief Method closes the client socket handle
	*/
    void closeOuterConnection();
	/**
	\brief Method closes the server socket handle
	*/
    void closeInnerConnection();
	/**
	\brief Method to send empty message to server
	Used to leave accept() func
	*/
    void sendEmptyInnerMessage();
};

#endif // SOCKET_M_H
