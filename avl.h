#ifndef AVL_H
#define AVL_H

#include <functional>

template <typename T, typename Compare = std::less<T>>
class AVL {
private:
    struct AVLNode {
        AVL ltree, rtree;
        int height, size;
        T val;
        AVLNode(T &&val) : height(0), size(1), val(val) {}
        AVLNode(const T &val) : height(0), size(1), val(val) {}
    } *root;
    Compare compare;
    void insert(AVLNode *node);
    void balance();
    int bheight() const;
    int bfactor() const;
    void update_height();
    void left_rotate();
    void right_rotate();
    int size() const;
    void update_size();
public:
    AVL();
    ~AVL();
    bool empty() const;
    void insert(const T &val);
    void insert(T &&val);
    void erase(const T &val);
    const T &find_min() const;
    const T &find_by_rank(int rank) const;
    const T &find_median() const;

};

#include "avl.tpp"

#endif // AVL_H
