#include "widget.h"
#include <utility>

void Dekart_tree::recountParents(Node* p) {
    if (p == nullptr) {
        return;
    }
    if (p->left != nullptr) {
        p->left->parent = p;
    }
    if (p->right != nullptr) {
        p->right->parent = p;
    }
}

int Dekart_tree::get_size(Node* v) {
    if (v == nullptr)
        return 0;
    else
        return v->size;
}

void Dekart_tree::_up(Node* v) {
    if (v == nullptr)
        return;
    v->size = get_size(v->left) + get_size(v->right) + 1;
    recountParents(v);
}

Node* Dekart_tree::_merge(Node* l, Node* r) {
    recountParents(l);
    recountParents(r);
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }

    if (l->priority < r->priority) {
        l->right = _merge(l->right, r);
        recountParents(l->right);
        recountParents(l->left);
        _up(l);
        return l;
    }
    else {
        r->left = _merge(l, r->left);
        recountParents(r->left);
        recountParents(r->right);
        _up(r);
        return r;
    }
}

std::pair<Node*, Node*> Dekart_tree::_split(Node* root, int k) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    recountParents(root);
    if (root->key < k) {
        auto p = _split(root->right, k);
        recountParents(p.first);
        recountParents(p.second);
        root->right = p.first;
        _up(root);
        return {root, p.second};
    }
    else {
        auto p = _split(root->left, k);
        recountParents(p.first);
        recountParents(p.second);
        root->left = p.second;
        _up(root);
        return {p.first, root};
    }

}

bool Dekart_tree::checker(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->key == key) return true;
    if (key < root->key) return checker(root->left, key);
    else return checker(root->right, key);
}

Node* Dekart_tree::insert(Node* root, Node* v) {
    if (root == nullptr)
        return v;
    recountParents(root);
    if (v->priority < root->priority) {
        auto p = _split(root, v->key);
        recountParents(p.first);
        recountParents(p.second);
        v->left = p.first;
        v->right = p.second;
        _up(v);
        recountParents(v);
        return v;
    }
    else {
        if (v->key < root->key) {
            root->left = insert(root->left, v);
            recountParents(root->left);
            recountParents(root);
        }
        else {
            root->right = insert(root->right, v);
            recountParents(root->right);
            recountParents(root);
        }
        _up(root);
        return root;
    }
}

Node* Dekart_tree::erase(Node* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key == key) {
        return _merge(root->left, root->right);
    }
    else if (key < root->key) {
        root->left = erase(root->left, key);
    }
    else {
        root->right = erase(root->right, key);
    }
    _up(root);
    recountParents(root);
    return root;
}

Node* Dekart_tree::erase_for_dauns(Node* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* ans = _merge(root->left, root->right);
    ans->parent = nullptr;
    recountParents(ans);
    recountParents(ans->left);
    recountParents(ans->right);
    return ans;
}
