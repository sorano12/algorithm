#include<iostream>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<thread>

using namespace std;
mutex mtx;
condition_variable cv;
string flag="A";


void printA(){
    while(true){
        unique_lock<mutex> locker(mtx);
        while(flag=="B"){
            cv.wait(locker);
        }
        this_thread::sleep_for(chrono::seconds(1));
        cout << "A" << endl;
        flag="B";
        cv.notify_all();
    }
}

void printB(){
    while(true){
        unique_lock<mutex> locker(mtx);
        while(flag=="A"){
            cv.wait(locker);
        }
        this_thread::sleep_for(chrono::seconds(1));
        cout << "B" << endl;
        flag="A";
        cv.notify_all();
    }
}

int main(){
    thread t1(printA);
    thread t2(printB);
    t1.join();
    t2.join();
    
}
