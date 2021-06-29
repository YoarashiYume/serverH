#include "pool.h"

Pool::Pool()
{
    int newSize=2*(std::thread::hardware_concurrency()-1);
    threads.resize( newSize > 0 ? newSize : 1);
    isWork.store(true);
}

void Pool::addFunc(std::string_view _request, funcType _func)
{
    funcList.emplace(std::make_pair(_request.data(),_func));
}
void Pool::work()
{
    while (true)
    {
        std::unique_lock<std::mutex> unqM(mtx);
        cv.wait((unqM));
        if (!isWork.load())
            return;
        else
        {
            supMtx.lock();
            Socket_M sock = std::move(taskList.top());
            taskList.pop();
            supMtx.unlock();
            Package param (sock.getMessage());
            if (funcList.contains(param.getUri()))
                funcList.at(param.getUri())(sock,param);
            else                                        //if there is no function - send empty answer and close socket
                funcList.at("")(sock,param);
        }
    }


}
void Pool::addTask(Socket_M sock)
{
    taskList.emplace(sock);
    cv.notify_one();
}

void Pool::start()
{
    for(auto& el : threads)
        el = std::thread(&Pool::work, this);
}

void Pool::stop()
{
    isWork.store(false);
}

Pool::~Pool()
{
    isWork.store(false);
    cv.notify_all();
    for(auto& el : threads)
        if (el.joinable())
            el.join();
    while (!taskList.empty())
    {
        taskList.top().closeOuterConnection();
        taskList.pop();
    }
}
