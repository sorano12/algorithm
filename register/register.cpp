#include<iostream>
#include<functional>
#include<memory>

using namespace std;

typedef function<void(int i)> call_back_;

class A{
public:
    A(){}
    ~A(){}
    void handle(int i){
        cout << "class:A handle" << endl;
        cb_(i);
    }

    void register_(call_back_ func){
        cb_=move(func);
    }
private:
    call_back_ cb_;
};

class B{
public:
    B(A& ca){
        ca.register_([this](int i){B::handle(i);});
    }
    ~B(){}
    void handle(int i){
        cout << "B,handle message" << i << endl;
    }    
};

int main(){
    A testa;
    B testb(testa);

    testa.handle(10);
}
