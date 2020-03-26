#include <iostream>

struct Node
{
    Node(int value): value(value),next(nullptr){}
    int value;
    Node *next;
};

class Queue{
public:
    void Enqueue(int val);
    int Dequeue();
    bool isEmpty() const;

    Queue(): head(nullptr),tail(nullptr){}
    ~Queue();

private:
    Node *head,*tail;
};

Queue::~Queue() {
    while(!isEmpty()){
        Dequeue();
    }
}


void Queue::Enqueue(int val) {

    Node* newNode=new Node(val);
    if(isEmpty()){
        tail=head=newNode;
        return;
    }
    tail->next=newNode;
    tail=newNode;
}

int Queue::Dequeue() {
    if(isEmpty()){
        return -1;
    }

    int value=head->value;
    Node* tmp=head;
    head=head->next;
    delete tmp;

    if(head == nullptr)
        tail= nullptr;
    return value;


}


bool Queue::isEmpty() const {
    return head== nullptr && tail==nullptr;
}

int main() {

    int *a=new int();
    int *b=new int();
    int *c=new int();
    int count=0;
    while((count=scanf("%d%d%d", a,b,c))!=3){
        std::cout<<count;
    }
    std::cout<<count;
//    Queue queue;
//
//    int n=0;
//    std::cin>>n;
//    for(int i=0;i<n;i++){
//        int op=0, val=0;
//        std::cin>>op>>val;
//
//        switch (op){
//            case 3: {
//                queue.Enqueue(val);
//                break;
//            }
//            case 2:{
//                int qValue=queue.Dequeue();
//                if(qValue!=val){
//                    std::cout<<"NO"<<std::endl;
//                    return 0;
//                }
//                break;
//            }
//
//            default:break;
//        }
//    }
//    std::cout<<"YES"<<std::endl;
    return 0;
}