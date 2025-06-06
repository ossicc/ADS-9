// Copyright 2022 NNTU-CS
#pragma once
#ifndef TREE_H
#define TREE_H

#include <memory>
#include <vector>

class Node {
 public:
  char value;
  std::vector<std::shared_ptr<Node>> children;

  Node(char val) : value(val) {}
};

class PMTree {
 public:
  PMTree(const std::vector<char>& elements);
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

#endif  // TREE_H
