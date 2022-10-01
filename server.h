#ifndef SERVER_H
#define SERVER_H

#include "pool.h"
#include "socket_m.h"

/**
\brief Class gets outer connection and push it in processing pool
*/
class Server final
{
private:
	/**
	\brief Method gets new connection and pushs task to ThreadPool
	*/
    void mainFunc();
	
    Socket_M sock;///< Server socket
    Pool thPool;///< ThreadPool
    std::thread worker;///< Main server thread in which the connection takes place
    std::atomic<bool> isWork;///< server current state
public:
	/**
	\brief handler function type
	\param Package - received REST request
	\return std::string server response to request
	*/
    using servFuncType = std::function<std::string(Package)>; 
	/**
	\brief Constructor
	\param _addr address to which the socket will be bound.
	\param _port server port
	\param _isNonBlocking whether waiting for a socket connection should block code execution
	*/
    Server(const std::string& _addr, const uint32_t _port,const bool _isNonBlocking = false);
	/**
	\brief Method starts server
	*/
    bool start();
	/**
	\brief Method stops server
	*/
    void stop();
	/**
	\brief Method adding request processing
	\param _request request on which the function is executed
	\param _returnType response message type
	\param _func handler function
	*/
    void addMethod(const std::string_view _request,const std::string_view _returnType ,servFuncType _func);
};

#endif // SERVER_H
