#include<iostream>
#include<algorithm>
using namespace std;

class Heap{
private:
  int a[1024];//规定从1开始存储
  int n;
  int count;
public:
  Heap(int num=1024):n(num),count(0){}

  void insert(int data){
    if(count>=n)return;
    ++count;
    a[count]=data;
    int i=count;
    while(i/2>0&&a[i]>a[i/2]){
        swap(a[i],a[i/2]);
        i=i/2;
    }
  }

  void headpify(int n,int i){
    //堆化
    while(true){
        int maxPos=i;
        if(i*2<=n&&a[i]<a[i*2])maxPos=i*2;//跟左孩子比较，小于则将最大指向左孩子
        if(i*2+1<=n&&a[maxPos]<a[i*2+1])maxPos=i*2+1;//左与父大者和右孩子比较，得到三者大值
        if(maxPos==i)break;//父亲最大，已经满足大顶堆条件，退出
        swap(a[i],a[maxPos]);//大者上移，父亲下沉，直到到指定位置
        i=maxPos;
    }
  }

  int removeMax(){
    if(count==0)return -1;
    a[1]=a[count];//交换最后一个元素和堆顶元素
    --count; //堆大小-1
    headpify(count,1); //下沉堆顶
  }

  void buildHeap(){
    for(int i=n/2;i>=1;--i){
        headpify(n,i);//自底而上建堆
    }
  }

  void sort(){
    buildHeap();
    int k=n;
    while(k>1){
        swap(a[1],a[k]);
        --k;
        headpify(k,1);
    }
  }

  void print(){
    for(int i=1;i<=n;i++){
        cout << a[i] << ' ';
        if(i%15==0)cout << endl;
    }
  }
  void equals(int b[],int cnt){
    n=cnt;
    for(int i=1;i<=n;i++){
        a[i]=b[i-1];
    }

  }
};

int main(){
    int b[10]{6,4,10,9,15,29,63,98,21,1};
    Heap heap;
    heap.equals(b,10);
    heap.buildHeap();
    heap.sort();
    heap.print();
}