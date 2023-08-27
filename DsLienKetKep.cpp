#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next;
    Node *previous;
};

struct DoubleLinkedList
{
    Node *head; // luôn trỏ tới phần tử đầu tiên
    Node *tall; // Luôn trỏ tới phần tử cuối
};

void init(DoubleLinkedList &ls)
{
    ls.head = NULL;
    ls.tall = NULL;
}

Node *createNode(int x)
{
    Node *p = new Node;
    p->value = x;
    p->next = NULL;
    p->previous = NULL;

    return p;
}

void addFirts(DoubleLinkedList &ls, int x)
{
    Node *p = createNode(x);
    if (ls.head == NULL)
    {
        ls.head = ls.tall = p;
    }
    else
    {
        p->next = ls.head;
        ls.head->previous = p;
        ls.head = p;
    }

    
}

void outPutleftToRight(const DoubleLinkedList ls)
{
    Node *p = ls.head;
    while (p != NULL)
    {
        cout << p->value << "\t";
        p = p->next;
    }
}

int main()
{
    DoubleLinkedList ls;
    init(ls);
    addFirts(ls, 10);
    addFirts(ls, 12);
    addFirts(ls, 100);
    outPutleftToRight(ls);
    return 0;
}
