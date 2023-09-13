#include <iostream>
using namespace std;
typedef double itemType;

class Stack2
{
public:
    Stack2() {
        head = new node();
        head -> next = nullptr;
    }

    ~Stack2() {
        delete head;
    }

    void push(itemType v) {
        z = new node();
        z -> key = v;
        z -> next = head;
        head = z;
    }

    itemType pop() {
        itemType item;
        item = head -> key;
        head = head -> next;
        return item;
    }

    int empty() {
        if (head -> next == nullptr)
            return 1;
        else
            return 0;
    }

private:
    struct node {
        itemType key;
        struct node *next;
    };
    struct node *head, *z;  // head는 stack의 top
};

int main()
{
    char c;
    Stack2 st;
    double x;
    while ((c = cin.get()) != '\n') {
        x = 0;
        while (c == ' ')
            cin.get(c);
        
        if (c == '+')
            x = st.pop() + st.pop();
        if (c == '*')
            x = st.pop() * st.pop();
        if (c == '-') {
            double a = st.pop();
            double b = st.pop();
            x = b - a;
        }
        if (c == '/') {
            double a = st.pop();
            double b = st.pop();
            x = b / a;
        }
        while (c >= '0' && c <= '9') {
            x = 10 * x + (c - '0');
            cin.get(c);
        }
        st.push(x);
    }
    
    double result = st.pop();
    if (result - (int)result == 0) {
        cout << result << '\n';
    }
    else {
        cout << fixed;
        cout.precision(2);
        cout << result << '\n';
    }
}