#ifndef AVL_TPP
#define AVL_TPP

#include <functional>
#include <algorithm>

#include "avl.h"

template <typename T, typename Compare>
AVL<T, Compare>::AVL() : root(nullptr) {}

template <typename T, typename Compare>
AVL<T, Compare>::~AVL() { delete root; }

template <typename T, typename Compare>
bool AVL<T, Compare>::empty() const {
    return !root;
}

template <typename T, typename Compare>
void AVL<T, Compare>::insert(AVLNode *node) {
    if (empty()) {
        root = node;
    } else {
        if (compare(node->val, root->val))
            root->ltree.insert(node);
        else
            root->rtree.insert(node);
    }
    balance();
}

template <typename T, typename Compare>
void AVL<T, Compare>::insert(T &&val) {
    insert(new AVLNode(val));
}

template <typename T, typename Compare>
void AVL<T, Compare>::insert(const T &val) {
    insert(new AVLNode(val));
}

template <typename T, typename Compare>
void AVL<T, Compare>::erase(const T &val) {
    if (empty()) return;
    if (root->val < val) {
        root->rtree.erase(val);
    } else if (val < root->val) {
        root->ltree.erase(val);
    } else {
        if (root->ltree.empty() || root->rtree.empty()) {
            AVLNode *oldroot = root;
            root = root->ltree.empty() ? root->rtree.root : root->ltree.root;
            oldroot->ltree.root = oldroot->rtree.root = nullptr;
            delete oldroot;
        } else {
            root->val = root->rtree.find_min();
            root->rtree.erase(root->val);
        }
    }
    balance();
}

template <typename T, typename Compare>
const T &AVL<T, Compare>::find_min() const {
    if (empty()) throw -1;
    return root->ltree.empty() ? root->val : root->ltree.find_min();
}

template <typename T, typename Compare>
const T &AVL<T, Compare>::find_by_rank(int rank) const {
    if (empty()) throw -1;
    if (root->ltree.size() == rank) return root->val;
    if (rank < root->ltree.size())
        return root->ltree.find_by_rank(rank);
    else
        return root->rtree.find_by_rank(rank - root->ltree.size() - 1);
}

template <typename T, typename Compare>
int AVL<T, Compare>::bheight() const {
    return empty() ? -1 : root->height;
}

template <typename T, typename Compare>
int AVL<T, Compare>::bfactor() const {
    return root->rtree.bheight() - root->ltree.bheight();
}

template <typename T, typename Compare>
void AVL<T, Compare>::update_height() {
    root->height = 1 + std::max(root->ltree.bheight(), root->rtree.bheight());
}

template <typename T, typename Compare>
void AVL<T, Compare>::balance() {
    if (empty()) return;
    update_height(); update_size();
    if (bfactor() <= -2) {
        if (root->ltree.bfactor() >= 1) root->ltree.left_rotate();
        right_rotate();
    } else if (bfactor() >= 2) {
        if (root->rtree.bfactor() <= -1) root->rtree.right_rotate();
        left_rotate();
    }
}

template <typename T, typename Compare>
void AVL<T, Compare>::left_rotate() {
    AVLNode *rc = root->rtree.root;
    root->rtree.root = rc->ltree.root;
    update_height(); update_size();
    rc->ltree.root = root;
    root = rc;
    update_height(); update_size();
}

template <typename T, typename Compare>
void AVL<T, Compare>::right_rotate() {
    AVLNode *lc = root->ltree.root;
    root->ltree.root = lc->rtree.root;
    update_height(); update_size();
    lc->rtree.root = root;
    root = lc;
    update_height(); update_size();
}

template <typename T, typename Compare>
int AVL<T, Compare>::size() const {
    return empty() ? 0 : root->size;
}

template <typename T, typename Compare>
void AVL<T, Compare>::update_size() {
    root->size = 1 + root->ltree.size() + root->rtree.size();
}

template<typename T, typename Compare>
const T &AVL<T, Compare>::find_median() const {
    return find_by_rank(size() / 2);
}

#endif
