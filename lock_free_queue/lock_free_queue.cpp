/*
暂时写一点逻辑性的东西，c++实现等有空去拜读herb sutter的Writing Lock-Free Code: A Corrected Queue再完善

无锁队列可以用链表或数组实现
链表里enqueue操作逻辑表述如下
n=new node();
n->value=data;
n->next=null;
while(true){//死循环
    tail=Q->tail;//取尾结点
    next=tail->next;
    
    //尾结点已经被移动，重新开始
    if(tail!=Q->tail)contine;

    //尾结点的next不为NULL，说明有进程已经CAS了tail->next
    //此时fetch tail知道next为NULL
    if(next!=NULL){
        CAS(Q->tail,tail,next);
        contine;
    }

    //tail位移动且next为NULL，满足插入条件，CAS他
    if(CAS(tail->next,next,n)==true)break;
}

//一切完成后置尾结点

dequeue逻辑则如下:
do{
    p=Q->head; //取头结点
    if(p->next==NULL){
        return ERR_EMPTY_QUEUE;
    }
    while(CAS(Q->head,p,p->next)!=true);//置head->next为新的dummy结点
    return p->next->value;
}

但是如上操作存在enqueue和dequeue在队列仅有一个结点时的冲突，会导致队列为空但是某一时刻head！=tail
所以要加入更严密的逻辑判定

dequeue:

while(true){
    //取出头结点尾结点和第一个元素的指针
    head=Q->head;
    tail=Q->tail;
    next=head->next;

    //Q->next移动，则重新取
    if(head!=Q->head)continue;

    //空队列
    if(head==tail&&next==NULL){
        return ERR_EMPTY_QUEUE;
    }

    //tail落后
    if(head!=tail&&next==NULL){
        CAS(Q->tail,tail,head);
        continue;
    }

    //cas成功，取出数据
    if(CAS(Q->head,head,next)==NULL){
        value=next->value;
        break;
    }
}
free(head); //释放老dummy结点
return value;


数组实现则采用ring buffer，head,tail和empty，也用cas实现无锁

cas的lock_free存在aba问题，这可以通过都变了 cas解决
就是额外维护一个cas访问的引用计数
*/