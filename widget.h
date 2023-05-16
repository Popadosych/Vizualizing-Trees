#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <set>
#include <QPoint>
#include <QKeyEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <stdexcept>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsView>
//#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QComboBox>
#include <QSet>
#include <QPoint>
#include <QSlider>
#include <CustomQGraphicsScene.h>
#include <univertex.h>
#include <utility>
#include <bits/stdc++.h>
#include <rbt.h>


namespace Ui{
    class Widget;
}

struct Node {
    Node *right, *left, *parent;
    int key, color, h;
    QPoint low, high;
    int size, priority;
    int hail;

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
        std::mt19937 RANDOMM(time(0));
        priority = RANDOMM();
    }

    bool operator != (const Node* b) {
        return b->key != key;
    }

    Node* next() {
        Node* p;
        int hhh = this->hail;
        if (right != nullptr) {
            p = right;
            ++hhh;
            while (p->left != nullptr) {
                p = p->left;
                ++hhh;
            }
            p->hail = hhh;
            return p;
        }
        p = this;
        while (p->parent != nullptr) {
            if (p->parent->left == p) {
                --hhh;
                p->parent->hail = hhh;
                return p->parent;
            }
            p = p->parent;
            --hhh;
        }
        return nullptr;
    }

    bool operator < (const Node* b) {
        return b->key < key;
    }
};

class AVL_tree {
public:
    Node* root;

    AVL_tree() {
        this->root = nullptr;
    }

    int height() {
        return _height(root);
    }

    void insert(int k) {
        if (_findKey(root, k) == nullptr)
            root = _insert(root, k);
        root->parent = nullptr;
    }

    void remove(int k) {
        if (_findKey(root, k) != nullptr)
            root = _remove(root, k);
        root->parent = nullptr;
    }

    int maxLen() {
        return _maxLen(root);
    }

    Node * find(int k) {
        return _findKey(root, k);
    }

    Node* get_tree() {
        return root;
    }

    Node* begin() {
        Node *min = root;
        if (root == nullptr) return nullptr;
        int hhh = 1;
        while (min != nullptr && min->left != nullptr) {
            min = min->left;
            ++hhh;
        }
        min->hail = hhh;
        return min;
    }

    Node* end() {
        return nullptr;
    }

    void clear() {
        delete root;
        root = nullptr;
    }
    bool _checker(Node* p, int k);

private:
    int _height(Node* p);
    int _balanceDiff(Node* p);
    void _fixHeight(Node* p);
    int _maxLen(Node* p);
    Node* _rotateRight(Node* p);
    Node* _rotateLeft(Node* q);
    Node* _balance(Node* p);
    Node* _insert(Node* p, int k);
    Node* _findMin(Node* p);
    Node* _removeMin(Node* p);
    Node* _remove(Node* p, int k);
    Node* _findKey(Node* p, int k);
};


class Dekart_tree {
public:
    Node* root;
    Dekart_tree() {
        this->root = nullptr;
    }

    Node* begin() {
        Node *min = root;
        if (root == nullptr) return nullptr;
        int hhh = 1;
        while (min != nullptr && min->left != nullptr) {
            min = min->left;
            ++hhh;
        }
        min->hail = hhh;
        return min;
    }

    int height() {
        return _height(root);
    }

    Node* get_tree() {
        return root;
    }

    Node* end() {
        return nullptr;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    int get_size(Node* p);
    Node* insert(Node* root, Node* v);
    Node* erase(Node* root, int key);
    bool checker(Node* root, int key);
    Node* erase_for_dauns(Node* root, int key);

private:
    void recountParents(Node*);
    int _height(Node* p);
    void _up(Node* p);
    Node* _merge(Node* p, Node* r);
    std::pair<Node*, Node*> _split(Node* p, int k);
};

class Widget : public QWidget
{
Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void renderTree();
    void renderLines(Node* p);
    void renderLines_RBT(RBT* p);
    CustomQGraphicsScene* scene;

public slots:
    void addElem();
    void addRand();
    void clearTree();
    void delElem();
    void delete_elem(int);
    void on_combo_wombo_curentTextChanged(const QString &arg1);

private:
    AVL_tree atree;
    Dekart_tree dtree;
    RBT* rbtree;
    QFont mainFont;
    QPen mainPen;
    QLineEdit *vertex, *quant, *delline;
    QPushButton *add, *clear, *randd, *del;
    QGraphicsView* mainCanvas;
    CustomQGraphicsScene* mainScene;
    QSlider* horizontal_slider;
    QComboBox* combo_wombo;
    Ui::Widget *ui;
};



#endif
