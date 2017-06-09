#ifndef ALGORITHM_CLUB_SPLAY_TREE_H
#define ALGORITHM_CLUB_SPLAY_TREE_H

#include <vector>
#include <stdexcept>

namespace alg_club {
    template <typename T>
    struct SplayTreeNode {
        T key;
        SplayTreeNode<T> *left;
        SplayTreeNode<T> *right;

        SplayTreeNode(const T& key, SplayTreeNode<T>* l, SplayTreeNode<T> *r)
            : key(key), left(left), right(right) {}
        SplayTreeNode(const T& key)
            : key(key), left(nullptr), right(nullptr) {}
        SplayTreeNode()
            : key(T()), left(nullptr), right(nullptr) {}
    };

    template <typename T>
    class SplayTree {
    public:
        SplayTree(): mRoot(nullptr) {}

        SplayTree(const SplayTree<T>&) = delete;
        SplayTree(SplayTree<T>&&) = delete;
        SplayTree<T>& operator=(const SplayTree<T>&) = delete;

        ~SplayTree() {
            destroy(mRoot);
        }

        void preOrder(std::vector<T>& preorder_vec) {
            preOrder(mRoot, preorder_vec);
        }

        void inOrder(std::vector<T>& inorder_vec) {
            inOrder(mRoot, inorder_vec);
        }
        void postOrder(std::vector<T>& postorder_vec) {
            postOrder(mRoot, postorder_vec);
        }

        SplayTreeNode<T>* search(T key) {
            search(mRoot, key);
        }
        T minimum() {
            auto min_node = minimum(mRoot);
            if (min_node == nullptr)
                throw std::runtime_error("Empty splay tree.");
            else
                return min_node -> key;
        }

        T maximum() {
            auto max_node = maximum(mRoot);
            if (max_node == nullptr)
                throw std::runtime_error("Empty splay tree");
            else
                return max_node -> key;
        }

        void insert(T key) {
            auto new_node = new SplayTreeNode<T>(key);
            mRoot = insert(mRoot, new_node);
            mRoot = splay(mRoot, key);
        }

        void remove(T key) {
            auto deleted = remove(mRoot, key);
            if (deleted == nullptr)
                throw std::runtime_error("Key does not exist.");
        }
    private:
        SplayTreeNode<T> *mRoot;

        void preOrder(SplayTreeNode<T>* root, std::vector<T> &preorder_vec) {
            if (root == nullptr)
                return;
            preorder_vec.push_back(root -> key);
            preOrder(root -> left, preorder_vec);
            preOrder(root -> right, preorder_vec);
        }

        void inOrder(SplayTreeNode<T>* root, std::vector<T>& inorder_vec) {
            if (root == nullptr)
                return;
            inOrder(root -> left, inorder_vec);
            inorder_vec.push_back(root -> key);
            inOrder(root -> right, inorder_vec);
        }

        void postOrder(SplayTreeNode<T>* root, std::vector<T>& postorder_vec) {
            if (root == nullptr)
                return;
            postOrder(root -> left, postorder_vec);
            postOrder(root -> right, postorder_vec);
            postorder_vec.push_back(root -> key);
        }

        SplayTreeNode<T>* search(SplayTreeNode<T>* root, T key) const {
            if (root == nullptr || root -> key == key)
                return root;
            if (key < root -> key)
                return search(root -> left, key);
            else
                return search(root -> right, key);
        }

        SplayTreeNode<T>* minimum(SplayTreeNode<T>* root) {
            if (root == nullptr)
                return root;
            while (root -> left)
                root = root -> left;
            return root;
        }

        SplayTreeNode<T>* maximum(SplayTreeNode<T>* root) {
            if (root == nullptr)
                return root;
            while (root -> right)
                root = root -> right;
            return root;
        }

        SplayTreeNode<T>* splay(SplayTreeNode<T>* root, T key) {
            if (root == nullptr)
                return root;
            SplayTreeNode<T> N, *l, *r, *node;
            N.left = N.right = nullptr;
            l = r = &N;

            while (true) {
                if (key < root -> key) {
                    if (root -> left == nullptr)
                        break;
                    if (key < root -> left -> key) {
                        // right rotation
                        node = root -> left;
                        root -> left = node -> right;
                        node -> right = root;
                        root = node;
                        if (root -> left == nullptr)
                            break;
                    }
                    r -> left = root;
                    r = root;
                    root = root -> left;
                } else if (key > root -> key) {
                    if (root -> right == nullptr)
                        break;
                    if (key > root -> right -> key) {
                        // left rotation
                        node = root -> right;
                        root -> right = node -> left;
                        node -> left = root;
                        root = node;
                        if (root -> right == nullptr)
                            break;
                    }
                    l -> right = root;
                    l = root;
                    root = root -> right;
                } else { break; }
            }
            l -> right = root -> left;
            r -> left = root -> right;
            root -> right = N.left;
            root -> left = N.right;

            return root;
        }

        SplayTreeNode<T>* insert(SplayTreeNode<T>* tree, SplayTreeNode<T>* node) {
            SplayTreeNode<T>* root =  nullptr, *cur = tree;
            while (cur) {
                root = cur;
                if (node -> key < cur -> key)
                    cur = cur -> left;
                else if (node -> key > cur -> key)
                    cur = cur -> right;
                else {
                    throw std::runtime_error("Key already exists.");
                }
            }
            if (root == nullptr) {
                tree = node;
            } else if (node -> key < root -> key) {
                root -> left = node;
            } else {
                root -> right = node;
            }
            return tree;            
        }

        SplayTreeNode<T>* remove(SplayTreeNode<T>* tree, T key) {
            if (tree == nullptr)
                return tree;
            SplayTreeNode<T> *node;
            if ((search(tree, key)) == nullptr)
                return nullptr;
            tree = splay(tree, key);
            
            if (tree -> left != nullptr) {
                node = splay(tree -> left, key);
                node -> right = tree -> right;
            } else {
                node = tree -> right;
            }
            delete tree;
            return node;
        }

        void destroy(SplayTreeNode<T>* root) {
            if (root == nullptr)
                return;
            destroy(root -> left);
            destroy(root -> right);
            delete root;
        }
    };
}
#endif // ALGORITHM_SPLAYCLUB_TREE_H ends here