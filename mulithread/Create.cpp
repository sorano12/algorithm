#include<iostream>
#include<thread>
using namespace std;

void thread_1(){
    cout << "子线程1" << endl;
}

void thread_2(int x){
    cout << "x:" << x << endl;
    cout << "子线程2" << endl;
}

int main(){
    thread first(thread_1);
    thread second(thread_2,100);
    cout << "主线程" << endl;
    //first.detach();
    //second.detach();
    cout << "子线程结束" << endl;
    return 0;
}