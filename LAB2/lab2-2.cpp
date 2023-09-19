#include <iostream>
using namespace std;
typedef struct treeNode *itemType;

struct treeNode {
    char info; 
    treeNode *l, *r;
};

struct treeNode *x, *z;

class Stack {
public:
    Stack(int max=100) {
        stack = new itemType[max];
        p = 0;
    }

    ~Stack() {
        delete stack;
    }

    inline void push(itemType v) {
        stack[p++] = v;
    }

    inline itemType pop() {
        return stack[--p];
    }

    inline int empty() {
        return !p;
    }

private:
    itemType *stack;
    int p;
};

void visit(struct treeNode *t) {
    cout << t->info << " ";
}

class Queue {
public:
    Queue(int max=100) {
        queue = new itemType[max];
        head = 0, tail = 0, size = max;
    }
    ~Queue() {
        delete queue;
    }
    void put(itemType v);
    itemType get();
    int empty();
private:
    itemType *queue;
    int head, tail, size;
};

void Queue::put(itemType v) 
{
    queue[tail++] = v;
    if (tail > size) 
        tail = 0; 
}

itemType Queue::get() 
{ 
    itemType t = queue[head++]; 
    if (head > size) 
        head = 0;
    return t; 
} 

int Queue::empty() { 
    return head == tail; 
}

void traverse(struct treeNode *t) 
{
    Queue queue;
    queue.put(t); 
    while (!queue.empty()) { 
        t = queue.get(); 
        visit(t); 
        if (t->l != z) 
            queue.put(t->l); 
        if (t->r != z) 
            queue.put(t->r); 
    } 
}

int main()
{
    char c;
    Stack stack(50);
    z = new treeNode;
    z -> l = z;
    z -> r = z;

    while ((c = cin.get()) != '\n') {
        while (c == ' ')
            cin.get(c);
        x = new treeNode;
        x -> info = c;
        x -> l = z;
        x -> r = z;
        if (c == '+' || c == '*' || c == '-') {
            x -> r = stack.pop();
            x -> l = stack.pop();
        }
        stack.push(x);
    }
    traverse(stack.pop());
    cout << endl;
    return 0;
}