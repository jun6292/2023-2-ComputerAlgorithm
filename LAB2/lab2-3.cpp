#include <iostream>
using namespace std;
typedef struct treeNode* itemType;

struct treeNode {
    char info; 
    struct treeNode *l, *r;
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

bool traverse(struct treeNode *t, int level, char find)
{
    if (find == '+' || find == '*' || find == '-' || find == '/')
        exit(0);
    if (t != z) {
        if (t->info == find) {
            cout << level << '\n';
            return true;
        }
        return (traverse(t->l, level + 1, find) || traverse(t->r, level + 1, find));
    }
    else {
        return false;
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

    char find;  // 찾고자 하는 피연산자
    cin >> find;
    if (!traverse(stack.pop(), 1, find))
        cout << "\nNot Found\n";

    cout << endl;
    return 0;
}