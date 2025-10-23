#pragma once
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* next;

    Node(int x = 0) : info(x), next(nullptr) {}
};

class myList {
private:
    Node* head;

public:
    myList() : head(nullptr) {}

    ~myList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add_el(int n) {
        Node* newNode = new Node(n);
        if (!head) {
            head = newNode;
            return;
        }
        Node* cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = newNode;
    }

    void show() const {
        Node* cur = head;
        while (cur) {
            cout << cur->info << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    void reverse() {
        Node* pr = nullptr;
        Node* cur = head;
        Node* next = nullptr;

        while (cur) {
            next = cur->next;
            cur->next = pr;
            pr = cur;
            cur = next;
        }
        head = pr;
    }
};
