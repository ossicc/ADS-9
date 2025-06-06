// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <memory>
#include <vector>

class Node {
 public:
  char value;
  std::vector<std::shared_ptr<Node>> children;

  explicit Node(char val) : value(val) {}
};

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& elements);
  void create(const std::vector<char>& elements);
  std::shared_ptr<Node> getRoot() const { return root; }

  size_t getTotalPermutations() const;
  std::vector<char> getElements() const;

 private:
  void create_tree(std::shared_ptr<Node>& parent,
                   const std::vector<char>& remain);
  std::shared_ptr<Node> root;
  std::vector<char> elements;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
