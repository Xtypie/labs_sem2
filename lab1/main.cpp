#include <iostream>
#include <math.h>
using namespace std;

bool Is3InNum(int n)
{
    while (n >= 10)
    {
        if ((n /= 10) == 3)
            return true;
    }
    return false;
}




struct Node
{
    int data;
    Node* left;
    Node* right;

};

void sortList(Node** sent) {
    if (*sent == nullptr) {
        return;
    }

    Node* current = *sent;
    Node *index = nullptr;
    int temp;

    do {
        index = current->right;

        while (index != *sent) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->right;
        }
        current = current->right;
    } while (current != *sent);
}

void DeleteWith3(Node* sent)
{
    Node * p = sent->right;
    while (p != sent)
    {
        if (Is3InNum(p->data))
        {
            Node * temp = p;
            p->right->left = p->left;
            p->left->right = p->right;
            p = p->right;
            delete temp;
        }
    }
}

bool DuplicateInList(Node* sent)
{
    Node* n = sent->right;
    Node* p = sent->right;
    while (n != sent)
    {
        while (p != sent)
        {
            if ((n->data == p->data) && (n != p))
                return true;
        }
    }
    return false;
}

void AddBack(Node* sent, int data)
{
    Node* p = new Node;
    p->data = data;
    p->left = sent->left;
    p->right = sent;
    sent->left->right = p;
    sent->left = p;
}

void PrintList(Node* sent)
{
    Node* p  = sent->right;
    while (p != sent)
    {
        cout << p->data << endl;
        p = p->right;
    }
}

void Clear(Node* sent)
{
    Node* p  = sent->right;
    while (p != sent)
    {
        Node* tmp = p;
        p = p->right;
        delete tmp;
    }
    sent->left = sent;
    sent->right = sent;
}


int main()
{
    Node* sent = new Node;
    sent->left = sent;
    sent->right = sent;

    AddBack(sent, 1);
    AddBack(sent, 2);
    AddBack(sent, 3);


    PrintList(sent);

    Clear(sent);
    delete sent;

    while (1) // Ввод натуральных чисел, 0 - конец
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        AddBack(sent, n);
    }
    int n;
    cin >> n;
    cout << (n % 10) << endl;
    return 0;

}