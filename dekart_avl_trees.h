#include <node.h>

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

    Node* find(int k) {
        return _findKey(root, k);
    }

    Node* get_tree() {
        return root;
    }

    Node* begin() {
        Node *min = root;
        if (root == nullptr) return nullptr;
        int h = 1;
        while (min != nullptr && min->left != nullptr) {
            min = min->left;
            ++h;
        }
        min->height = h;
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
        min->height = hhh;
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

private:
    void recountParents(Node*);
    int _height(Node* p);
    void _up(Node* p);
    Node* _merge(Node* p, Node* r);
    std::pair<Node*, Node*> _split(Node* p, int k);
};
