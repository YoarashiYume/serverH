#ifndef POOL_H
#define POOL_H

#include <thread>
#include <vector>
#include <stack>
#include <condition_variable>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <atomic>
#include "socket_m.h"

/**
\brief ThreadPool for treatment incoming socket
*/
class Pool
{
public:
	/**
	\brief handler function type
	\param Package received REST request
	\param Socket_M socket from which the request came
	*/
    using funcType = std::function<void(Socket_M,Package)>;
	/**
	\brief Constructor
	Sets the pool size
	*/
    Pool();
	/**
	\brief Method adding request processing
	\param _request request on which the function is executed
	\param _func handler function
	*/
    void addFunc(std::string_view _request, funcType _func);
	/**
	\brief Method adds a request to the processing queue
	\param sock socket from which the request came
	*/
    void addTask(Socket_M sock);
	/**
	\brief Method starts the ThreadPool
	*/
    void start();
	/**
	\brief Method stops the ThreadPool
	*/
    void stop();
	/**
	\brief Destructor
	waiting for puts to complete
	*/
    ~Pool();
private:
    std::vector<std::thread> threads;///< array of processing threads
    std::unordered_map<std::string, funcType> funcList;///< array of handler functions
    std::stack<Socket_M> taskList;///< array of requests
    std::mutex mtx, ///< for condition_variable
	supMtx;///< guarantees the correct change of the list of tasks
    std::condition_variable cv;///< controls the correct launch of threads for executing tasks
    std::atomic<bool> isWork;///< ThreadPool current state
    
	/**
	\brief Threaded method for processing tasks
	*/
	void work();
};

#endif // POOL_H
