#ifndef AVL_H
#define AVL_H

#include <functional>

/**
 * @brief The AVL< T, Compare > class provides a container that stores a multiset of elements using AVL tree.
 *
 * The implememtation for this class is extremely similar to the one provided in class.
 * Except there is an additional size variable to keep track of the size of the subtree for rank query.
 *
 * The user can also define custom comparison for the element in the class using a functional class.
 * However, the default < comparator will be used if there is no custom comparator provided.
 *
 * @param T element type in the container
 * @param Compare the comparator class, defaulted to std::less<T>
 */
template <typename T, typename Compare = std::less<T>>
class AVL {
private:
    /**
     * @brief The AVLNode struct represents a node in a AVL tree.
     */
    struct AVLNode {
        AVL ltree; /**< @brief The left subtree. */
        AVL rtree; /**< @brief The right subtree. */
        int height; /**< @brief The height of the tree node. */
        int size; /**< @brief The size of the tree */
        T val; /**< @brief The root element */
        AVLNode(T &&val) : height(0), size(1), val(val) {} /**< @brief Constuct a node with the given element. */
        AVLNode(const T &val) : height(0), size(1), val(val) {} /**< @brief Construct a node with the given element. */
    } *root; /**< @brief The pointer to the root node of the tree */
    Compare compare; /**< @brief The comparator object */
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
