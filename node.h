#include <QPoint>
#include <bits/stdc++.h>

struct Node {
    Node *right, *left, *parent;
    int key, color, h;
    QPoint low, high;
    int size, priority;
    int height;

    Node() {
        right = left = nullptr;
        color = 1;
        key = 0;
        h = 0;
    }

    Node(int k, int c = -1, Node* p = nullptr) {
        key = k;
        color = c;
        right = left = nullptr;
        parent = p;
        h = 1;
        size = 1;
        std::mt19937 rand(time(0));
        priority = rand();
    }

    bool operator != (const Node* b) {
        return b->key != key;
    }

    Node* next() {
        Node* p;
        int h = height;
        if (right != nullptr) {
            p = right;
            ++h;
            while (p->left != nullptr) {
                p = p->left;
                ++h;
            }
            p->height = h;
            return p;
        }
        p = this;
        while (p->parent != nullptr) {
            if (p->parent->left == p) {
                --h;
                p->parent->height = h;
                return p->parent;
            }
            p = p->parent;
            --h;
        }
        return nullptr;
    }

    bool operator < (const Node* b) {
        return b->key < key;
    }
};