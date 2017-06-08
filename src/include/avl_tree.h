#ifndef ALGORITHM_CLUB_AVLTREE_H
#define ALGORITHM_CLUB_AVLTREE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace alg_club {
    template <typename T>
    struct AVLTreeNode {
        T key;
        int height;
        AVLTreeNode *left;
        AVLTreeNode *right;

        AVLTreeNode(T key, AVLTreeNode *l, AVLTreeNode *r)
            : key(key), height(0), left(l), right(r) {}
    };

    template <typename T>
    class AVLTree {
    public:
        AVLTree(): root(nullptr) {}
        AVLTree(const AVLTree&) = delete;
        AVLTree(AVLTree&&) = delete;
        AVLTree& operator=(const AVLTree&) = delete;

        ~AVLTree() {
            destroy(root);
        }

        int height() {
            return height(root);
        }

        void preOrder();
        void inOrder();
        void postOrder();

        AVLTreeNode<T>* search(T key) {
            return search(root, key);
        }
        
        T minimum() {
            AVLTreeNode<T>* node = minimum(root);
            if (node)
                return node -> key;
            else
                throw std::runtime_error("empty tree");
        }
        T maximum() {
            AVLTreeNode<T>* node = maximum(root);
            if (node)
                return node -> key;
            else
                throw std::runtime_error("empty tree");
        }

        void insert(T key) {
            insert(root, key);
        }

        void remove(T key) {
            auto node_ptr = search(root, key);
            if (node_ptr == nullptr)
                std::cerr << "Key does not exist.\n";
            else {
                remove(root, node_ptr);
            }
        }

        void destroy() {
            destroy(root);
        }

        void print();
    
        AVLTreeNode<T>* root;
    private:
        int height(AVLTreeNode<T>* node) {
            if (node != nullptr)
                return node -> height;
            return 0;
        }

        void preOrder(AVLTreeNode<T> *node) const;
        void inOrder(AVLTreeNode<T> *node) const;
        void postOrder(AVLTreeNode<T> *node) const;

        AVLTreeNode<T>* search(AVLTreeNode<T>* node, T key) const {
            if (node == nullptr || node -> key == key) {
                return node;
            }
            if (node -> key > key) {
                return search(node -> left, key);
            } else {
                return search(node -> right, key);
            }
        }
        AVLTreeNode<T>* minimum(AVLTreeNode<T> *node) {
            if (node == nullptr)
                return nullptr;
            while (node -> left)
                node = node -> left;
            return node;
        }
        AVLTreeNode<T>* maximum(AVLTreeNode<T> *node) {
            if (node == nullptr)
                return nullptr;
            while (node -> right)
                node = node -> right;
            return node;
        }

        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2) {
            AVLTreeNode<T> *k1;
            k1 = k2 -> left;
            k2 -> left = k1 -> right;
            k1 -> right = k2;

            k2 -> height = std::max(height(k2 -> left), height(k2 -> right)) + 1;
            k1 -> height = std::max(height(k1 -> left), k2 -> height) + 1;

            return k1;
        }
        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3) {
            k3 -> left = rightRightRotation(k3 -> left);
            return leftLeftRotation(k3);
        }

        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T> *k1) {
            AVLTreeNode<T>* k2;

            k2 = k1 -> right;
            k1 -> right = k2 -> left;
            k2 -> left = k1;

            k1 -> height = std::max(height(k1 -> left), height(k1 -> right)) + 1;
            k2 -> height = std::max(k1 -> height, height(k2 -> right)) + 1;

            return k2;
        }

        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1) {
            k1 -> right = leftLeftRotation(k1 -> right);
            return rightRightRotation(k1);
        }

        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key) {
            if  (tree == nullptr) {
                tree = new AVLTreeNode<T>(key, nullptr, nullptr);
                if (tree == nullptr) {
                    std::cerr << "ERROR: create avltree node failed!\n";
                    return nullptr;
                }
            } else if (key < tree -> key) {
                tree -> left = insert(tree -> left, key);
                if (height(tree -> left) - height(tree -> right) > 1) {
                    if (key < tree -> left -> key)
                        tree = leftLeftRotation(tree);
                    else
                        tree = leftRightRotation(tree);
                }
            } else if (key > tree -> key) {
                tree -> right = insert(tree -> right, key);
                if (height(tree -> right) - height(tree -> left) > 1) {
                    if (key > tree -> right -> key)
                        tree = rightRightRotation(tree);
                    else
                        tree = rightLeftRotation(tree);
                }
            } else {
                std::cerr << "ERROR: key already exists\n";
            }

            tree -> height = std::max(height(tree -> left), height(tree -> right)) + 1;
            return tree;
        }

        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z) {
            if (tree == nullptr || z == nullptr)
                return nullptr;
            if (z -> key > tree -> key) {
                tree -> right = remove(tree -> right, z);
                if (height(tree -> left) - height(tree -> right) > 1) {
                    AVLTreeNode<T>* l = tree -> left;
                    if (height(l -> right) > height(l -> left))
                        tree = leftRightRotation(tree);
                    else
                        tree = leftLeftRotation(tree);
                }
            } else if (z -> key < tree -> key) {
                tree -> left = remove(tree -> left, z);
                if (height(tree -> right) - height(tree -> left) > 1) {
                    AVLTreeNode<T>* right = tree -> right;
                    if (height(right -> right) > height(right -> left))
                        tree = rightRightRotation(tree);
                    else
                        tree = rightLeftRotation(tree);
                }
            } else {
                if (tree -> left != nullptr && tree -> right != nullptr) {
                    if (height(tree -> left) > height(tree -> right)) {
                        AVLTreeNode<T>* max_left = maximum(tree -> left);
                        tree -> key = max_left -> key;
                        tree -> left = remove(tree -> left, max_left);
                    } else {
                        AVLTreeNode<T>* min_right = minimum(tree -> right);
                        tree -> key = min_right -> key;
                        tree -> right = remove(tree -> right, min_right);
                    }
                } else {
                    AVLTreeNode<T>* tmp = tree;
                    tree = (tree -> left != nullptr) ? tree -> left : tree -> right;
                    delete tmp;
                }
            }
            tree -> height = std::max(height(tree -> left), height(tree -> right)) + 1;
            return tree;
        }

        void destroy(AVLTreeNode<T>* &root) {
            if (root == nullptr)
                return;
            if (root -> left)
                destroy(root -> left);
            if (root -> right)
                destroy(root -> right);
            delete root;
        }

        void print(AVLTreeNode<T>* node, T key, int direction);
    };
}

#endif // ALGORITHM_CLUB_AVLTREE_H ends here