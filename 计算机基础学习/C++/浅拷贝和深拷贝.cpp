#include<iostream>
#include<string.h>

using namespace std;

class TestClassA{
public:
    TestClassA(int isize):m_isize(isize){
        m_pkdata=new char[m_isize];

    }

    TestClassA(const TestClassA& rta):m_isize(rta.m_isize){
        m_pkdata=new char[m_isize];
        memcpy(m_pkdata,rta.m_pkdata,m_isize);
    }

    ~TestClassA(){
        if(m_pkdata){
            delete[] m_pkdata;
            m_pkdata=nullptr;
        }
    }




    int m_isize;
    char* m_pkdata;
};

