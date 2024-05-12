#include<iostream>
#include<atomic>
#include<thread>

int a=0;

class SpinLock{
public:
    void lock(){
        while(flag.test_and_set(std::memory_order_acquire));

    }
    void unlock(){
        flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag=ATOMIC_FLAG_INIT;
};

SpinLock spinlock;

void add_(){
    spinlock.lock();
    for(int i=0;i<10000;i++)a++;
    spinlock.unlock();
}

int main(){
    std::thread thread1(add_);
    std::thread thread2(add_);

    thread1.join();
    thread2.join();

    std::cout << a << std::endl;
    return 0;

}

