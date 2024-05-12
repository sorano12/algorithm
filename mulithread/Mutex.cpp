#include <iostream>
#include <thread>
#include <atomic>
#include <time.h>
#include <mutex>
#include<chrono>

#define MAX 1000
#define THREAD_COUNT 20000

//std::atomic<int> total(0);
int total=0;
std::mutex mtx;

void threadTask()
{
    //mtx.lock();
    for (int i = 0; i < MAX; i++)
    {
        total++;
    }
    //mtx.unlock();
}

int main()
{
    auto start=std::chrono::steady_clock::now();
    std::thread t[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        t[i] = std::thread(threadTask);
    }
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        t[i].join();
    }

    auto finish=std::chrono::steady_clock::now();
    std::chrono::duration<double> duration=finish-start;
    std::cout << "result:" << total << std::endl; // 计算结果
    std::cout << "duration:" << duration.count() << "ms" << std::endl; // 计算耗时

    return 0;
}
