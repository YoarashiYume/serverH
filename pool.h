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
#include "Randomizer.h"
#include "socket_m.h"

class Pool
{
public:
    using funcType = std::function<std::string(Package)>;
    void answerFunc(Socket_M& sock,Package& pack, std::string msg);
    Pool();
    void addFunc(std::string_view _request, funcType _func);
    void addTask(Socket_M sock);
    void start();
    void stop();
    ~Pool();
private:
    std::vector<std::thread> threads;
    std::unordered_map<std::string, funcType> funcList;
    std::stack<Socket_M> taskList;
    std::mutex mtx, supMtx;
    std::condition_variable cv;
    std::atomic<bool> isWork;
    void work();
};

#endif // POOL_H
