//
// Created by ZachZhang on 2017/5/21.
//

#ifndef ALGORITHM_CLUB_BINARY_SEARCH_TREE_H_H
#define ALGORITHM_CLUB_BINARY_SEARCH_TREE_H_H

#include <stdexcept>
#include <cassert>
#include <iostream>

//template <typename K, typename V>
//class BST;
//
//template <typename K, typename V>
//std::ostream& operator<< (std::ostream &os, const BST<K, V>& bst);

namespace alg_club {
    template <typename Key, typename Value>
    class BST {
        template <typename K, typename V>
        friend std::ostream& operator<< (std::ostream &os, const BST<K, V>& bst);
    private:
        struct Node {
            Key key;
            Value value;
            Node *parent;
            Node *left;
            Node *right;
        };
    public:
        BST(): root(nullptr) {}
        BST(const BST&) = delete;
        BST(BST&&) = delete;
        BST &operator=(const BST&) = delete;

        ~BST() { destruct_(root); }

        const Value& find(const Key &key) {
            if (auto node = find_node(key))
                return node -> value;
            throw std::runtime_error("key does not exist.");
        }

        void insert(const Key &key, const Value &value) {
            Node  *cur = root, *prev = nullptr;
            while (cur != NULL) {
                prev = cur;
                if (key < cur -> key)
                    cur = cur -> left;
                else
                    cur = cur -> right;
            }
            auto n_node = new Node;
            n_node -> value = value;
            n_node -> key = key;
            n_node -> left = nullptr;
            n_node -> right = nullptr;
            if (prev == nullptr) {
                n_node -> parent = nullptr;
                root = n_node;
                return;
            }
            n_node -> parent = prev;

            if (prev -> key > key) {
                prev -> left = n_node;
            } else {
                prev -> right = n_node;
            }
        }

        bool deleteKey(const Key &key) {
            auto node = find_node(key);
            if (!node) return false;
            if (node -> left == nullptr) {
                replace(node, node -> right);
            } else if (node -> right == nullptr) {
                replace(node, node -> left);
            } else {
                auto tmp = minimum(node -> right);
                replace(tmp, tmp -> right);
                replace(node, tmp);
                tmp -> left = node -> left;
                tmp -> right = node -> right;
            }
            delete node;
            return true;
        }


    private:
        Node *root;

        void destruct_(Node *node) {
            if (node == nullptr)
                return;
            destruct_(node -> left);
            destruct_(node -> right);
            delete node;
        }

        void replace(Node *u, Node *v) {
            if (u -> parent == nullptr) {
                root = v;
            } else if (u -> parent -> left == u){
                u -> parent -> left = v;
            } else {
                u -> parent -> right = v;
            }
            if (v != nullptr)
                v -> parent = u -> parent;
        }

        Node *find_node(const Key &key) {
            auto cur = root;
            while (cur != nullptr) {
                if (cur -> key == key)
                    return cur;
                if (cur -> key > key)
                    cur = cur -> left;
                else
                    cur = cur -> right;
            }
            return nullptr;
        }

        Node *minimum(Node *n) {
            Node* ret = n;
            while (ret -> left) {
                ret = ret -> left;
            }
            return ret;
        }

        void print_tree(Node *node, std::ostream& out) const {
            if (node == nullptr)
                return;
            print_tree(node -> left, out);
            out << "[" << node -> key << ": "
                      << node -> value << "] ";
            print_tree(node -> right, out);
        }
    };
    template <typename Key, typename Value>
    std::ostream &operator<<(std::ostream &out, const BST<Key, Value>& bst) {
        bst.print_tree(bst.root, out);
        return out;
    }
}

//template <typename Key, typename Value>
//std::ostream &operator<<(std::ostream &out, const alg_club::BST<Key, Value>& bst) {
//    bst.print_tree(bst -> root, out);
//}

#endif //ALGORITHM_CLUB_BINARY_SEARCH_TREE_H_H
