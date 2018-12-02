#ifndef AVL_TPP
#define AVL_TPP

#include <functional>
#include <algorithm>

#include "avl.h"

/**
 * @brief Constructs an AVL tree with no elements.
 */
template <typename T, typename Compare>
AVL<T, Compare>::AVL() : root(nullptr) {}

template <typename T, typename Compare>
AVL<T, Compare>::~AVL() { delete root; }

/**
 * @brief Returns @c true if the container is empty, @c false otherwise.
 *
 * The implementation of the function is the same as the one provided in class.
 * @return a @c boolean indicating whether the tree is empty
 */
template <typename T, typename Compare>
bool AVL<T, Compare>::empty() const {
    return !root;
}

/**
 * @brief Insert @a node into the container.
 *
 * The implementation of the function is the same as the one provided in class.
 * @param node Node to be inserted
 */
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

/**
 * @brief Insert @a val into the container.
 *
 * This is an overload of  AVL<T, Compare>::insert(AVLNode *) function.
 * @param val value to be inserted
 */
template <typename T, typename Compare>
void AVL<T, Compare>::insert(T &&val) {
    insert(new AVLNode(val));
}

/**
 * @brief Insert @a val into the container.
 *
 * This is an overload of AVL<T, Compare>::insert(AVLNode *) function.
 * @param val value to be inserted
 */
template <typename T, typename Compare>
void AVL<T, Compare>::insert(const T &val) {
    insert(new AVLNode(val));
}

/**
 * @brief Erase @a val from the container.
 *
 * The implementation of the function is the same as the one provided in class.
 *
 * @param val value to be erased
 */
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

/**
 * @brief Find the minimum value in the container.
 *
 * The implementation of the function is the same as the one provided in class.
 *
 * @return the minimum element
 */
template <typename T, typename Compare>
const T &AVL<T, Compare>::find_min() const {
    if (empty()) throw -1; // throw exception if the tree is empty
    return root->ltree.empty() ? root->val : root->ltree.find_min();
}

/**
 * @brief Find the value ranked @a rank in the container.
 *
 * The function recursively find the element of a sepecifc rank.
 * The root element is ranked @a rank if and only if the number of elements in the left subtree is equals to @a rank.
 * If the element is not found at the root, the function tries to locate which subtree the element is at using the @a rank and the size of left subtree and recursively search in the subtree.
 *
 * @return the element ranked @a rank
 */
template <typename T, typename Compare>
const T &AVL<T, Compare>::find_by_rank(int rank) const {
    if (empty()) throw -1; // throw exception if the tree is empty
    if (root->ltree.size() == rank) return root->val; // return the value if it matches the rank
    if (rank < root->ltree.size()) // locate the subtree where the element is in
        return root->ltree.find_by_rank(rank); // query the left subtree
    else
        return root->rtree.find_by_rank(rank - root->ltree.size() - 1); // query the right subtree
}

/**
 * @brief Return the height of the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 *
 * @return the height of the tree
 */
template <typename T, typename Compare>
int AVL<T, Compare>::bheight() const {
    return empty() ? -1 : root->height;
}

/**
 * @brief Return the balance factor of the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 *
 * @return the balance factor
 */
template <typename T, typename Compare>
int AVL<T, Compare>::bfactor() const {
    return root->rtree.bheight() - root->ltree.bheight();
}

/**
 * @brief Update the height of the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 */
template <typename T, typename Compare>
void AVL<T, Compare>::update_height() {
    root->height = 1 + std::max(root->ltree.bheight(), root->rtree.bheight());
}

/**
 * @brief Balance the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 */
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

/**
 * @brief Perform a left rotation on the root of the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 */
template <typename T, typename Compare>
void AVL<T, Compare>::left_rotate() {
    AVLNode *rc = root->rtree.root;
    root->rtree.root = rc->ltree.root;
    update_height(); update_size();
    rc->ltree.root = root;
    root = rc;
    update_height(); update_size();
}

/**
 * @brief Perform a right rotation on the root of the tree.
 *
 * The implementation of the function is the same as the one provided in class.
 */
template <typename T, typename Compare>
void AVL<T, Compare>::right_rotate() {
    AVLNode *lc = root->ltree.root;
    root->ltree.root = lc->rtree.root;
    update_height(); update_size();
    lc->rtree.root = root;
    root = lc;
    update_height(); update_size();
}

/**
 * @brief Return the size of the tree.
 *
 * @return the size of the tree
 */
template <typename T, typename Compare>
int AVL<T, Compare>::size() const {
    return empty() ? 0 : root->size;
}

/**
 * @brief Update the size of the tree.
 *
 * The implementation is similar to AVL<T, Compare>::update_height().
 */
template <typename T, typename Compare>
void AVL<T, Compare>::update_size() {
    root->size = 1 + root->ltree.size() + root->rtree.size();
}

/**
 * @brief Return the median element of the container.
 *
 * The function is a convinent wrapper around AVL<T, Compare>::find_by_rank(int). The function searches the element ranked AVL<T, Compare>::size() / 2, i.e. the median.
 *
 * @return the median element
 */
template<typename T, typename Compare>
const T &AVL<T, Compare>::find_median() const {
    return find_by_rank(size() / 2);
}

#endif
