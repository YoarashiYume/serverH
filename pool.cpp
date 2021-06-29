#include "pool.h"

void Pool::answerFunc(Socket_M &sock,Package& pack, std::string msg)
{
    sock.sendMessage(pack.getProtocol());
    sock.sendMessage(" 200 OK\r\nConnection: close\r\nContent-Length: ");
    sock.sendMessage(std::to_string(msg.length()));
    sock.sendMessage("\r\nContent-Type: text/html\r\n\r\n");
    sock.sendMessage(msg);

}

Pool::Pool()
{
    int newSize=2*(std::thread::hardware_concurrency()-1);
    threads.resize( newSize > 0 ? newSize : 1);
    isWork.store(true);
}

void Pool::addFunc(std::string_view _request, funcType _func)
{
    funcList[_request.data()] = _func;
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
            std::string str;
            if (funcList.contains(param.getUri()))
                str = funcList.at(param.getUri())(param);
            else
                str = "Invalid request";
            answerFunc(sock,param,str);
            sock.closeOuterConnection();
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
