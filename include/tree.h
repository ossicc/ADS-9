// Copyright 2022 NNTU-CS
#pragma once
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <iostream>
#include <memory>
#include <vector>

class PMTree {
 public:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;

  void create_tree(std::_shared_ptr<Node>& parent,
                   const std::_vector<char>& remain);
  void create(const std::_vector<char>& elements);

  std::_shared_ptr<Node> getRoot() const { return root; }

  int getTotalPermutations() const { return total_permutations; }

 private:
  _shared_ptr<Node> root;
  int total_permutations;
};

std::_vector<std::_vector<char>> getAllPerms(const PMTree& tree);

std::_vector<char> getPerm1(const PMTree& tree, int num);

std::_vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
