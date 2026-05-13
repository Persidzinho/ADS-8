// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insertNode(Node* node, const T& value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->key) {
      node->left = insertNode(node->left, value);
    } else if (value > node->key) {
      node->right = insertNode(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  Node* searchNode(Node* node, const T& value) const {
    if (!node || node->key == value) return node;
    if (value < node->key) return searchNode(node->left, value);
    return searchNode(node->right, value);
  }

  int height(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
  }

  void collectNodes(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    collectNodes(node->left, vec);
    vec.push_back({node->key, node->count});
    collectNodes(node->right, vec);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T& value) {
    root = insertNode(root, value);
  }

  int search(const T& value) const {
    Node* node = searchNode(root, value);
    return node ? node->count : 0;
  }

  int depth() const {
    return height(root);
  }

  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collectNodes(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
