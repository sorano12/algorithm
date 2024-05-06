#include<iostream>
#include<vector>
#include<string>

using namespace std;

//主串
string a="qwioehaobcoabvoahoaababacdpuvhsdubfwe";

//模式串
string b="ababacd";

int main(){
    int n=b.length();
    //构造next_数组
    vector<int> next_(n,-1);
    int k=-1; //标志目前的最长匹配前缀末尾下标
    for(int i=0;i<n;i++){
        while(k!=-1&&b[i]!=b[k+1]){
            k=next_[k];
        }
        if(b[k+1]==b[i]){
            ++k;
        }
        next_[i]=k;
    }

    //利用next_这个部分匹配表进行匹配
    int m=a.length();
    int j=0; //当前模式串匹配位置
    bool flag=false;
    for(int i=0;i<m;i++){
        if(j>0&&b[j]!=a[i]){
            j=next_[j-1]+1;
        }
        if(b[j]==a[i]){
            ++j;
        }
        if(j==n){
            cout << "successed! " << i-n+1 <<endl;
            flag=true;
            break;
        }
    }
    if(!flag)cout << "failed!" << endl;
}